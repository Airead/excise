var fs = require('fs');
var libxmljs = require("libxmljs");
var xml =  fs.readFileSync('sample.xml').toString();


var xmlDoc = libxmljs.parseXml(xml);

console.log(xml);
var accountId = xmlDoc.get('//cost');
if (accountId) {
    console.log(accountId.text());
} else {
    console.log('not found!');
}
