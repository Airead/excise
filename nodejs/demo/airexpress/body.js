var express = require('express');
var bodyParser = require('body-parser');

var app = express();

// see https://github.com/expressjs/body-parser
// 添加 body-parser 中间件就可以了
app.use(bodyParser.urlencoded({extended: false}));
app.use(bodyParser.json());

app.post('/', function (req, res) {
    console.log('req.body', req.body);
    res.send({airead: 'fan'});
});

app.listen(8888);

//  shell
//
// $ curl -d'fan=airead' localhost:8888
// {"airead":"fan"}%