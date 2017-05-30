# WiFi-Network
[![npm](https://img.shields.io/npm/v/wifi-network.svg?style=flat-square)](https://npmjs.com/package/wifi-network)
[![npm license](https://img.shields.io/npm/l/wifi-network.svg?style=flat-square)](https://npmjs.com/package/wifi-network)
[![npm downloads](https://img.shields.io/npm/dm/wifi-network.svg?style=flat-square)](https://npmjs.com/package/wifi-network)
[![build status](https://img.shields.io/travis/jhermsmeier/node-wifi-network/master.svg?style=flat-square)](https://travis-ci.org/jhermsmeier/node-wifi-network)

Cross-platform wireless network control

## Install via [npm](https://npmjs.com)

```sh
$ npm install --save wifi-network
```

## Usage

```js
var wifi = require( 'wifi-network' )
```

### Scan for available networks

```js
wifi.scan( function( error, networks ) {
  console.log( error || networks )
})
```

```js
[
  {
    ssid: 'Vodafone Hotspot',
    bssid: 'a6:31:c4:f2:2d:ca',
    countryCode: 'DE',
    beaconInterval: 100,
    noise: -87,
    rssi: -48,
    channelNumber: 1,
    channelBand: 1,
    channelWidth: 1
  },
  ...
]
```
