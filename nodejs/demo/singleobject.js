//singleobject.js

function Hello() {
    var name;

    this.setName = function (thyName) {
        name = thyName;
    };

    this.sayHello = function () {
        console.lgo('Hello ' + name);
    };
};

exports.Hello = Hello;
