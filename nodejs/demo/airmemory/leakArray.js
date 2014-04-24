/**
 * Created by airead on 14-4-24.
 */
var leakArray = [];
exports.leak = function () {
  leakArray.push("leak" + Math.random());
};