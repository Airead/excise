var EventEmitter = require('events').EventEmitter;
var event = new EventEmitter();

var print_p = function () {
    console.log('. ');
    setTimeout(function () {
        event.emit('point');
    }, 100);
}

event.on('some_event', function() {
    console.log('some_event occured.');
    console.log('remove print_p');
    event.removeListener('point', print_p);
});

event.on('point', print_p);

setTimeout(function () {
    event.emit('some_event');
}, 1000);

print_p()
