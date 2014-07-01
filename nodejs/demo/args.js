/**
 * Created by airead on 14-6-20.
 */
function studyArgs() {
    console.log(arguments);
}

var a = [1,2,3,4];

console.log('apply');
studyArgs.apply(this, a);

console.log('call');
studyArgs.call(this, a);
