#ifndef __SRC_WLAN_H
#define __SRC_WLAN_H

#include <nan.h>

struct WifiNetwork {
  std::string ssid;
  std::string bssid;
  std::string country_code;
  long beacon_interval;
  long noise;
  long rssi;
  long channel_number;
  long channel_band;
  long channel_width;
};

std::vector<WifiNetwork> wifi_scan_networks();
v8::Local<v8::Object> pack_wifi_network( const WifiNetwork *instance );
// WifiNetwork unpack_wifi_network( const v8::Local<v8::Object> *object );

NAN_METHOD( scan );

#endif // __SRC_WLAN_H
