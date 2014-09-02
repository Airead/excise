var assert = require('assert');
var redis = require('redis');

describe('Strings', function () {
    var client;
    var key = 'someKey';
    var val = 'hello world';
    beforeEach(function (done) {
        client = redis.createClient();

        client.on('connect', function() {
            client.del(key, done);
        });
    });

    it('get empty is null', function (done) {
        var args = [key];
        client.get(args, function (err, data) {
            console.log(arguments);
            assert(err === null);
            assert(data === null);
            done();
        });
    });

    it('set string', function (done) {
        var args = [key, val];
        client.set(args, function (err, data) {
            console.log(arguments);
            assert(err === null);
            done();
        });
    });
});
