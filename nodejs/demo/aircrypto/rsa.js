/**
 * Created by airead on 14-3-27.
 */
var fs = require('fs');
var crypto = require('crypto');
var u = require('ursa');

var priKeyStr = fs.readFileSync('fan.key').toString();
var pubKeyStr = fs.readFileSync('fan.pem').toString();

console.log('----rsaTest()----');
var sig = rsaTest();
ursaDecrypt(sig);

function ursaDecrypt(sig) {
    var pubKey = u.createPublicKey(pubKeyStr);

    var data = pubKey.publicDecrypt(sig, 'hex', 'hex');
    console.log(data);
}

function rsaTest() {
    var content = 'AireadFan';
    console.log('content: [%s]', content);

    var sign = crypto.createSign('md5WithRSAEncryption');
    sign.update(new Buffer(content, 'utf8'));
    var sig = sign.sign(priKeyStr, 'hex');
    console.log('sig: ', sig);

    var verify = crypto.createVerify('md5WithRSAEncryption');
    verify.update(new Buffer(content, 'utf8'));
    var ret = verify.verify(pubKeyStr, sig, 'hex');
    console.log('ret: ', ret);

    return sig;
}