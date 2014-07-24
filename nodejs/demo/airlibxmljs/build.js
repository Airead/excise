/**
 * Created by airead on 14-7-24.
 */
var libxmljs = require('libxmljs');

var doc = new libxmljs.Document();

doc.node('root')
    .node('child').attr({foo: 'bar'})
    .node('grandchild', 'grandchild content').attr({baz: 'fizbuzz'})
    .parent()
    .parent()
    .node('sibling', 'with content!');

console.log(doc.toString());