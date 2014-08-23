/**
 * Created by airead on 14-7-28.
 */
var soap = require('soap');
var url = 'http://stage-api.eg.gashplus.com/CP_Module/checkorder.asmx?wsdl';
var args = {data: 'hello'};
soap.createClient(url, function (err, client) {
    if (err) {
        console.log('create client error', err);
        return;
    }
    client.getResponseResult(args, function (err, result) {
        if (err) {
            console.log('error: ', err);
            return;
        }
        console.log(result);
    });
});