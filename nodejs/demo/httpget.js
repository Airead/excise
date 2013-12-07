/**
 * @file httpget.js
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/11/24 18:31:42
 */

var http = require('http');

http.get({host: 'www.baidu.com'}, function (res) {
    res.setEncoding('utf8');
    res.on('data', function (data) {
       console.log(data); 
    });
});
