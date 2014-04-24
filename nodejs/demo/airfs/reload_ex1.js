/**
 * Created by airead on 14-4-24.
 */
var path = require('path');
var reload = require('./reload');
var wt = require('./watchFile');

var file = 'watchFile.js';
var fullPath = path.resolve(file);
console.log(fullPath);
reload.autoReload(fullPath, function (newModule) {
    if (newModule) {
        wt = newModule;
        wt.test('test');
    }
});