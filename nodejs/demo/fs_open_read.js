/**
 * @file fs_open_read.js
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/11/24 17:33:22
 */

var fs = require('fs');

fs.open('content.txt', 'r', function(err, fd) {
    if (err) {
        console.error(err);
        return;
    }

    var buf = new Buffer(8);
    fs.read(fd, buf, 0, 8, null, function(err, bytesRead, buffer) {
        if (err) {
            console.error(err);
            return;
        }

        console.log('bytesRead: ' + bytesRead);
        console.log(buffer);
    })
});
