var wifi = module.exports = require( 'bindings' )( 'wifi.node' )

// Channel band
wifi.BAND_UNKNOWN = 0
wifi.BAND_2GHZ = 2
wifi.BAND_5GHZ = 5

// Channel width
wifi.WIDTH_UNKNOWN = 0
wifi.WIDTH_20MHZ = 1
wifi.WIDTH_40MHZ = 2
wifi.WIDTH_80MHZ = 3
wifi.WIDTH_160MHZ = 4

// Physical Layer (PHY) Modes
wifi.MODE_NONE = 0
wifi.MODE_11A = 1
wifi.MODE_11B = 2
wifi.MODE_11G = 3
wifi.MODE_11N = 4
wifi.MODE_11AC = 5
