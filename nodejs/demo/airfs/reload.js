/**
 * Created by airead on 14-4-24.
 */
var fs = require('fs');
var path = require('path');


// {
//   "path": {
//        changeFile1: callback,
//        cahngeFile2: callback,
//   }
// }

// usage:
//reload.autoReload(fullPath, function (newModule) {
//    if (newModule) {
//        something = newModule;
//        do other ...
//    }
//});

var config = {};

function autoReload(fileFullPath, callback) {
    var dir = path.dirname(fileFullPath);
    var filename = path.basename(fileFullPath);

    console.log('set auto reload: dir [%s], file [%s] ', dir, filename);

    if (!config[dir]) {
        config[dir] = {};
        watchDir(dir)
    }

    config[dir][filename] = callback;
}

function watchDir(dir) {
    fs.watch(dir, function (event, changeFile) {
        _debug('changeFile: ', changeFile);
        if (!config[dir]) {
            console.log('[autoReload] error: not found %s config', dir);
            return;
        }

        if (!config[dir][changeFile]) {
            _debug('[autoReload] debug: not found %s config, filename: %s', dir, changeFile);
            return;
        }

        var fileFullPath = path.join(dir, changeFile);
        delete require.cache[fileFullPath];
        var callback = config[dir][changeFile];
        _debug('run callback', callback);
        callback(require(fileFullPath));
    });
}

function _debug() {
    if (process.env['AUTH_RELOAD'] == 1) {
        console.log.apply(console.log, arguments);
    }
}

exports.autoReload = autoReload;