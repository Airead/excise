/**
 * Created by airead on 14-1-6.
 */
var util = require('util');

var START_TIME = new Date();
var str = util.format('%s-%d-%s %s:%s:%s',
    START_TIME.getFullYear(), START_TIME.getMonth() + 1, START_TIME.getDate(),
    START_TIME.getHours(), START_TIME.getMinutes(), START_TIME.getSeconds());

console.log(str);
