/**
 * Created by airead on 14-3-26.
 */
var spawn = require('child_process').spawn;

function getFileOwner(file, cb) {
    var llCmd = spawn('ls', ['-l', file]);
    var stdout = '';
    llCmd.stdout.on('data', function (data) {
        stdout += data;
    });
    llCmd.on('error', function (err) {
        console.log(err);
        stdout += err.toString();
    });
    llCmd.on('close', function (code) {
        console.log('exit with code [%s]', code);
        console.log('stdout: ', stdout);
        var tmps = stdout.split(' ');
        if(tmps.length >= 3) {
            cb(tmps[3]);
        } else {
            cb('');
        }
    });
}

var file = 'getFileOwner.js';
getFileOwner(file, function (owner) {
    console.log('file %s owner: %s', file, owner);
});