#include <nan.h>
#include "wifi.hpp"

class WlanScanWorker : public Nan::AsyncWorker {

 public:

  explicit WlanScanWorker( Nan::Callback *callback )
    : Nan::AsyncWorker( callback ), networks() {}

  ~WlanScanWorker() {}

  void Execute() {
    networks = wifi_scan_networks();
  }

  void HandleOKCallback() {

    Nan::HandleScope scope;
    v8::Local<v8::Object> network_list = Nan::New<v8::Array>();

    uint32_t i;
    uint32_t size = networks.size();

    for( i = 0; i < size; i++ ) {
      Nan::Set( network_list, i, pack_wifi_network( &networks[i] ) );
    }

    v8::Local<v8::Value> argv[] = { Nan::Null(), network_list };
    callback->Call( 2, argv );

  }

 private:

  std::vector<WifiNetwork> networks;

};


NAN_METHOD(scan) {

  if( !info[0]->IsFunction() ) {
    return Nan::ThrowTypeError( "Callback must be a function" );
  }

  Nan::Callback *callback = new Nan::Callback( info[0].As<v8::Function>() );
  Nan::AsyncQueueWorker( new WlanScanWorker( callback ) );

  info.GetReturnValue().SetUndefined();

}
