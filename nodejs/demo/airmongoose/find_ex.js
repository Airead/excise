/**
 * Created by airead on 13-12-13.
 */
var mongoose = require('mongoose');
mongoose.connect('mongodb://localhost/mongoose_test');

var db = mongoose.connection;
db.on('error', console.error.bind(console, 'connection error:'));

var messageDefine = {
    "date":{
		"type":"Date",
		"default":0
	}
};

db.once('open', function () {
    console.log('mongo opened');
    var messageSchema = mongoose.Schema(messageDefine);
    var messageDoc = mongoose.model('messages', messageSchema);

    messageDoc.find({date: {$gte: new Date(1385827200000), $lte: new Date(1386914743730)}}, function(err, messages) {
        if (err) {
            console.log(err);
            return;
        }
        console.log('message total: ', messages.length);
    });

    messageDoc.findOne({date: 1}, function (err, d) {
        console.log('d: ', d);
    });
});