/**
 * Created by airead on 14-1-9.
 */
var mongoose = require('mongoose');
mongoose.connect('mongodb://localhost/AIREAD_TEST');

var db = mongoose.connection;
db.on('error', console.error.bind(console, 'connection error:'));

db.once('open', function () {
    console.log('open');
});