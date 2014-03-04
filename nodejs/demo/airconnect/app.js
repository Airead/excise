/**
 * Created by airead on 14-1-7.
 */
var connect = require('connect');
var app = connect();

app.use(connect.logger('dev'))
    .use(function () {
        console.log('req start');
    })
    .use(function (req, res) {
        res.end('hello world\n');
        console.log('res.headerSent: ', res.headerSent);
    });

app.listen(3000);
