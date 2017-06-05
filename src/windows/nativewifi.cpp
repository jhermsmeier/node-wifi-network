// See https://support.microsoft.com/en-us/kb/165721
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef UNICODE
#define UNICODE
#endif

#include <locale>
#include <codecvt>

#include <windows.h>
#include <wlanapi.h>
#include <objbase.h>
#include <wtypes.h>

#include <stdio.h>
#include <stdlib.h>

#include "../wifi.hpp"

// Need to link with Wlanapi.lib and Ole32.lib
#pragma comment( lib, "wlanapi.lib" )
#pragma comment( lib, "ole32.lib" )

std::string wide_to_string( std::wstring input ) {
  using convert_type = std::codecvt_utf8<wchar_t>;
  std::wstring_convert<convert_type, wchar_t> converter;
  return converter.to_bytes( input );
}

std::wstring string_to_wide( std::string input ) {
  using convert_type = std::codecvt_utf8<wchar_t>;
  std::wstring_convert<convert_type, wchar_t> converter;
  return converter.from_bytes( input );
}

std::string hex(const unsigned char* input, size_t length) {
  static const char* lut = "0123456789ABCDEF";
  std::string output;
  output.reserve(2 * length);
  for( size_t i = 0; i < length; ++i ) {
      const unsigned char c = input[i];
      output.push_back(lut[c >> 4]);
      output.push_back(lut[c & 15]);
  }
  return output;
}

std::string guid_to_string( GUID guid ) {
  WCHAR GuidString[40] = {0};
  DWORD result = StringFromGUID2( guid, (LPOLESTR) &GuidString, 39 );
  return wide_to_string( std::wstring( GuidString ) );
}

std::string get_interface_state(WLAN_INTERFACE_STATE state) {
  switch(state) {
    case wlan_interface_state_not_ready: return "NOT_READY"; break;
    case wlan_interface_state_connected: return "CONNECTED"; break;
    case wlan_interface_state_ad_hoc_network_formed: return "AD_HOC_NETWORK_FORMED"; break;
    case wlan_interface_state_disconnecting: return "DISCONNECTING"; break;
    case wlan_interface_state_disconnected: return "DISCONNECTED"; break;
    case wlan_interface_state_associating: return "ASSOCIATING"; break;
    case wlan_interface_state_discovering: return "DISCOVERING"; break;
    case wlan_interface_state_authenticating: return "AUTHENTICATING"; break;
    default: return "UNKNOWN";
  }
}

std::string ErrorResultToString(DWORD result) {

  if(result == ERROR_SUCCESS) {
    return std::string();
  }

  LPSTR messageBuffer = nullptr;
  DWORD langId = MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT);
  DWORD formatFlags = FORMAT_MESSAGE_ALLOCATE_BUFFER |
    FORMAT_MESSAGE_FROM_SYSTEM |
    FORMAT_MESSAGE_IGNORE_INSERTS;

  size_t size = FormatMessageA(formatFlags, NULL, result, langId, (LPSTR) &messageBuffer, 0, NULL);

  std::string message(messageBuffer, size);

  LocalFree(messageBuffer);

  return message;

}

std::vector<WifiInterface> wifi_list_interfaces() {

  std::vector<WifiInterface> wifi_interfaces;

  HANDLE hClientHandle = INVALID_HANDLE_VALUE;
  DWORD dwNegotiatedVersion = 0;
  DWORD result;

  result = WlanOpenHandle(WLAN_API_VERSION, NULL, &dwNegotiatedVersion, &hClientHandle);

  if(result != ERROR_SUCCESS) {
    printf("Error: %s\n", ErrorResultToString(result).c_str());
    return wifi_interfaces;
  }

  PWLAN_INTERFACE_INFO_LIST pIfList = NULL;
  PWLAN_INTERFACE_INFO pIfInfo = NULL;

  result = WlanEnumInterfaces(hClientHandle, NULL, &pIfList);

  if( result != ERROR_SUCCESS ) {
    printf("Error: %s\n", ErrorResultToString(result).c_str());
    WlanCloseHandle(hClientHandle, NULL);
    return wifi_interfaces;
  }

  for (DWORD i = 0; i < pIfList->dwNumberOfItems; i++) {

    WifiInterface iface = WifiInterface();
    pIfInfo = (WLAN_INTERFACE_INFO *) &pIfList->InterfaceInfo[i];

    iface.guid = pIfInfo->InterfaceGuid; // TODO: Copy this
    iface.description = wide_to_string(std::wstring(pIfInfo->strInterfaceDescription));
    iface.guid_string = guid_to_string(pIfInfo->InterfaceGuid);
    iface.state = get_interface_state(pIfInfo->isState);

    wifi_interfaces.push_back(iface);

  }

  WlanFreeMemory(pIfList);
  pIfInfo = NULL;

  WlanCloseHandle(hClientHandle, NULL);
  hClientHandle = INVALID_HANDLE_VALUE;

  return wifi_interfaces;

}

std::vector<WifiNetwork> wifi_scan_networks() {

  std::vector<WifiNetwork> wifi_networks;
  std::vector<WifiInterface> wifi_interfaces = wifi_list_interfaces();

  DWORD result;
  HANDLE hClientHandle = INVALID_HANDLE_VALUE;
  DWORD dwClientVersion = WLAN_API_VERSION;
  DWORD dwNegotiatedVersion = 0;

  result = WlanOpenHandle(dwClientVersion, NULL, &dwNegotiatedVersion, &hClientHandle);

  if(result != ERROR_SUCCESS) {
    printf("Error opening handle: %s\n", ErrorResultToString(result).c_str());
  } else {
    printf("Success opening handle\n");
  }

  // result = WlanScan(hClientHandle, &pInterfaceGuid, NULL, NULL, NULL);

  GUID interfaceGuid = wifi_interfaces[0].guid;
  PWLAN_BSS_LIST pBssList = NULL;
  PWLAN_BSS_ENTRY pBssEntry = NULL;

  result = WlanGetNetworkBssList( hClientHandle, &interfaceGuid, NULL, dot11_BSS_type_any, NULL, NULL, &pBssList );

  if( result != ERROR_SUCCESS ) {
    printf("Error: %s\n", ErrorResultToString(result).c_str());
  } else {

    for( DWORD i = 0; i < pBssList->dwNumberOfItems; i++ ) {

      pBssEntry = (WLAN_BSS_ENTRY *) &pBssList->wlanBssEntries[i];
      WifiNetwork network = WifiNetwork();

      network.ssid = std::string(reinterpret_cast<const char*>(pBssEntry->dot11Ssid.ucSSID), pBssEntry->dot11Ssid.uSSIDLength);
      network.bssid = hex(pBssEntry->dot11Bssid, 6);
      network.rssi = (int64_t) pBssEntry->lRssi;
      network.channel_band = (int64_t) pBssEntry->ulChCenterFrequency;
      // NOTE: This is not noise, but link quality - only added for eyeballing
      network.noise = (int64_t) pBssEntry->uLinkQuality;

      wifi_networks.push_back( network );

    }

    WlanFreeMemory(pBssList);
    pBssEntry = NULL;

  }

  // TODO: Use `WlanGetAvailableNetworkList()` instead, as the documentation
  // (https://docs.microsoft.com/en-us/windows/desktop/api/wlanapi/nf-wlanapi-wlangetnetworkbsslist)
  // notes that data returned by `WlanGetNetworkBssList()` is not to be trusted,
  // since it originates from the network infrastructure (AP, ifrastr. BSS network, or network peer)

  if(hClientHandle != INVALID_HANDLE_VALUE) {
    if(WlanCloseHandle(hClientHandle, NULL) != ERROR_SUCCESS) {
      printf("Error closing handle: %s\n", ErrorResultToString(result).c_str());
    }
  }

  return wifi_networks;

}
