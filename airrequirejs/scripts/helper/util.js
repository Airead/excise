define([], function () {
    return {
        sayHello: function (name) {
            name = name || 'world';
            console.log('say', name);
        }
    };
});