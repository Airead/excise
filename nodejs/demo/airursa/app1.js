/**
 * Created by airead on 14-1-2.
 */
var fs = require('fs');
var ursa = require('ursa');

var msg = 'Hello AireadFan';
console.log('message: ' + msg);

var privateKeyContent = fs.readFileSync('./id_rsa');
console.log('private Buffer: ');
console.log(privateKeyContent);

var privateKey = ursa.createPrivateKey(privateKeyContent);

