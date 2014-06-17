/**
 * @overview
 *
 * @author Caesar Chi
 * @blog clonn.blogspot.com
 * @version 2012/02/27
 */

var express = require('express'),
    app = express(),
    port = 1337;

function middleHandler(req, res, next) {
    console.log("execute middle ware");
    next();
}

function middleHandler2(req, res, next) {
    console.log("execute middle ware2");
    next();
}

app.use(function (req, res, next) {
    console.log("first middle ware");
    next();
});

app.use(function (req, res, next) {
    console.log("second middle ware");
    next();
});

app.get('/', middleHandler, middleHandler2, function (req, res) {
    console.log("end middleware function");
    res.send("page render finished");
});

app.listen(port);
console.log('start server');