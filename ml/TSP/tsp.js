"use strict";

window.addEventListener("load", main, false);

// config
var WINDOW_WIDTH = 500;
var WINDOW_HEIGHT = 500;

var NUM_CITIES = 20;
var CITY_SIZE = 5;

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
    stage = new PIXI.Stage(0xFFFFFF);
    var renderer = PIXI.autoDetectRenderer(WINDOW_WIDTH, WINDOW_HEIGHT);

    document.body.appendChild(renderer.view);

    var gaTSP = new GaTSP(MUTATION_RATE, CROSSOVER_RATE, POP_SIZE, NUM_CITIES, WINDOW_WIDTH, WINDOW_HEIGHT);
    gameInfo.gaTSP = gaTSP;
    gaTSP.render();
    gaTSP.show(stage);

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

    var gaTSP = gameInfo.gaTSP;

    gaTSP.render();

    switch (char) {
    case ' ':
        console.log('into space process');
        if (!gaTSP.started) {
            gaTSP.run();
        } else {
            gaTSP.stop();
        }
        break;
    case 'D':
        debugger;
        break;
    case 'R':
        console.log('reset');
        break;
    case 'N':
        console.log('one epoch');
        gaTSP.epoch();
        gaTSP.render();
        console.log('gaTSP', gaTSP);
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
 class MapTSP
*/
function MapTSP(width, height, numCities) {
    this.width = width;
    this.height = height;
    this.numCities = numCities;
    this.margin = 50;

    // city coordinates, {x: 0, y: 0}
    this.cities = [];

    this.createCitiesCircular();
    this.calculateBestPossibleRoute();
}

MapTSP.prototype.createCitiesCircular = function () {
    var radius;

    if (this.height < this.width) {
        radius = this.height / 2 - this.margin;
    } else {
        radius = this.width / 2 - this.margin;
    }

    var origin = {x: this.width / 2, y: this.height / 2};
    var segmentSize = 2 * PI / this.numCities;
    var angle = 0;

    var cities = [];

    while (angle < 2 * PI) {
        var thisCity = {};

        thisCity.x = radius * Math.sin(angle) + origin.x;
        thisCity.y = radius * Math.cos(angle) + origin.y;

        cities.push(thisCity);
        angle += segmentSize;
    }
    this.cities = cities;
};

MapTSP.prototype.calculateBestPossibleRoute = function () {
    this.bestPossibleRoute = 0;

    for (var i = 0; i < this.cities.length - 1; i++) {
        this.bestPossibleRoute += this.calculateA2B(this.cities[i], this.cities[i+1]);
        this.bestPossibleRoute += EPSILON;
    }
    this.bestPossibleRoute += this.calculateA2B(this.cities.slice(-1)[0], this.cities[0]);
};

MapTSP.prototype.calculateA2B = function (city1, city2) {
    var diffx = city1.x - city2.x;
    var diffy = city1.y - city2.y;

    return Math.sqrt(diffx * diffx + diffy * diffy);
};

MapTSP.prototype.getTourLength = function (route) {
    var totalDistance = 0;
    for (var i = 0; i < route.length - 1; i++) {
        var city1 = route[i];
        var city2 = route[i+1];

        totalDistance += this.calculateA2B(this.cities[city1], this.cities[city2]);
    }

    totalDistance += this.calculateA2B(this.cities.slice(-1)[0], this.cities[0]);

    return totalDistance;
};

// MapTSP end here

/*
 class Genome
*/
function Genome(numCities) {
    this.cities = [];
    this.fitness = 0;

    this.cities = this.grabPermutatioin(numCities);
}

Genome.prototype.grabPermutatioin = function (limit) {
    var perm = [];
    for (var i = 0; i < limit; i++) {
        var nextPossibleNum = randInt(0, limit);
        while (perm.indexOf(nextPossibleNum) >= 0) {
            nextPossibleNum = randInt(0, limit);
        }

        perm.push(nextPossibleNum);
    }
    return perm;
};

// Genome end here

/*
 class GaTSP
*/
function GaTSP(mutRat, crossRat, popSize, numCities, mapWidth, mapHeight) {
    this.mutatioinRate = mutRat;
    this.crossvoerRate = crossRat;
    this.popSize = popSize;
    this.fittestGenome = 0;
    this.generation = 0;
    this.shortestRoute = 999999999;
    this.longestRoute = 0;
    this.chromoLength = numCities;
    this.started = false;

    this.pen = new PIXI.Graphics();

    this.startText = new PIXI.Text("");
    this.titleText = new PIXI.Text("");

    this.tagTexts = [];

    this.style = {
        font: 'bold 15px Arial',
        fill: '#565E67'
    };
    this.startText.setStyle(this.style);
    this.titleText.setStyle(this.style);


    this.population = [];

    this.map = new MapTSP(mapWidth, mapHeight, numCities);

    this.titleText.position.x = this.map.margin / 5;
    this.titleText.position.y = 10;
    this.startText.position.y = mapHeight - this.map.margin + 10;

    this.createStartPopulation();
}

GaTSP.prototype.createStartPopulation = function () {
    this.population = [];

    for (var i = 0; i < this.popSize; i++) {
        this.population.push(new Genome(this.chromoLength));
    }

    this.generation = 0;
    this.shortestRoute = 999999999;
    this.fittestGenome = 0;
    this.started = false;
};

GaTSP.prototype.render = function () {
    var i, x, y, targetCity, text;

    this.pen.clear();

    // draw all the cities
    for (i = 0; i < this.map.cities.length; i++) {
        x = this.map.cities[i].x;
        y = this.map.cities[i].y;
        this.pen.lineStyle(2);
        this.pen.drawEllipse(x, y, CITY_SIZE, CITY_SIZE);
    }

    var route = this.population[this.fittestGenome].cities;
    // console.log('fittest %s', this.fittestGenome, route);

    this.pen.lineStyle(1);

    var startCity = this.map.cities[route[0]];
    this.pen.moveTo(startCity.x, startCity.y);
    if (this.generation !== 0) {
        for (i = 1; i < route.length; i++) {
            targetCity = this.map.cities[route[i]];
            this.pen.lineTo(targetCity.x, targetCity.y);

            if (NUM_CITIES < 100) {
                if (!this.tagTexts[i]) {
                    text = new PIXI.Text("");
                    text.setStyle(this.style);
                    stage.addChild(text);
                    this.tagTexts[i] = text;
                }
                this.tagTexts[i].setText(i.toString());
                this.tagTexts[i].position.x = targetCity.x + 2;
                this.tagTexts[i].position.y = targetCity.y + 2;
            }
        }
        targetCity = startCity;
        this.pen.lineTo(startCity.x, startCity.y);
        if (!this.tagTexts[i]) {
            text = new PIXI.Text("");
            text.setStyle(this.style);
            stage.addChild(text);
            this.tagTexts[i] = text;
        }
        this.tagTexts[i].setText(i.toString());
        this.tagTexts[i].position.x = targetCity.x + 2;
        this.tagTexts[i].position.y = targetCity.y + 2;
    }

    var title = 'Generation: ' + this.generation;
    this.titleText.setText(title);
    if (this.started) {
        this.startText.setText('Space to stop');
        this.epoch();
    } else {
        this.startText.setText('Press Space to start a new run');
    }
    this.startText.position.x = parseInt((this.map.width - this.startText.width) / 2);
};

GaTSP.prototype.show = function (stage) {
    stage.addChild(this.titleText);
    stage.addChild(this.startText);
    stage.addChild(this.pen);
};

GaTSP.prototype.run = function () {
    console.log('start run');
    this.createStartPopulation();
    this.started = true;
};

GaTSP.prototype.stop = function () {
    console.log('stop run');
    this.started = false;
};

GaTSP.prototype.reset = function () {
    this.shortestRoute = 999999999;
    this.longestRoute = 0;
    this.totalFitness = 0;
};

GaTSP.prototype.epoch = function () {
    // console.log('epoch ', this.generation);
    this.reset();

    this.calculatePopulationsFitness();
    // console.log('calculatePopulationsFitness end');

    if (this.shortestRoute <= this.map.bestPossibleRoute) {
        this.started = false;
        return;
    }

    var newPop = [];

    // First add NUM_BEST_TO_ADD number of the last generation's
    // fittest genome(elitism)
    for (var i = 0; i < NUM_BEST_TO_ADD; i++) {
        var baby = new Genome(this.chromoLength);
        baby.cities = this.population[this.fittestGenome].cities.slice(0);
        newPop.push(baby);
    }

    // now create the remainder of the populatioin
    while (newPop.length < this.popSize) {
        // console.log('newPop length', newPop.length);
        // grab two parents
        var mum = this.rouletteWheelSelection();
        var dad = this.rouletteWheelSelection();
        // console.log('rouletteWheelSelection end');

        var baby1 = new Genome(this.chromoLength);
        var baby2 = new Genome(this.chromoLength);

        // console.log('mum %s, dad %s', mum.cities.length, dad.cities.length);
        this.crossoverPMX(mum, dad, baby1, baby2);
        // console.log('crossoverPMX end');

        this.mutateEM(baby1.cities);
        this.mutateEM(baby2.cities);
        // console.log('mutate end');

        newPop.push(baby1);
        newPop.push(baby2);
    }

    this.population = newPop;
    this.generation += 1;
};

GaTSP.prototype.calculatePopulationsFitness = function () {
    var i;
    // for each chromo
    for (i = 0; i < this.popSize; i++) {
        var tourLength = this.map.getTourLength(this.population[i].cities);
        this.population[i].fitness = tourLength;

        // console.log('shortestRoute %s, tourLength %s', this.shortestRoute, tourLength)
        if (tourLength < this.shortestRoute) {
            this.shortestRoute = tourLength;
            this.fittestGenome = i;
        }

        if (tourLength > this.longestRoute) {
            this.longestRoute = tourLength;
        }
    }

    for (i = 0; i < this.popSize; i++) {
        this.population[i].fitness = this.longestRoute - this.population[i].fitness;
    }
};

GaTSP.prototype.rouletteWheelSelection = function () {
    var slice = Math.random() * this.totalFitness;
    var total = 0.0;

    var selectedGenome = 0;

    for (var i = 0; i < this.popSize; i++) {
        total += this.population[i].fitness;
        if (total > slice) {
            selectedGenome = i;
            break;
        }
    }

    return this.population[selectedGenome];
};

GaTSP.prototype.crossoverPMX = function (mum, dad, baby1, baby2) {
    baby1.cities = mum.cities.slice(0);
    baby2.cities = dad.cities.slice(0);

    if (Math.random() > this.crossvoerRate || mum === dad) {
        return;
    }

    var begin = randInt(0, mum.cities.length - 1);
    var end = begin;

    while (end <= begin) {
        end = randInt(0, mum.cities.length);
    }

    var pos1, pos2;

    for (var pos = begin; pos <= end; pos++) {
        var gene1 = mum.cities[pos];
        var gene2 = dad.cities[pos];

        if (gene1 != gene2) {
            // swap baby1
            var p1 = baby1.cities.indexOf(gene1);
            var p2 = baby1.cities.indexOf(gene2);
            baby1.cities[p1] = gene2;
            baby1.cities[p2] = gene1;

            p1 = baby2.cities.indexOf(gene1);
            p2 = baby2.cities.indexOf(gene2);
            baby2.cities[p1] = gene2;
            baby2.cities[p2] = gene1;
        }
    }
};

GaTSP.prototype.mutateEM = function (chromo) {
    if (Math.random() > this.mutatioinRate) {
        return;
    }

    var pos1 = randInt(0, chromo.length);
    var pos2 = pos1;

    while (pos1 == pos2) {
        pos2 = randInt(0, chromo.length);
    }

    var tmp = chromo[pos1];
    chromo[pos1] = chromo[pos2];
    chromo[pos2] = tmp;
};

// GaTSP end here

// [min, max)
function randInt(min, max) {
    return Math.floor(Math.random() * (max - min) + min);
}
