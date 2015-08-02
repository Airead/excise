var cp = require("child_process");

cp.exec("node -v", function(err, data) {
	console.log(data);
});