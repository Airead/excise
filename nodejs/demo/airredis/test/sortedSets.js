/**
 * Created by airead on 14-8-7.
 */
var redis = require('redis');
var assert = require("assert");

function isType(obj, type) {
    var typestr = '[object ' + type + ']';
    return Object.prototype.toString.call(obj) === typestr;
}

describe('Sorted Sets', function () {
    var client = null;
    var key = 'sortedSets';
    before(function (done) {
        client = redis.createClient();
        client.on('ready', function () {
            done()
        });

        client.on("error", function (err) {
            console.log("error event - " + client.host + ":" + client.port + " - " + err);
        });
    });

    after(function (done) {
        client.on('end', function () {
            done()
        });
        client.quit();
    });

    describe('ZRANGEBYSCORE', function () {
        it('empty record', function (done) {
            client.zrangebyscore(key, 1, 1, function (err, replies) {
                assert(!err);
                assert(isType(replies, 'Array'));
                assert(replies.length === 0);
                done()
            });
        });
    });

    describe('ZSCORE', function () {
        it('empty record', function (done) {
            client.zscore(key, 'noexist', function (err, replies) {
                assert(!err);
                assert(isType(replies, 'Null'));
                done()
            });
        });
    })
});