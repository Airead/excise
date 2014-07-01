var csv = require('csv');

var input = '#Welcome\n"1","2","3","4"\n"a","b","c","d"';

csv.parse(input, {comment: '#'}, function (err, output) {
    console.log(output);
});
