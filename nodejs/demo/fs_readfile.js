/**
 * @file fs_readfile.js
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/11/24 17:22:24
 */

var fs = require('fs');

function readfileCallback (err, data) {
    console.log('=================================');
    if (err) {
        console.error(err);
    } else {
        console.log(data);
    }
}

fs.readFile('content.txt', readfileCallback);

fs.readFile('content.txt', 'utf-8', readfileCallback);

fs.readFile('no_exist.txt', readfileCallback);
