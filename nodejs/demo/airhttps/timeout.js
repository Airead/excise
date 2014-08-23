/**
 * Created by airead on 14-7-29.
 */
var https = require('https');

function httpsGet(url, callback) {
    https.get(url, function (_res) {
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
    }).on('error', function (error) {
        console.log('connect failed', url, error);
        callback('-1');
    });
}

var url = 'https://112.124.0.158';
var start = Date.now();
httpsGet(url, function (err, data) {
    console.log('cost %ss', Date.now() - start);
    if (err) {
        console.log('error: ', err);
        return;
    }
    console.log('receive data: ', data);
});