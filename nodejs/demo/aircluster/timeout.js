/**
 * Created by airead on 14-1-4.
 */
var http = require('http');

//The url we want is: 'www.random.org/integers/?num=1&min=1&max=10&col=1&base=10&format=plain&rnd=new'
var options = {
    host: '10.0.1.88',
    port: '8989',
    path: '/integers/?num=1&min=1&max=10&col=1&base=10&format=plain&rnd=new'
};

callback = function (response) {
    var str = '';

    //another chunk of data has been recieved, so append it to `str`
    response.on('data', function (chunk) {
        str += chunk;
    });

    //the whole response has been recieved, so we just print it out here
    response.on('end', function () {
        console.log(str);
    });
};

var req = http.request(options, callback);
//req.setTimeout(2000, function () {
//    console.log('timeout');
//});
req.on('socket', function (socket) {
    console.log('on socket');
    socket.setTimeout(2000);
});
req.end();

req.on('error', function(err) {
    console.log('caught error: ', err);
});
