/**
 * @file httpserverrequestget.js
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/11/24 17:52:35
 */

var http = require('http');
var url = require('url');
var util = require('util');

http.createServer(function (req, res) {
    res.writeHead(200, {'Content-Type': 'text/plain'});
    res.end(util.inspect(url.parse(req.url, true)));
}).listen(3000);

console.log("HTTP server is listening at port 3000.");
