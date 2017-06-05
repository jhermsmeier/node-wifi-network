#include <nan.h>
#include "wifi.hpp"

using v8::String;
using v8::Number;
using Nan::New;

v8::Local<v8::Object> pack_wifi_interface( const WifiInterface *instance ) {

  v8::Local<v8::Object> object = Nan::New<v8::Object>();

  Nan::Set( object,
    New<String>("guid").ToLocalChecked(),
    New<String>( instance->guid_string ).ToLocalChecked()
  );
  Nan::Set( object,
    New<String>("description").ToLocalChecked(),
    New<String>( instance->description ).ToLocalChecked()
  );
  Nan::Set( object,
    New<String>("state").ToLocalChecked(),
    New<String>( instance->state ).ToLocalChecked()
  );

  return object;

}
