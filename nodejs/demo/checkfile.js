/**
 * Created by airead on 14-3-26.
 */
var fs = require('fs');

function getFirstExistFile(paths, cb) {
    _exist(paths, 0, function (file) {
        cb(file);
    });

    function _exist(paths, index, cb) {
        if (paths.length == index) {
            cb('');
            return;
        }
        fs.exists(paths[index], function (exist) {
            if (exist) {
                cb(paths[index]);
                return;
            }
            _exist(paths, index + 1, cb);
        });
    }
}

var fileList = ['not_exist.txt', 'checkfilef.js', 'debug12.js'];
getFirstExistFile(fileList, function (file) {
    if (file) {
        console.log('get first exists file: ', file);
    } else {
        console.log('not fonud exists file');
    }
});
