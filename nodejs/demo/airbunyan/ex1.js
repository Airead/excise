/**
 * Created by airead on 14-6-13.
 */
var bunyan = require('bunyan');
var log = bunyan.createLogger({name: 'myapp'});
log.info('hi');