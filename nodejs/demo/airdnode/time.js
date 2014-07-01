var dnode = require('dnode');

var d = dnode.connect(53870);
d.on('remote', function (remote) {
    remote.time_now(function (t) {
        console.log('time = ' + t);
        d.end();
    });
});