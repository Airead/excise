//readfilesync.js

var fs = require('fs');
var data = fs.readFileSync('readfilesync.js', 'utf-8');
console.log(data);
console.log('====end.');
