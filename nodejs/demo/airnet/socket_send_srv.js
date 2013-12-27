/**
 * Created by airead on 13-12-23.
 */
var net = require('net');

var HOST = '127.0.0.1';
var PORT = 6969;

var server = net.createServer();
server.listen(PORT, HOST, function () {
    console.log('Server listening on ' + server.address().address + ':' + server.address().port);

    server.on('connection', function (sock) {
        console.log('CONNECTED: ' + sock.remoteAddress + ':' + sock.remotePort);

        sock.on('data', function (data) {
            console.log('DATA ' + sock.remoteAddress + ': ' + data);
            sock.write('You said "' + data + '"');
        });

        sock.on('close', function (data) {
            console.log('CLOSE: ' + sock.remoteAddress + ' ' + sock.remotePort);
        });
    });
});
