var wifi = require( '..' )
var inspect = require( '../test/inspect' )

wifi.listInterfaces( function( error, interfaces ) {
  console.log( inspect( error || interfaces ) )
})
