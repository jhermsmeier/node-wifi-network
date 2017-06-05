#include "wifi.hpp"

NAN_MODULE_INIT(InitAll) {
  NAN_EXPORT(target, scan);
  NAN_EXPORT(target, listInterfaces);
}

NODE_MODULE(Wlan, InitAll);
