#import <CoreWLAN/CoreWLAN.h>
#import "../wifi.hpp"

std::vector<WifiNetwork> wifi_scan_networks() {

  CWChannel *channel;
  // TODO: Error handling
  NSError *error;

  CWWiFiClient *client = [CWWiFiClient sharedWiFiClient];
  CWInterface *interface = [client interface];

  NSSet<CWNetwork *> *networks = [interface scanForNetworksWithSSID:nil error:&error];
  std::vector<WifiNetwork> wifi_networks;

  for( CWNetwork *network in networks ) {

    WifiNetwork wifi_network = WifiNetwork();
    channel = [network wlanChannel];

    wifi_network.ssid = [[network ssid] UTF8String];
    wifi_network.bssid = [[network bssid] UTF8String] ?
      [[network bssid] UTF8String] : "";
    wifi_network.country_code = [[network countryCode] UTF8String] ?
      [[network countryCode] UTF8String] : "";
    wifi_network.beacon_interval = [network beaconInterval];
    wifi_network.noise = [network noiseMeasurement];
    wifi_network.rssi = [network rssiValue];
    wifi_network.channel_number = [channel channelNumber];
    wifi_network.channel_band = [channel channelBand];
    wifi_network.channel_width = [channel channelWidth];

    wifi_networks.push_back( wifi_network );

  }

  return wifi_networks;

}
