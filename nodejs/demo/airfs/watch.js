/**
 * Created by airead on 14-3-31.
 */
var path = require('path');
var wt = require('./watchFile');
var fs = require('fs');

function addAutoReloadDir(dir) {
    fs.watch(dir, function (event, file) {
        console.log('arguments: ', arguments);
        console.log('event: %s, file: %s', event, file);
        if (event == "change") {
            console.log('before delete wt: ', wt);
            wt.test('before');
            //console.log('require cache: ', require.cache);
            delete require.cache[file];
            console.log('after delete wt: ', wt);
            wt.test('after');
            wt = require('./watchFile');
            console.log('reload wt: ', wt);
            wt.test('required');
        }
    });
}

function addAutoReloadFileTest(file) {
    var dir = path.dirname(file);
    var filename = path.basename(file);
    console.log('dir', dir);
    fs.watch(dir, function (event, changeFile) {
        console.log('event: %s, file: %s', event, changeFile);

        if (changeFile == filename) {
            console.log('event: %s, file: %s', event, file);
            console.log('before delete wt: ', wt);
            wt.test('before');
            //console.log('require cache: ', require.cache);
            //delete require.cache[file];
            console.log('after delete wt: ', wt);
            wt.test('after');
            require('./watchFile');
            console.log('reload wt: ', wt);
            wt.test('required');
        }
    });
}

function addAutoReloadFile(file, cb) {
    var dir = path.dirname(file);
    var filename = path.basename(file);
    console.log('dir: ', dir);
    console.log('filename', filename);
    fs.watch(dir, function (event, changeFile) {
        console.log('changeFile: ', changeFile);
        if (changeFile == filename) {
            delete require.cache[file];
            cb(require(file));
            return;
        }
        cb(null);
    });
}

var file = 'watchFile.js';
var fullPath = path.resolve(file);
console.log(fullPath);
//addAutoReloadFileTest(fullPath);
addAutoReloadFile(fullPath, function (newModule) {
    if (newModule) {
        wt = newModule;
        wt.test('test');
    }
});
