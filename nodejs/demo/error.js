/**
 * Created by airead on 14-1-4.
 */
var events = require('events');

var emitter = new events.EventEmitter();
var err = new Error('hello');

emitter.emit('error');

process.on('uncaughtException', function(err) {
    console.log('hello Exception');
});