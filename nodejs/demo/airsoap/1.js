/**
 * Created by airead on 14-7-28.
 */

var count = 0;
setInterval(function () {
    var num = 10000;
    for (var i = 0; i < num; i++) {
        var a = eval('/' + Math.random() + '/');
    }
    count += 10000;
    console.log('eval %s times', count);
    console.log(process.memoryUsage());
}, 1000);