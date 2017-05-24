var assert = require( 'assert' )
var wifi = require( '..' )

describe( 'wifi-network', function() {

  specify( 'scan()', function( done ) {
    wifi.scan( function( error, networks ) {
      assert.ifError( error )
    })
  })

})
