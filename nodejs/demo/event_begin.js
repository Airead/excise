/**
 * @file event_begin.js
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/11/24 17:02:23
 */

var events = require('events');

var emitter = new events.EventEmitter();

emitter.on('someEvent', function(arg1, arg2) {
    console.log('listener1', arg1, arg2);
});

emitter.on('someEvent', function(arg1, arg2) {
    console.log('listener2', arg1, arg2);
});

emitter.emit('someEvent', 'byvoid', 1991);
