/**
 * Created by airead on 14-4-18.
 */
var kue = require('kue');
var jobs = kue.createQueue();

kue.app.listen(3000);

function newJob(name) {
    var job = jobs.create('new_job', {
        name: name
    });

    job.on('complete', function () {
        console.log('Job', job.id, 'with name', job.data.name, 'is done');
    });
    job.on('failed', function () {
        console.log('Job', job.id, 'with name', job.data.name, 'has failed');
    });

    job.save();
}

jobs.process('new_job', 1, function (job, done) {
    setTimeout(function () {
        console.log('job', job.id, 'is done, data: ', job.data);
        done && done();
    }, 9000);
});

setInterval(function () {
    newJob('sendMail');
}, 10000);