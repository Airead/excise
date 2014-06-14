/**
 * Created by airead on 14-6-10.
 */
var redis = require('redis');

describe('Keys', function () {
    var client;
    var key = 'someKey';
    var needSet = true;
    beforeEach(function (done) {
        client = redis.createClient();

        client.on('connect', function () {
            if (needSet) {
                needSet = false;
                var args = [key, 'Hello'];
                client.set(args, done);
            } else {
                done();
            }
        })
    });
    describe('keys', function () {
        it('info', function (done) {
            var args = [key];
            client.keys(args, function (err, data) {
                console.log(arguments);
                done();
            })
        });
    });
    describe('ttl', function () {
        it('info', function (done) {
            var args = [key];
            client.ttl(args, function (err, data) {
                console.log(arguments);
                done();
            });
        })
    });
    describe('expire', function () {
        it('info', function (done) {
            var args = [key, 5];
            client.expire(args, function (err, data) {
                console.log(arguments);
                done();
            });
        })
    });
    describe('ttl', function () {
        it('info', function (done) {
            var args = [key];
            client.ttl(args, function (err, data) {
                console.log(arguments);
                done();
            });
        })
    });
});
