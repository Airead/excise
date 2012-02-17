window.addEventListener("load", eventWindowLoaded, false);
var Debugger = function (message) { };
Debugger.log = function (message) {
    try {
	console.log(message);
    } catch (exception) {
	return ;
    }
}

function eventWindowLoaded () {
    canvasApp();
}

function canvasSupport () {
    return Modernizr.canvas;
}

function canvasApp () {
    if (!canvasSupport()) {
	return ;
    }
    
    var theCanvas = document.getElementById("canvasOne");
    var context = theCanvas.getContext("2d");

    Debugger.log("Drawing Canvas");

    function drawScreen() {
	//background
	context.fillStyle = "#ffffaa";
	context.fillRect(0, 0, 500, 300);

	//text
	context.fillStyle = "#000000";
	context.font = "20px _sans";
	context.textBaseline = "top";
	context.fillText ("Hello World!", 195, 80);

	//image
	var helloWorldImage = new Image();
	helloWorldImage.src = "helloworld.gif";
	helloWorldImage.onload = function () {
	    context.drawImage(helloWorldImage, 160, 130);
	}
	//box
	context.strokeStyle = "#000000";
	context.strokeRect(5, 5, 490, 290);
    }

    drawScreen();
}

