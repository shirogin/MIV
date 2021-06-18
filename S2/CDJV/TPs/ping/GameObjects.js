class Ball extends CircleObject {
    constructor(name, position, raduis, InitV) {
        super("Ball " + name, position, raduis, InitV, true);
        this.render.collide = { fill: "#FFc0F0" };
        this.render.color = { fill: "#EF4C00" };
    }
}
class Paddle extends RectObject {
    constructor(name, position, sizes, InitV) {
        super("Paddle " + name, position, sizes, InitV, true);
        this.render.collide = { fill: "#FFFF00" };
        this.render.color = { fill: "#9A8290" };
    }
}
