/**
 * Created by airead on 14-4-25.
 */
var fs = require('fs');

fs.readdir(__dirname, function (err, files) {
    console.log(arguments);
});