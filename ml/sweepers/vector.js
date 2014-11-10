PIXI.Point.prototype.multiplyScalar = function(s) {
    this.x *= s;
    this.y *= s;
    return this;
};

PIXI.Point.prototype.add = function(v) {
    this.x += v.x;
    this.y += v.y;
    return this;
};
