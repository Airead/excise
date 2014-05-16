/**
 * Created by airead on 14-4-26.
 */

var A = 'Airead Fan';

var variableStr = 'a';

var reg = new RegExp(variableStr, 'g');

console.log('origin str: ', A);
console.log('replace   : ', A.replace(reg, '|'));