"use strict";

window.addEventListener("load", main, false);

// config
var WINDOW_WIDTH = 400;
var WINDOW_HEIGHT = 400;

var SWEEPER_SCALE = 100;
var NUM_SWEEPERS = 30;
var MINE_SCALE = 2;
var NUM_MINES = 40;

var CROSSOVER_RATE = 0.75;
var MUTATION_RATE = 0.4;
var POP_SIZE = 40;

// MUST be a multiple of 2
var NUM_BEST_TO_ADD = 2;

var EPSILON = 0.000001;

var PI = 3.1415926535897;

var COLOR = {
    white: 0xFFFFFF,
    black: 0x000000,
    gray: 0x808080,
    red: 0xFF0000
};

var keyCode = null;

var stage = null;

function main() {
    var gameInfo = {};
    stage = new PIXI.Stage(0xEEEEEE);
    var renderer = PIXI.autoDetectRenderer(WINDOW_WIDTH, WINDOW_HEIGHT);
    window.renderer = renderer;

    document.body.appendChild(renderer.view);

    var controller = new Controller();
    gameInfo.controller = controller;
    controller.render();
    controller.show();

    registerKeyEvent();

    requestAnimFrame(animate);
    function animate() {
        loop(gameInfo);

        renderer.render(stage);
        requestAnimFrame(animate);
    }
}

function loop(gameInfo) {
    var char = keyCode;
    var result = {};
    keyCode = null;

    var ctl = gameInfo.controller;

    ctl.render();

    switch (char) {
    case ' ':
        console.log('into space process');
        break;
    case 'D':
        debugger;
        break;
    case 'R':
        console.log('reset');
        break;
    case 'N':
        break;
    }
}

function registerKeyEvent() {
    document.addEventListener('keydown', function(event) {
        console.log('key down', event);
        var char = String.fromCharCode(event.keyCode);
        console.log('press key [%s], keyCode', char, event.keyCode);
        keyCode = char;
    });
}

/*
 class Controller
*/
function Controller() {
    var i;

    this.numSweepers = NUM_SWEEPERS;
    this.ga = null;
    this.fastRender = false;
    this.ticks = 0;
    this.numMines = NUM_MINES;
    this.generation = 0;
    this.width = WINDOW_WIDTH;
    this.height = WINDOW_HEIGHT;

    this.pen = new PIXI.Graphics();
    this.generationText = new PIXI.Text("");

    this.sweepers = [];
    this.mines = [];

    var tmp;
    // create mine sweepers
    for (i = 0; i < this.numSweepers; i++) {
        tmp = new Mine();
        tmp.addToStage(stage);
        this.sweepers.push(tmp);
    }

    // create mine mines
    for (i = 0; i < this.numMines; i++) {
        tmp = new Mine();
        tmp.addToStage(stage);
        this.mines.push(tmp);
    }
}

Controller.prototype.show = function () {
    stage.addChild(this.generationText);
};

Controller.prototype.render = function () {
    var i;
    var gt = 'Generation: ' + this.generation;
    this.generationText.setText(gt);

    if (!this.fastRender) {
        // render the sweepers
        for (i = 0; i < this.sweepers.length; i++) {
            this.sweepers[i].render();
        }

        for (i = 0; i < this.mines.length; i++) {
            this.mines[i].render();
        }
    } else {

    }
};


/*
 class Minesweeper
*/
function Minesweeper() {
    this.rotation = Math.random() * Math.PI * 2;
    this.lTrack = 0.16;
    this.rTrack = 0.16;
    this.fitness = 0;
    this.scale = 1;
    this.closestMine = 0;

    this.shape = this.scalePath(10);

    this.position = new PIXI.Point(Math.random() * WINDOW_WIDTH, Math.random() * WINDOW_HEIGHT);

    this.container = new PIXI.DisplayObjectContainer();
    this.pen = new PIXI.Graphics();
    this.container.addChild(this.pen);

    // draw sweeper Shape
    this.genShape();

    // this.renderTexture = new PIXI.RenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
    this.renderTexture = new PIXI.RenderTexture(800, 800);
    this.renderTexture.render(this.container);
    this.sprite = new PIXI.Sprite(this.renderTexture);
}

Minesweeper.prototype.scalePath = (function () {
    var scaled = false;
    var paths = [
        new PIXI.Point(-1, -1),
        new PIXI.Point(-1, 1),
        new PIXI.Point(-0.5, 1),
        new PIXI.Point(-0.5, -1),

        new PIXI.Point(0.5, -1),
        new PIXI.Point(1, -1),
        new PIXI.Point(1, 1),
        new PIXI.Point(0.5, 1),

        new PIXI.Point(-0.5, -0.5),
        new PIXI.Point(0.5, -0.5),

        new PIXI.Point(-0.5, 0.5),
        new PIXI.Point(-0.25, 0.5),
        new PIXI.Point(-0.25, 1.75),
        new PIXI.Point(0.25, 1.75),
        new PIXI.Point(0.25, 0.5),
        new PIXI.Point(0.5, 0.5)
    ];

    function callOnce(scale) {
        if (!scaled) {
            scaled = true;
            for (var i = 0; i < paths.length; i++) {
                paths[i].add(new PIXI.Point(1, 1));
                paths[i].multiplyScalar(scale);
            }
        }

        return paths;
    }

    return callOnce;
})();

Minesweeper.prototype.genShape = function () {
    var i;
    var s = this.shape;
    var pen = this.pen;

    pen.lineStyle(1, 0x000000);

    // draw left track
    pen.moveTo(s[0].x, s[0].y);
    for (i = 1; i < 4; i++) {
        pen.lineTo(s[i].x, s[i].y);
    }
    pen.lineTo(s[0].x, s[0].y);

    // draw right track
    pen.moveTo(s[4].x, s[4].y);
    for (i = 5; i < 8; i++) {
        pen.lineTo(s[i].x, s[i].y);
    }
    pen.lineTo(s[4].x, s[4].y);

    pen.moveTo(s[8].x, s[8].y);
    pen.lineTo(s[9].x, s[9].y);

    pen.moveTo(s[10].x, s[10].y);
    for (i = 11; i < 16; i++) {
        pen.lineTo(s[i].x, s[i].y);
    }

};

Minesweeper.prototype.reset = function () {
    this.position = PIXI.Point(Math.random() * WINDOW_WIDTH, Math.random() * WINDOW_HEIGHT);
    this.fitness = 0;
    this.rotation = Math.random() * Math.PI * 2;
};

Minesweeper.prototype.addToStage = function (stage) {
    stage.addChild(this.sprite);
};

Minesweeper.prototype.updateSprite = function () {
    this.sprite.position = this.position;
    this.sprite.rotation = this.rotation;
    this.sprite.scale.x = this.sprite.scale.y = this.scale;
};

Minesweeper.prototype.render = function () {
    this.updateSprite();
};

// Minesweeper end here

/*
 class Mine
*/
function Mine() {
    this.rotation = Math.random() * Math.PI * 2;
    this.lTrack = 0.16;
    this.rTrack = 0.16;
    this.fitness = 0;
    this.scale = 1;
    this.closestMine = 0;

    this.shape = this.scalePath(10);

    this.position = new PIXI.Point(Math.random() * WINDOW_WIDTH, Math.random() * WINDOW_HEIGHT);

    this.container = new PIXI.DisplayObjectContainer();
    this.pen = new PIXI.Graphics();
    this.container.addChild(this.pen);

    // draw sweeper Shape
    this.genShape();

    // this.renderTexture = new PIXI.RenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
    this.renderTexture = new PIXI.RenderTexture(800, 800);
    this.renderTexture.render(this.container);
    this.sprite = new PIXI.Sprite(this.renderTexture);
}

Mine.prototype.scalePath = (function () {
    var scaled = false;
    var paths = [
        new PIXI.Point(-1, -1),
        new PIXI.Point(-1, 1),
        new PIXI.Point(1, 1),
        new PIXI.Point(1, -1)
    ];

    function callOnce(scale) {
        if (!scaled) {
            scaled = true;
            for (var i = 0; i < paths.length; i++) {
                paths[i].add(new PIXI.Point(1, 1));
                paths[i].multiplyScalar(scale);
            }
        }

        return paths;
    }

    return callOnce;
})();

Mine.prototype.genShape = function () {
    var i;
    var s = this.shape;
    var pen = this.pen;

    pen.lineStyle(1, 0x00FF00);

    // draw left track
    pen.moveTo(s[0].x, s[0].y);
    for (i = 1; i < 4; i++) {
        pen.lineTo(s[i].x, s[i].y);
    }
    pen.lineTo(s[0].x, s[0].y);
};

Mine.prototype.reset = function () {
    this.position = PIXI.Point(Math.random() * WINDOW_WIDTH, Math.random() * WINDOW_HEIGHT);
    this.fitness = 0;
    this.rotation = Math.random() * Math.PI * 2;
};

Mine.prototype.addToStage = function (stage) {
    stage.addChild(this.sprite);
};

Mine.prototype.updateSprite = function () {
    this.sprite.position = this.position;
    this.sprite.rotation = this.rotation;
    this.sprite.scale.x = this.sprite.scale.y = this.scale;
};

Mine.prototype.render = function () {
    this.updateSprite();
};

// Mine end here

// [min, max)
function randInt(min, max) {
    return Math.floor(Math.random() * (max - min) + min);
}
