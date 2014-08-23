/**
 * Created by airead on 14-7-29.
 */
var http = require('http');

function httpGet(url, callback) {
    var req = http.get(url, function (_res) {
        if (_res.statusCode == 200) {
            var data = '';
            _res.on('data', function (chunk) {
                data += chunk;
            });
            _res.on('end', function () {
                callback(null, data);
            });
            _res.on('error', callback);
        }
        else {
            var errmsg = '';
            _res.setEncoding('utf8');
            _res.on('data', function (chunk) {
                errmsg += chunk;
            });
            _res.on('end', function () {
                console.log('err: %s, statusCode: ', url, _res.statusCode, errmsg);
                callback(-1);
            });
        }
    });

    req.on('error', function (error) {
        console.log('connect failed', url, error);
        callback('-1');
    });

    req.on('socket', function (socket) {
        socket.setTimeout(2000, function () {
            req.abort();
        });
    });
}

var url = 'http://localhost:8888';
var start = Date.now();
httpGet(url, function (err, data) {
    console.log('cost %ss', Date.now() - start);
    if (err) {
        console.log('error: ', err);
        return;
    }
    console.log('receive data: ', data);
});