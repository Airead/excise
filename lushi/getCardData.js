'use strict';

var fs = require('fs');
var request = require('request');
var async = require('async');

var cardMetaData = [];

var post_url = 'http://cha.17173.com/hs/list/async';

async.timesSeries(100, function(i, cb) {
	var form = {
		page: i + 1
	};
	request.post({
		url: post_url,
		formData: form
	}, function(err, res, body) {
		if (err) {
			console.log('get data error: page ', i + 1);
			return cb(err);
		}
		var cards = JSON.parse(body).data;
		console.log('page ', i + 1, cards.length);
		if (cards.length == 0) {
			return cb(404);
		}
		cardMetaData = cardMetaData.concat(cards);
		setTimeout(cb, 0);
	});
}, function(err) {
	if (err) {
		console.log('error: ', err);
	}

	fs.writeFileSync('cardsData.json', JSON.stringify(cardMetaData));
	console.log('write cardsData success');
});