/**
 * @file event_error.js
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/11/24 17:18:54
 */

var events = require('events');

var emitter = new events.EventEmitter();

emitter.emit('error');
