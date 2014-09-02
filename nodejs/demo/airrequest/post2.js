// test with python httpbin

var request = require('request');

describe('post', function () {
    var url = 'http://127.0.0.1:8000/post';

    it('post raw data', function (done) {
        var options = {
            body: "hello body"
        };
        request.post(url, options, function (err, res, body) {
            console.log(JSON.parse(body));
            done();
        });
    });
    it('post obj data', function (done) {
        var options = {
            form: {key: "val"}
        };
        request.post(url, options, function (err, res, body) {
            console.log(JSON.parse(body));
            done();
        });
    });
});
