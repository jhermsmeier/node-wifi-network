#import <CoreWLAN/CoreWLAN.h>

int main(int argc, char const *argv[]) {
  CWWiFiClient *client = [CWWiFiClient sharedWiFiClient];
  CWInterface *interface = [client interface];

  NSError *error = nil;
  // Actively scan for networks around
  NSSet<CWNetwork *> *networks = [interface scanForNetworksWithSSID:nil error:&error];
  // Get the currently cached results (from a previous scan by either the OS or oneself)
  // NSSet<CWNetwork *> *networks = [interface cachedScanResults];

  CWChannel *channel;

  unsigned int i = 0;
  unsigned int size = [networks count];

  printf("[\n");
  for( CWNetwork *network in networks ) {
    i++;
    printf("  {\n");
    printf("    \"ssid\": \"%s\",\n", [[network ssid] UTF8String]);
    printf("    \"bssid\": \"%s\",\n", [[network bssid] UTF8String]);
    printf("    \"countryCode\": \"%s\",\n", [[network countryCode] UTF8String]);
    printf("    \"beaconInterval\": %ld,\n", (long) [network beaconInterval]);
    printf("    \"noise\": %ld,\n", (long) [network noiseMeasurement]);
    // Received Signal Strength Indication (RSSI)
    printf("    \"rssi\": %ld,\n", (long) [network rssiValue]);
    channel = [network wlanChannel];
    printf("    \"channel\": %ld,\n", (long) [channel channelNumber]);
    printf("    \"channelBand\": %ld,\n", (long) [channel channelBand]);
    printf("    \"channelWidth\": %ld\n", (long) [channel channelWidth]);
    if( i < size ) {
      printf("  },\n");
    } else {
      printf("  }\n");
    }
  }
  printf("]\n");

  return 0;
}
