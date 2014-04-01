/**
 * Created by airead on 14-3-26.
 */
var spawn = require('child_process').spawn;

var idCmd = spawn('sudo', ['su', '-', 'airead', '-c', 'id', 'airead']);

var stdout = '';

idCmd.stdout.on('data', function (data) {
    stdout += data;
});

idCmd.on('close', function (code) {
    console.log('stdout: ', stdout);
});