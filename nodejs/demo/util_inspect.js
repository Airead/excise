/**
 * @file util_inspect.js
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/11/24 16:56:54
 */

var util = require('util');

function Person() {
    this.name = 'byvoid';
    this.toString = function () {
        return this.name;
    };
}

var obj = new Person();

console.log(util.inspect(obj));
console.log(util.inspect(obj, true));
