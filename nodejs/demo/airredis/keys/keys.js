/**
 * Created by airead on 14-6-10.
 */
var redis = require('redis');

client = redis.createClient();

var key = 'inTimeCost'

var funcs = [
    function test_keys(cb) {
        client.keys(key, function (err, data) {
            console.log(key, arguments);
            console.log(key, data);
            cb();
        });
    },

    function test_ttl(cb) {
        client.ttl(key, function (err, data) {
            console.log(key, arguments);
            console.log(key, data);
            cb();
        });
    },

    function test_expire(cb) {
        var args = [key, 10];
        client.expire(args, function () {
            console.log(args, arguments);
            cb();
        });
    }
];

function runTest(funcs) {
    var total = funcs.length;
    var index = 0;

    (function _run(funcs) {
        if (index < total) {
            var func = funcs[index];
            index++;

            console.log('-----run %s-----', func.name);
            func(function () {
                _run(funcs);
            });
        }
    })(funcs);
}

runTest(funcs);