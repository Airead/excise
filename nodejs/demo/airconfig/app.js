var CONFIG = require('config');

var count = 0;

function print() {
    console.log('%s===============', count++);

    console.log('CONFIG.Customer.dbHost: ', CONFIG.Customer.dbHost);
    console.log('CONFIG.Customer.dbPort: ', CONFIG.Customer.dbPort);
    console.log('CONFIG.Customer.dbName: ', CONFIG.Customer.dbName);
}

setInterval(print, 1000);
