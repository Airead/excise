var crypto = require('crypto');
op = {
    "mid": "M1000390",
    "cid": "C003900000641",
    "key1": "WpAyafFrEN4uywoTrBzUUij6ibmuNSuq",
    "key2": "1VdLRwETWUg=",
    "password": "w45q94tawke"
};

data = 'hello';
des3Encrypt(data, op.key1, op.key2);

function des3Encrypt(data, key, iv) {
    var keyb = new Buffer(key, 'base64');
    var ivb = new Buffer(iv ? iv : 0, 'base64');
    var alg = 'des3';

    var cipher = crypto.createCipheriv(alg, keyb, ivb);
    cipher.setAutoPadding(true);
    var ciph = cipher.update(data, 'utf8', 'hex');
    ciph += cipher.final('hex');

    return ciph;
}