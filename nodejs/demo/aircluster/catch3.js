/**
 * Created by airead on 14-1-4.
 */
function async () {
    var emitter = new (require('events').EventEmitter)();
    process.nextTick(function () {
        emitter.emit('error', new Error('Something went wrong'));
    });

    return emitter;
}

var event = async();
//event.on('error', function (err) {
//    console.log(err);
//});