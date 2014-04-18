/**
 * Created by airead on 14-4-18.
 */
var program = require('commander');

var redis = require('redis');

program
    .version('0.0.1')
    .option('-c, --channel [channel]', 'select channel [channel]', 'airead')
    .option('-n, --name [name]', 'select your name', 'guest' + Math.random())
    .parse(process.argv);


var client = redis.createClient();
client.on('error', function (err) {
    console.log('Error ' + err);
});

client.on('ready', function () {
    console.log('arguments: ', arguments);
    console.log('redis conn: ready');
});

var clientMsg = redis.createClient();
clientMsg.on('error', function (err) {
    console.log('Error ' + err);
});

clientMsg.on('ready', function () {
    console.log('arguments: ', arguments);
    console.log('redis conn: ready');
});


client.on('connect', function () {
    console.log('arguments: ', arguments);
    console.log('redis conn: connect');

    client.on('subscribe', function (channel, count) {
        console.log('on subscribe arguments: ', arguments);
    });
    client.subscribe(program.channel, function (err, msg) {
        console.log('subscribe callback argumetns: ', arguments);
    });

    client.on('message', function (channel, message) {
        if (message.split(':')[0] != program.name) {
            console.log('%s: recv %s', channel, message);
        }
    });

    process.stdin.resume();
    process.stdin.setEncoding('utf8');
    process.stdin.on('data', function (data) {
        var msg = [program.name, data].join(': ');
        clientMsg.publish(program.channel, msg);
    });
});
