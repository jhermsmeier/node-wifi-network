var assert = require( 'assert' )
var wifi = require( '..' )

describe( 'wifi-network', function() {

  specify( 'scan()', function( done ) {

    this.timeout( 10e3 )

    wifi.scan( function( error, networks ) {
      assert.ifError( error )
      done()
    })

  })

})
