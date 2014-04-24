/**
 * Created by airead on 14-4-24.
 */

setInterval(function () {
    //console.log('ram: ', process.memoryUsage());
    require('./leakArray');
    delete require.cache[ require.resolve('././leakArray')];
}, 100);
