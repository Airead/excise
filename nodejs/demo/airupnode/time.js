var upnode = require('upnode');

var up = upnode.connect(53870);

setInterval(function () {
    up(function (remote) {
        console.log('up');
        remote.time(function (t) {
            console.log('time = ' + t);
        })
    });
}, 1000);