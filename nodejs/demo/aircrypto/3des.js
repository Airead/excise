/**
 * Created by airead on 14-3-20.
 */
var assert = require('assert');
var crypto = require('crypto');

function test_des(param) {
    var key = new Buffer(param.key);
    var iv = new Buffer(param.iv ? param.iv : 0)
    var plaintext = param.plaintext
    var alg = param.alg
    var autoPad = param.autoPad

    //encrypt
    var cipher = crypto.createCipheriv(alg, key, iv);
    cipher.setAutoPadding(autoPad)  //default true
    var ciph = cipher.update(plaintext, 'utf8', 'hex');
    ciph += cipher.final('hex');
    console.log(alg, ciph)

    //decrypt
    var decipher = crypto.createDecipheriv(alg, key, iv);
    cipher.setAutoPadding(autoPad)
    var txt = decipher.update(ciph, 'hex', 'utf8');
    txt += decipher.final('utf8');
    assert.equal(txt, plaintext, 'fail');
}

function testDecrypt(param) {
    var key = new Buffer(param.key);
    var iv = new Buffer(param.iv ? param.iv : 0);
    var plaintext = param.plaintext;
    var alg = param.alg;
    var decipher = crypto.createDecipheriv(alg, key, iv);

    var txt = decipher.update(plaintext, 'base64', 'utf8');
    txt += decipher.final('utf8');
    console.log(JSON.parse(txt));
}

test_des({
    alg: 'des-ecb',
    autoPad: true,
    key: '01234567',
    plaintext: '1234567812345678',
    iv: null
})

test_des({
    alg: 'des-cbc',
    autoPad: true,
    key: '01234567',
    plaintext: '1234567812345678',
    iv: '12345678'
})

test_des({
    alg: 'des-ede3',    //3des-ecb
    autoPad: true,
    key: '0123456789abcd0123456789',
    plaintext: '1234567812345678',
    iv: null
})

test_des({
    alg: 'des-ede3-cbc',    //3des-cbc
    autoPad: true,
    key: '0123456789abcd0123456789',
    plaintext: '1234567812345678',
    iv: '12345678'
})

testDecrypt({
    alg: 'des-ede3',
    autoPad: true,
    key: '5mv85Qa2Yx1Kg1flBhhEfe3d',
    plaintext: 'PUCJO3fzQZAZurLW/3phf5mHgfx688lECDyJe3/ljmfLsxCZc5gX8dtEw0eRd+o+e0GLMarY+TjN5mwFY4S8aZZ5GFPxgbxj50LXZDuQ7sQIQF+y50Qg2wVpUYJWCJ3U7mkGwlvbht0vOdhIDZDGzEsgJuc8U4zrGbqy1v96YX8f0kLh7PVbbAnmDIniAVFinLsHcyyTHF+iT5+3798SoGwdsCGnoduJ12iTcccHQ0IkAA0gFDh1i763XAIO+vWcs4KXKfA5WJJT3C/nOItAQIoq7a4qigKedGdN9fxJebllzfnkVZe0TtMnEIqyjx1Er0xTLFO4KTs=',
    iv: null
})