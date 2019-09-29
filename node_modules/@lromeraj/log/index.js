const moment = require('moment');
const Colors = require('colors/safe');

// simple log functions
class Log {

  static now() {
    let mom = moment();
    return `${mom.format('DD/MM/YYYY HH:mm:ss')}`;
  }

  static pref() {

    let pref = '';

		if ( process.env.LOG_NAME ) {
			pref = `[${Colors.yellow( process.env.LOG_NAME )}]`;
		}

    if ( process.env.LOG_TIME == "yes" ) {
      pref += `${Colors.bold( this.now() ) }` + '.';
    } else {
      pref = pref.length ? pref+'.' : '';
    }

    return pref;
  }

  static error( msg ) {
    console.log(`${this.pref()}${Colors.red( 'error' )}: ${msg}`);
  }

  static param( attr, val ) {
    Log.info( Colors.magenta( attr ) + ': ' + val );
  }

  static info( msg ) {
    console.log(`${Log.pref()}${Colors.cyan( 'info' )}: ${msg}`);
  }

  static warn( msg ) {
    console.log(`${Log.pref()}${Colors.yellow( 'warn' )}: ${msg}`);
  }

  static success( msg ) {
    console.log(`${Log.pref()}${Colors.green( 'success' )}: ${msg}`)
  }

}

module.exports = Log;
