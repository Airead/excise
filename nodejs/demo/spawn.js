/**
 * Created by airead on 14-1-6.
 */
var spawn = require('child_process').spawn;

var gitlog = spawn('../git', ['log', '-n2', '--pretty=format:"%h %ai %s"']);

var str = '';

gitlog.stdout.on('data', function (data) {
    console.log('stdout: ' + data);
    str += data;
});

gitlog.stderr.on('data', function (data) {
    console.log('stderr: ' + data);
});

gitlog.on('close', function (code) {
    console.log('child process exited with code ' + code);
});

gitlog.stdout.on('finish', function () {
    console.log(str);
});

gitlog.on('error', function (err) {
    console.log('catch error: ', err);
});

setTimeout(function () {
    console.log('time up');
}, 3000);