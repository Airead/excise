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

var publicKeyContent = fs.readFileSync('./pub.pem');
console.log('publick Buffer: ');
console.log(publicKeyContent);

var privateKey = ursa.createPrivateKey(privateKeyContent);
var publicKey = ursa.createPublicKey(publicKeyContent);

var encryptContent = privateKey.privateEncrypt(msg, 'utf8', 'base64');
console.log('encryptContent', encryptContent);

var decryptContent = publicKey.publicDecrypt(encryptContent, 'base64', 'utf8');
console.log('decryptContent', decryptContent);
