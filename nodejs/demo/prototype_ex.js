/**
 * Created by airead on 14-5-16.
 */
var eventEmitter = require('events').EventEmitter;


function print_t(msg) {
    console.log(msg + ' //', eval(msg));
}

function hr() {
    console.log('------------');
}

function A() {}
function B() {}

var a = new A();
console.log('a = A()');
print_t('a.constructor == A');
print_t('a.constructor.prototype == A.prototype');
print_t('a instanceof A');

hr();
var b = {one: 1, two: 2};
console.log('b = {one: 1, two: 2};');
console.log('b.prototype');

A.prototype = b;
console.log('A.prototype = b;');

var c = new A();
console.log('c = new A();');
print_t('c instanceof A');
print_t('Object.getPrototypeOf(c)');
print_t('Object.getPrototypeOf(c) == A.prototype');
console.log();

print_t('c.one');
print_t('c.two');

print_t('c.constructor == A');
print_t('c.constructor.prototype == A.prototype');
print_t('c.__proto__ == A.prototype');
console.log();

print_t('c.constructor == b');
print_t('c.constructor.prototype == b.prototype');
console.log();

print_t('c.constructor == b.constructor');
print_t('c.constructor.prototype == b.constructor.prototype');
console.log();

hr();
var d = new B();
console.log('d = new B()');
print_t('d.constructor.prototype == B.prototype');
A.prototype = d;
console.log('A.prototype = d;');

var e = new A();
console.log('e = new A()');
print_t('e.constructor');
print_t('e instanceof A');
console.log();

print_t('e.constructor == A');
print_t('e.constructor.prototype == A.prototype');
print_t('e.__proto__.constructor == B');
console.log();

print_t('e.constructor == B');
console.log();

hr();
A.prototype = B.prototype;
console.log('A.prototype = B.prototype;');
var f = new A();
console.log('f = new A();');
print_t('f instanceof A');
print_t('Object.getPrototypeOf(f) == A.prototype');
print_t('A.prototype == B.prototype');
print_t('f.constructor == A');
print_t('f.constructor == B');
print_t('f.constructor.prototype == B.prototype');
print_t('f.constructor.prototype == A.prototype');