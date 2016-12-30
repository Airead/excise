requirejs.config({
    baseUrl: 'scripts',
});

requirejs(['helper/util'], function (util) {
    console.log('arguments', arguments);
    util.sayHello();
    util.sayHello('airead');
});