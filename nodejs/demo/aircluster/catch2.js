/**
 * Created by airead on 14-1-4.
 */
function async(callback) {
    process.nextTick(function () {
        throw new Error('Something went wrong');
        callback();
    });
}

try {
    async(function () {
        console.log('It worked!');
    });
} catch(error) {
    console.log('This is never printed.');
}

process.on('uncaughtException', function (err) {
    console.log('Caught exception: ' + err);
});