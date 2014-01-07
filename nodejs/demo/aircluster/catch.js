/**
 * Created by airead on 14-1-4.
 */
try {
    throw new Error('hello error');
} catch(error) {
    console.log('This is a error: ', error);
}