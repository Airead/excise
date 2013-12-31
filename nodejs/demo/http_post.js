/**
 * Created by airead on 13-12-27.
 */
var http=require('http');
var qs=require('querystring');

var post_data={a:123,time:new Date().getTime()};//这是需要提交的数据
var content=qs.stringify(post_data);

console.log(process.argv);
if (process.argv.length < 5) {
    console.log('usage: node ', process.argv[1], ' <host> <port> <path>');
    return;
}
var host = process.argv[2];
var port = process.argv[3];
var path = process.argv[4];

var options = {
  host: host,
  port: port,
  path: path,
  method: 'POST',
  headers:{
  'Content-Type':'application/x-www-form-urlencoded',
  'Content-Length':content.length
  }
};
console.log("post options:\n",options);
console.log("content:",content);
console.log("\n");

var req = http.request(options, function(res) {
  console.log("statusCode: ", res.statusCode);
  console.log("headers: ", res.headers);
  var _data='';
  res.on('data', function(chunk){
     _data += chunk;
  });
  res.on('end', function(){
     console.log("\n--->>\nresult:",_data)
   });
});

req.write(content);
req.end();