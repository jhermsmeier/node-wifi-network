#include <nan.h>
#include "wifi.hpp"

using v8::String;
using v8::Number;
using Nan::New;

v8::Local<v8::Object> pack_wifi_network( const WifiNetwork *instance ) {

  v8::Local<v8::Object> object = Nan::New<v8::Object>();

  Nan::Set( object,
    New<String>("ssid").ToLocalChecked(),
    New<String>( instance->ssid ).ToLocalChecked()
  );
  Nan::Set( object,
    New<String>("bssid").ToLocalChecked(),
    New<String>( instance->bssid ).ToLocalChecked()
  );
  Nan::Set( object,
    New<String>("countryCode").ToLocalChecked(),
    New<String>( instance->country_code ).ToLocalChecked()
  );
  Nan::Set( object,
    New<String>("beaconInterval").ToLocalChecked(),
    New<Number>( instance->beacon_interval )
  );
  Nan::Set( object,
    New<String>("noise").ToLocalChecked(),
    New<Number>( instance->noise )
  );
  Nan::Set( object,
    New<String>("rssi").ToLocalChecked(),
    New<Number>( instance->rssi )
  );
  Nan::Set( object,
    New<String>("channelNumber").ToLocalChecked(),
    New<Number>( instance->channel_number )
  );
  Nan::Set( object,
    New<String>("channelBand").ToLocalChecked(),
    New<Number>( instance->channel_band )
  );
  Nan::Set( object,
    New<String>("channelWidth").ToLocalChecked(),
    New<Number>( instance->channel_width )
  );

  return object;

}
