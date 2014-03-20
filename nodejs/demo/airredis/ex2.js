var redis = require('redis');

var client = redis.createClient();
client.on('error', function (err) {
    console.log(err);
});

client.on('connect', function () {
    console.log('connect...');
    client['HGETALL'](['bigWheelGofld'], function (err, records) {
        if (err) {
            console.log(err);
            return;
        }
        console.log('type: ', typeof(records));
        console.log(records);
        console.log(typeof(null));
    });
});