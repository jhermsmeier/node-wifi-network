# WiFi-Network
[![npm](https://img.shields.io/npm/v/wifi-network.svg?style=flat-square)](https://npmjs.com/package/wifi-network)
[![stability](https://img.shields.io/badge/stability-experimental-orange.svg?style=flat-square)](https://nodejs.org/api/documentation.html#documentation_stability_index)
[![npm license](https://img.shields.io/npm/l/wifi-network.svg?style=flat-square)](https://npmjs.com/package/wifi-network)
[![npm downloads](https://img.shields.io/npm/dm/wifi-network.svg?style=flat-square)](https://npmjs.com/package/wifi-network)
[![build status](https://img.shields.io/travis/jhermsmeier/node-wifi-network/master.svg?style=flat-square)](https://travis-ci.org/jhermsmeier/node-wifi-network)

Cross-platform wireless network control

## Install via [npm](https://npmjs.com)

```sh
$ npm install --save wifi-network
```

## Supported Platforms

- [x] Mac OS
- [ ] Windows
- [ ] Linux

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
    noise: -88,
    rssi: -52,
    channelNumber: 1,
    channelBand: 2,
    channelWidth: 20,
  },
  ...
]
```

## Contributing

### Auxiliary Dependencies

- [cpplint](https://github.com/cpplint/cpplint)

```
$ pip install cpplint
```

## References

- [Apple / CoreWLAN](https://developer.apple.com/reference/corewlan)
- [Microsoft / Native Wifi API](https://msdn.microsoft.com/en-us/library/ms706556(VS.85).aspx)
