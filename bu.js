#!/usr/bin/node

const {spawn,exec,spawnSync}    = require('child_process');
const Configstore               = require('configstore');
const fs                        = require('fs');
const Log                       = require('@lromeraj/log');
const Colors                    = require('colors/safe');
const argv                      = require('yargs').argv;
const ncp                       = require('ncp').ncp;
const walk                      = require('walk');
const moment                    = require('moment');

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

  const bu = p => {

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


            next();
          }

        }

      });

    })

    let zName = p.name+'_'+moment().format('DDMMYYYY_HH_mm_ss');
    spawnSync( 'zip', [ '-r', p.local.dest+'/'+zName, ..._toZip ], {stdio:'inherit'} );

    let _fOld = {
      name: '',
      mtimeMs: null
    }

    let _q = 0;

    let files = fs.readdirSync( p.local.dest );

    files.forEach( _fName => {
      let fstat = fs.statSync( p.local.dest+'/'+_fName );
      if ( fstat.isFile() ) {
        if ( _fName.indexOf('.zip') > -1 && _fName.indexOf( p.name ) > -1 ) {
          if ( _fOld.mtimeMs == null || fstat.mtimeMs < _fOld.mtimeMs ) {
            _fOld.name = _fName;
            _fOld.mtimeMs = fstat.mtimeMs;
          }
          _q++;

        }
      }

    })

    if  ( _q >= p.max+1 ) {
      fs.unlinkSync( p.local.dest+'/'+_fOld.name );
    }


  }

  profs.forEach( p => {

    if ( p.name === argv.name ) {
      bu( p );
    }

  });




}

main();
