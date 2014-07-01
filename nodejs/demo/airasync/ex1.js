/**
 * Created by airead on 14-6-20.
 */
var async = require('async');

var arr = [1, 2,3,4,5,6,10];
async.eachSeries(arr, function (num, callback) {
    setTimeout(function () {
        console.log('num: ', num);
        //if (num !== 3) {
            callback();
        //}
    }, 1000)
}, function (err) {
    console.log('err: ', err);
});