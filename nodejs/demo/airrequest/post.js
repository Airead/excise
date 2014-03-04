var http = require('http');
var qs = require('querystring');

var path = [
    '/test_post',
    'AIREAD_TEST', '13'
].join('/');


var postData = 'data={"level": 10}&ddd=/da[1"fda+';

var options = {
    hostname: '127.0.0.1',
    port: 5555,
    path: path,
    body: 'hero_data=asdasdf',
    headers: {
          'Content-Type': 'application/x-www-form-urlencoded',
          'Content-Length': postData.length
    }
};
console.log(options);

httpPost(options, postData, function (err, rdata) {
    if (err) {
        var msg = 'err: set dddd failed';
        console.log(msg);
        console.log(err);
        console.log('return msg:', msg);

        return;
    }
    console.log('return data: ', rdata);
});

function httpPost(options, data, callback) {
    options.method = 'POST';
    var req = http.request(options, function (res) {
        if (res.statusCode != 200) {
            console.log(res.statusCode);
            callback(-1);
            return;
        }

        var data = '';
        res.setEncoding('utf8');
        res.on('data', function (chunk) {
            data += chunk;
        });
        res.on('end', function () {
            callback(null, data);
        });
    });
    req.on('error', function (e) {
        console.log(e);
        callback('-1');
    });
    req.write(data);
    req.end();
}