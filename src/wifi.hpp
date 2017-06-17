#ifndef SRC_WIFI_HPP_
#define SRC_WIFI_HPP_

#include <nan.h>
#include <string>
#include <vector>

struct WifiNetwork {
  std::string ssid;
  std::string bssid;
  std::string country_code;
  int64 beacon_interval;
  int64 noise;
  int64 rssi;
  int64 channel_number;
  int64 channel_band;
  int64 channel_width;
};

std::vector<WifiNetwork> wifi_scan_networks();
v8::Local<v8::Object> pack_wifi_network( const WifiNetwork *instance );
// WifiNetwork unpack_wifi_network( const v8::Local<v8::Object> *object );

NAN_METHOD( scan );

#endif // SRC_WIFI_HPP_
