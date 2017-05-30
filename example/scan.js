var wifi = require( '..' )
var inspect = require( '../test/inspect' )

wifi.scan( function( error, networks ) {
  console.log( inspect( error || networks ) )
})
