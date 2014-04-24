/**
 * Created by airead on 14-1-3.
 */
var cluster = require('cluster');
var http = require('http');
var numCPUs = require('os').cpus().length;

console.log('cpu number is ', numCPUs);
console.log('cluster.isMaster: ', cluster.isMaster);

if (cluster.isMaster) {
    console.log('master start...');

    // Fork workers.
    for (var i = 0; i < numCPUs; i++) {
        cluster.fork();
    }

    cluster.on('listening', function (worker, address) {
        console.log('listening: worker ' + worker.process.pid + ', Address: ' + address.address + ':' + address.port);
    });

    cluster.on('exit', function(worker, code, signal) {
        console.log('worker ' + worker.process.pid + ' died');
    });
} else {
    http.createServer(function(req, res) {
        res.writeHead(200);
        res.end('hello world\n' + process.pid);
    }).listen(8899);
}