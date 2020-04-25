#include "wifi.hpp"

NAN_MODULE_INIT( Init ) {
  NAN_EXPORT( target, scan );
}

#if NODE_MAJOR_VERSION >= 10
  NAN_MODULE_WORKER_ENABLED( Wlan, Init );
#else
  NODE_MODULE( Wlan, Init );
#endif
