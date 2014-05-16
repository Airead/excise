module.exports = function (grunt) {
    grunt.initConfig({
        log: {
            foo: [1, 2, 3],
            bar: 'hello world',
            baz: false
        },
        hello: {
            options: {
                o1: 1,
                o2: 2
            },
            foo: 1,
            bar: 2
        }
    });

    grunt.registerMultiTask('log', 'Log stuff.', function () {
        grunt.log.writeln(this.target + ': ' + this.data);
    });

    grunt.registerTask('hello', 'hello', function () {
        console.log('arguments:', arguments);
        console.log(this);
        console.log(this.options());
        console.log(this.requiresConfig());
        console.log(grunt.config.data[this.name]);
    });
};