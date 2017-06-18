#ifndef SRC_WIFI_HPP_
#define SRC_WIFI_HPP_

#include <nan.h>
#include <string>
#include <vector>

struct WifiNetwork {
  std::string ssid;
  std::string bssid;
  std::string country_code;
  int64_t beacon_interval;
  int64_t noise;
  int64_t rssi;
  int64_t channel_number;
  int64_t channel_band;
  int64_t channel_width;
};

std::vector<WifiNetwork> wifi_scan_networks();
v8::Local<v8::Object> pack_wifi_network( const WifiNetwork *instance );
// WifiNetwork unpack_wifi_network( const v8::Local<v8::Object> *object );

NAN_METHOD( scan );

#endif // SRC_WIFI_HPP_
