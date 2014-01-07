/**
 * Created by airead on 14-1-4.
 */
var fs = require('fs');
var domain = require('domain');

var d = domain.create();

d.on('error', function (er) {
    console.error('Caught error!', er);
});

d.run(function() {
    process.nextTick(function() {
        setTimeout(function() {
            fs.open('non-existent file', 'r', d.bind(function(er, fd) {
                if (er) throw er;
                // proceed ...
            }));
        }, 100);
    })
});