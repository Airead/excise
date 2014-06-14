/**
 * Created by airead on 14-6-13.
 */
var debug = require('debug');

function getTime(date) {
    var time = date ? new Date(date) : new Date();
    return time.getFullYear() + '/' + (time.getMonth() + 1) + '/' + time.getDate() + ' ' + ('0' + time.getHours()).slice(-2) + ':' + ('0' + time.getMinutes()).slice(-2) + ':' + ('0' + time.getSeconds()).slice(-2);
}

debug.formatArgs = function () {
  var args = arguments;
  var useColors = this.useColors;
  var name = this.namespace;

  if (useColors) {
    var c = this.color;

    args[0] = '  \u001b[9' + c + 'm' + name + ' '
      + '\u001b[0m'
      + args[0] + '\u001b[3' + c + 'm'
      + ' +' + exports.humanize(this.diff) + '\u001b[0m';
  } else {
    args[0] = getTime()
      + ' ' + name + ' ' + args[0];
  }
  return args;
};

a = debug('a');

console.log(debug.enabled());
a('aaa');

debug.enable('a');
console.log(debug.enabled('a'));
b = debug('a');
a('aaa');
b('bbb');
