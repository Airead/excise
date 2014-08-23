/**
 * Created by airead on 14-8-15.
 */
var mongoose = require('mongoose');

var conn = mongoose.createConnection('mongodb://localhost/four_game');

var accountSchema = mongoose.Schema({
    _id: Number
});

var Account = conn.model('account', accountSchema);

Account.find({}, function (err, docs) {
    if (err) {
        console.log('error: ', err);
        return;
    }
    console.log('docs: ', docs);
    conn.close();
});

console.log('before on open');
conn.on('open', function () {
    console.log('on open');
});
console.log('after on open');
