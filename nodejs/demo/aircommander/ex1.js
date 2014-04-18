/**
 * Created by airead on 14-4-18.
 */
/**
 * Module dependencies.
 */

var program = require('commander');

program
    .version('0.0.1')
    .option('-p, --peppers', 'Add peppers')
    .option('-P, --pineapple', 'Add pineapple')
    .option('-b, --bbq', 'Add bbq sauce')
    .option('-c, --cheese [type]', 'Add the specified type of cheese [marble]', 'marble')

program
    .command('setup')
    .description('run remote setup commands')
    .action(function () {
        console.log('setup');
    });

program.parse(process.argv);

console.log('you ordered a pizza with:');
console.log('program.peppers: ', program.peppers);
if (program.peppers) console.log('  - peppers');
if (program.pineapple) console.log('  - pineapple');
if (program.bbq) console.log('  - bbq');
console.log('  - %s cheese', program.cheese);
console.log('program args: ', program.args);