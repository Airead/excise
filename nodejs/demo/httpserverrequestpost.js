/**
 * @file httpserverrequestpost.js
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/11/24 17:59:23
 */

var http = require('http');
var querystring = require('querystring');
var util = require('util');

http.createServer(function (req, res) {
    var post = '';

    req.on('data', function (chunk) {
        post += chunk;
    });

    req.on('end', function() {
        post = querystring.parse(post);
        res.end(util.inspect(post));
    });
}).listen(3000);

console.log("HTTP server is listening at port 3000.");
