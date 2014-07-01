/**
 * Created by airead on 14-6-20.
 */
var fs = require('fs');

var content = fs.readFileSync('multipartyFormData.txt').toString();

// console.log('content: ', content);
var form = parse(content);
console.log(form);


function parse(data) {
    var cur = 0;
    var form = {};

    cur = getOneKey(data, cur);
    while (cur >= 0) {
        cur = getOneKey(data, cur);
    }

    return form;

    function getOneKey(data, start) {
        // return end pos
        var ignoreChars = ['\r', '\n', '"'];
        var searchStr = 'Content-Disposition: form-data; name="';
        var pos = data.indexOf(searchStr, start);

        if (pos < 0) {
            return -1; // return -1 for end
        }

        var keyStart = pos + searchStr.length;

        var tmpdata = data.slice(keyStart);
        var keyEnd = tmpdata.indexOf('"');
        var key = tmpdata.slice(0, keyEnd);

        var valParseStart = keyStart + keyEnd;
        searchStr = '-----';
        var valEnd = data.indexOf(searchStr, valParseStart);
        tmpdata = data.slice(valParseStart, valEnd);
        var val = '';
        for (var i = 0; i < tmpdata.length; i++) {
            var c = tmpdata[i];
            if (ignoreChars.indexOf(c) < 0) {
                val += c;
            }
        }

        console.log('key: ', key, 'val: ', val);
        form[key] = val;
        return valEnd;
    }
}

