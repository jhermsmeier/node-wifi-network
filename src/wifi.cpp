#include "wifi.hpp"

NAN_MODULE_INIT(InitAll) {
  NAN_EXPORT(target, scan);
}

NODE_MODULE(Wlan, InitAll);
