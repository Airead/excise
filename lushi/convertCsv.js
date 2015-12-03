var csv = require('csv');

var cards = require('./cards');

var headers = [
    "card_id",
    "card_name",
    "card_set",
    "card_type", // 4 随从, 5 法术, 7 武器
    "class",
    "rarity",
    "cost",
    "atk",
    "health",
    "race",
    "taunt",
    "freeze",
    "windfury",
    "battlecry",
    "stealth",
    "combo",
    "aura",
    "charge",
    "grant_charge",
    "spellpower",
    "silence",
    "enrage",
    "divine_shield",
    "deathrattle",
    "secret",
    "inspire",
    "id",
];

var csvData = [headers];

cards.forEach(function(card) {
	var row = [];
	headers.forEach(function(key) {
		row.push(card[key]);
	});
	csvData.push(row);
});

csv.stringify(csvData, function(err, data) {
	if (err) {
		console.log('err: ', err);
		return;
	}
	console.log(data);
});
