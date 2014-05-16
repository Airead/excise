/**
 * Created by airead on 14-4-24.
 */
var fs = require('fs');
var Schema = require('protobuf').Schema;

// "schema" contains all message types defined in buftest.proto|desc.
var schema = new Schema(fs.readFileSync('buftest.desc'));

// The "BufTest" message.
var BufTest = schema['com.chrisdew.buftest.BufTest'];

var ob = { num: 42 };
ob.payload = new Buffer("Hello World");

var proto = BufTest.serialize(ob);
console.log('proto.length:', proto.length);

var outOb = BufTest.parse(proto);
console.log('unserialised:', JSON.stringify(outOb));

var payload = new Buffer(outOb.payload);
console.log(payload);