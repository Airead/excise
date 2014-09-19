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

function main() {
    var stage = new PIXI.Stage(0xFFFFFF);
    var renderer = PIXI.autoDetectRenderer(WINDOW_WIDTH, WINDOW_HEIGHT);

    document.body.appendChild(renderer.view);

    var map = new BobsMap(stage);
    map.stage = stage;

    map.Render();

    requestAnimFrame(animate);
    function animate() {
        requestAnimFrame(animate);

        renderer.render(stage);
    }
}

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

    this.mapTiles = [];
    this.stage = stage;

    // init this.memory to 0
    this.memory = [];
    var i, j;
    for (i = 0; i < WINDOW_HEIGHT; i++) {
        this.memory.push([]);
        for (j = 0; j < WINDOW_WIDTH; j++) {
            this.memory[i].push(0);
        }
    }

    this.graphics = new PIXI.Graphics();

    this.stage.addChild(this.graphics);
}

BobsMap.prototype.drawRectWithColor = function (graphics, rectInfo, color) {
    graphics.lineStyle(1, COLOR.gray);
    graphics.beginFill(color);
    graphics.drawRect(rectInfo.left, rectInfo.top, rectInfo.width, rectInfo.height);
    graphics.endFill();
};

BobsMap.prototype.Render = function () {
    var i, j;
    var border = 20;

    var blockSizeX = (WINDOW_WIDTH - 2 * border) / MAP_WIDTH;
    var blockSizeY = (WINDOW_HEIGHT - 2 * border) / MAP_HEIGHT;

    var gh = this.graphics;
    gh.clear();

    for (i = 0; i < MAP_HEIGHT; i++) {
        for (j = 0; j < MAP_WIDTH; j++) {
            var left = border + j * blockSizeX;
            var top = border + i * blockSizeY;

            var rectInfo = {
                left: left,
                top: top,
                width: blockSizeX,
                height: blockSizeY
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
