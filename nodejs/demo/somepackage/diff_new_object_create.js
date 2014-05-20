/**
 * Created by airead on 14-5-19.
 */
/**
 * Created by airead on 14-4-23.
 */
var eventEmitter = require('events').EventEmitter;

function Event1() {
}

Event1.prototype = new eventEmitter();
console.log('Event1.prototype', Event1.prototype);

var e1 = new Event1();
e1.on('hello', function () {
    console.log('e1 hello');
});

console.log('Event1.prototype', Event1.prototype);

var e2 = new Event1();
e2.on('hello', function () {
    console.log('e2 hello');
});
console.log('Event1.prototype', Event1.prototype);


function Event2() {
}

Event2.prototype = Object.create(eventEmitter.prototype);
console.log('Event2.prototype', Event2.prototype);

var f1 = new Event2();
f1.on('hello', function () {
    console.log('f1 hello');
});
console.log('Event2.prototype', Event2.prototype);

var f2 = new Event2();
f2.on('hello', function () {
    console.log('f2 hello');
});
console.log('Event2.prototype', Event2.prototype);

e1.emit('hello');
f1.emit('hello');