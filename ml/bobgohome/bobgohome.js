window.addEventListener('load', main, false);

// config
var WINDOW_WIDTH = 450;
var WINDOW_HEIGHT = 300;

var MAP_WIDTH = 15;
var MAP_HEIGHT = 10;

var CROSSOVER_RATE = 0.7;
var MUTATION_RATE = 0.001;

var POP_SIZE = 140;
var CHROMO_LENGTH = 70;
var GENE_LENGTH = 2;

var COLOR = {
    white: 0xFFFFFF,
    black: 0x000000,
    gray: 0x808080,
    red: 0xFF0000
};

var keyCode = null;

function main() {
    var gameInfo = {};
    var stage = new PIXI.Stage(0xFFFFFF);
    var renderer = PIXI.autoDetectRenderer(WINDOW_WIDTH, WINDOW_HEIGHT);

    document.body.appendChild(renderer.view);

    var map = new BobsMap(stage);
    gameInfo.map = map;
    window.map = map;  // for debug

    map.Render();

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
    keyCode = null;

    switch (char) {
    case ' ':
        console.log('into space process');
        gameInfo.map.memoryRender();
        break;
    case 'T':
        console.log('into test route Path');
        var path = gameInfo.map.genTestPath();
        var fit = gameInfo.map.testRoute(path);
        gameInfo.map.memoryRender();
        var result = {
            testPath: path,
            fit: fit,
            map: gameInfo.map
        };
        console.log('get result', result);
        break;
    case 'D':
        debugger;
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
 class BobsMap
*/
function BobsMap(stage) {
    this.map = [
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
        [1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1],
        [8, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1],
        [1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1],
        [1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1],
        [1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1],
        [1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1],
        [1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 5],
        [1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1],
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    ];

    this.border = 20; // 四周边界
    this.blockSizeX = (WINDOW_WIDTH - 2 * this.border) / MAP_WIDTH;
    this.blockSizeY = (WINDOW_HEIGHT - 2 * this.border) / MAP_HEIGHT;

    this.startX = 14;
    this.startY = 7;
    this.endX = 0;
    this.endY = 2;

    this.stage = stage;

    // init this.memory to 0
    this.memory = this.getCleanMemory();

    this.graphics = new PIXI.Graphics();
    this.memoryGraphics = new PIXI.Graphics();

    this.stage.addChild(this.graphics);
    this.stage.addChild(this.memoryGraphics);
}

BobsMap.prototype.drawRectWithColor = function (graphics, rectInfo, color) {
    graphics.lineStyle(1, COLOR.gray);
    graphics.beginFill(color);
    graphics.drawRect(rectInfo.left, rectInfo.top, rectInfo.width, rectInfo.height);
    graphics.endFill();
};

BobsMap.prototype.Render = function () {
    var i, j;

    var gh = this.graphics;
    gh.clear();

    for (i = 0; i < MAP_HEIGHT; i++) {
        for (j = 0; j < MAP_WIDTH; j++) {
            var left = this.border + j * this.blockSizeX;
            var top = this.border + i * this.blockSizeY;

            var rectInfo = {
                left: left,
                top: top,
                width: this.blockSizeX,
                height: this.blockSizeY
            };

            switch (this.map[i][j]) {
            case 0:
                this.drawRectWithColor(gh, rectInfo, COLOR.white);
                break;
            case 1:
                this.drawRectWithColor(gh, rectInfo, COLOR.black);
                break;
            case 5:
            case 8:
                this.drawRectWithColor(gh, rectInfo, COLOR.red);
                break;
            }
        }
    }
};

BobsMap.prototype.getCleanMemory = function () {
    var mem = [];
    var i, j;
    for (i = 0; i < MAP_HEIGHT; i++) {
        mem.push([]);
        for (j = 0; j < MAP_WIDTH; j++) {
            mem[i].push(0);
        }
    }
    return mem;
};

BobsMap.prototype.memoryRender = function () {
    var y, x;

    this.memoryGraphics.clear();
    for (y = 0; y < MAP_HEIGHT; y++) {
        for (x = 0; x < MAP_WIDTH; x++) {
            var left = this.border + this.blockSizeX * x;
            var top = this.border + this.blockSizeY * y;

            var rectInfo = {
                left: left,
                top: top,
                width: this.blockSizeX,
                height: this.blockSizeY
            };

            if (this.memory[y][x] == 1) {
                this.drawRectWithColor(this.memoryGraphics, rectInfo, COLOR.gray);
            }
        }
    }
};

BobsMap.prototype.genTestPath = function () {
    var path = [];
    for (var i = 0; i < CHROMO_LENGTH; i++) {
        path.push('nsew'[Math.floor(Math.random() * 4)]);
    }

    return path;
};

BobsMap.prototype.testRoute = function (path) {
    var i;
    var posX = this.startX;
    var posY = this.startY;

    this.memory = this.getCleanMemory();
    for (i = 0; i < path.length; i++) {
        switch (path[i]) {
        case 'n': // North
            if ((posY - 1) >= 0 && (this.map[posY-1][posX] != 1)) {
                posY -= 1;
            }
            break;
        case 's': // South
            if ((posY + 1) < MAP_HEIGHT && (this.map[posY+1][posX] != 1)) {
                posY += 1;
            }
            break;
        case 'e': // East
            if ((posX + 1) < MAP_WIDTH && (this.map[posY][posX + 1] != 1)) {
                posX += 1;
            }
            break;
        case 'w': // East
            if ((posX - 1) < MAP_WIDTH && (this.map[posY][posX - 1] != 1)) {
                posX -= 1;
            }
            break;
        }

        this.memory[posY][posX] = 1;
    }

    var diffX = Math.abs(posX - this.endX);
    var diffY = Math.abs(posY - this.endY);

    return 1 / (diffX + diffY + 1);
};

// BobsMap end here

/*
 class Genome
*/
function Genome(numBits) {
    this.bits = [];
    this.fitness = 0;

    for (var i = 0; i < numBits; i++) {
        this.bits.push(Math.floor(Math.random() * 2));
    }
}
