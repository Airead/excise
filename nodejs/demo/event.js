var EventEmitter = require('events').EventEmitter;
var event = new EventEmitter();

event.on('some_event', function() {
    console.log('some_event occured.');
});

event.on('point', function () {
    console.log('. ');
    print_p();
});

setTimeout(function () {
    event.emit('some_event');
}, 1000);

var print_p = function () {
    setTimeout(function () {
        event.emit('point');
    }, 100);
}

print_p()
