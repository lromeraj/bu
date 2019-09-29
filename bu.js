#!/usr/bin/node

const {spawn,exec}  = require('child_process');
const Configstore   = require('configstore');
const fs            = require('fs');
const Log           = require('@lromeraj/log');
const Colors        = require('colors/safe');
const argv          = require('yargs').argv;
const ncp           = require('ncp').ncp;
const walk          = require('walk');

async function main() {

  const CONFIG = new Configstore( "bu", {}, {
    globalConfigPath: true
  });

  const cleanPathStr = ( pstr ) => {
    return pstr.replace( /\/{2,}/g, '/' );
  }

  let profs = CONFIG.get('profiles') || [];

  let summery = {
    filesCopied: 0
  }

  let _toZip = [];

  if ( typeof argv.zip === 'string' ) {
    console.log( 'hola' );
  }

  profs.forEach( p => {

    if ( p.name === argv.name ) {

      let _srcs = p.srcs || [];
      let _regs = [];
      let _bu = [];

      p.ignore.forEach( ig => {
        let m = ig.match( new RegExp('^/(.*?)/([gimy]*)$') );
        _regs.push( new RegExp( m[1], m[2] ) );
      });

      _srcs.forEach( src => {

        let _baseDir = cleanPathStr( src ).split('/');
        _baseDir.pop();
        _baseDir = _baseDir.join('/');

        walker = walk.walkSync( src, {

          listeners: {

            file: function (root, fileStats, next) {

              let cit = true; // copy it or not
              let ig = false;
              let _destDir = p.local.dest+'/'+root.replace(_baseDir,'');
              let _srcFile = root+'/'+fileStats.name;
              let _destFile = _destDir+'/'+fileStats.name;

              if ( fs.existsSync( _destFile ) ) {

                let m1 = fs.statSync( _srcFile ).mtimeMs;
                let m2 = fs.statSync( _destFile ).mtimeMs;

                if ( m2 > m1 ) {
                  cit = false;
                }

              }

              _regs.forEach( reg => {

                if ( _srcFile.match( reg ) ) {
                  Log.warn(`ignoring ${cleanPathStr( _srcFile )}`);
                  ig = true;
                }

              })

              if ( !ig ) {
                _toZip.push( _srcFile );
              }

              if ( cit && !ig ) {

                if ( !fs.existsSync( _destDir ) ) {
                  Log.info( `mkdir ${cleanPathStr( _destDir )}` );
                  fs.mkdirSync( _destDir, {recursive: true}, function( err ) {
                    console.log( err );
                  });
                }


                Log.info(`copying ${cleanPathStr( _srcFile )}`);
                fs.copyFileSync( _srcFile, _destFile, function( err ) {
                  console.log( err );
                  summery.filesCopied++;

                });

              }

              next();
            }

          }

        });


      })

        let _scp;

        if ( p.remote.host ) {
          Log.info(`building zip ...`);
          let _zipName = p.name+'.zip';
          exec(`zip ${_zipName} ${_toZip.join(' ')}`, ( err, stdout, stderr ) => {
            Log.info(`sending zip ...`);
            _scp = spawn( 'scp', [ _zipName, `${p.remote.host}:${p.remote.dest}` ], {stdio: 'inherit'} );
            sh
          })

        }



    }



  });




}

main();
