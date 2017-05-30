#import <CoreWLAN/CoreWLAN.h>
#import "../wifi.hpp"

long get_channel_band(CWChannel *channel) {
  switch( [channel channelBand] ) {
    case kCWChannelBandUnknown:
      return 0;
    case kCWChannelBand2GHz:
      return 2;
    case kCWChannelBand5GHz:
      return 5;
  }
}

long get_channel_width(CWChannel *channel) {
  switch( [channel channelWidth] ) {
    case kCWChannelWidthUnknown:
      return 0;
    case kCWChannelWidth20MHz:
      return 20;
    case kCWChannelWidth40MHz:
      return 40;
    case kCWChannelWidth80MHz:
      return 60;
    case kCWChannelWidth160MHz:
      return 120;
  }
}

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
    wifi_network.bssid = [[network bssid] UTF8String];
    wifi_network.country_code = [[network countryCode] UTF8String] ?
      [[network countryCode] UTF8String] : "";
    wifi_network.beacon_interval = [network beaconInterval];
    wifi_network.noise = [network noiseMeasurement];
    wifi_network.rssi = [network rssiValue];
    wifi_network.channel_number = [channel channelNumber];
    wifi_network.channel_band = get_channel_band( channel );
    wifi_network.channel_width = get_channel_width( channel );

    wifi_networks.push_back( wifi_network );

  }

  return wifi_networks;

}
