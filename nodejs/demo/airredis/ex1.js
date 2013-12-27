/**
 * Created by airead on 13-12-20.
 */
var redis = require('redis');
var client = redis.createClient();

client.on('error', function (err) {
    console.log('Error' + err);
});

client.set('string key', 'string val', redis.print);
client.hmset('hash key', 'hashtest 1', 'some value', redis.print);
client.hmset('hash key', {'hashtest 2': 'some other value'}, redis.print);
client.hkeys('hash key', function (err, replies) {
    console.log(replies.length + 'replies:');
    replies.forEach(function (reply, i) {
        console.log('    ' + i + ': ' + reply);
    });
});

client.keys('*', function (err, replies) {
    console.log(replies.length + 'replies:');
    console.log(replies);
});

client.hgetall('bossBaseAiread_test', function (err, replies) {
    console.log(typeof(replies));
    console.log(replies);
    console.log(replies.result);
});