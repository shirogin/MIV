class Transform {
    #position = new Vector2();
    get position() {
        return this.#position.Copy();
    }
    set position(v2) {
        if (v2 instanceof Vector2) this.#position = v2;
        else throw new Error("position is supposed to be Vector2");
    }

    #scale = new Vector2(1, 1);
    get scale() {
        return this.#scale.Copy();
    }
    set scale(v2) {
        if (v2 instanceof Vector2) this.#scale = v2;
        else throw new Error("scale is supposed to be Vector2");
    }

    #rotation = new Vector2();
    get rotation() {
        return this.#rotation.Copy();
    }
    set rotation(v2) {
        if (v2 instanceof Vector2) this.#rotation = v2;
        else throw new Error("rotation is supposed to be Vector2");
    }
}
class Collision {
    #normalVector;
    #speed;
    #collider1;
    #collider2;
    get speed() {
        return this.#speed;
    }
    get normalVector() {
        return this.#normalVector;
    }
    constructor(collider1, collider2) {
        //console.log(collider1, collider2);
        [this.#collider1, this.#collider2] = [collider1, collider2];
        this.#normalVector = collider2.position.NormalVector(collider1.position);
        const vRelativeVelocity = collider2.gameObject.physics.vilocity.Vector(
            collider1.gameObject.physics.vilocity
        );
        if (this.#normalVector.x === 0 && this.#normalVector.y === 0)
            this.#speed = vRelativeVelocity.x + vRelativeVelocity.y;
        else
            this.#speed =
                vRelativeVelocity.x * this.#normalVector.x +
                vRelativeVelocity.y * this.#normalVector.y;
    }
    Inverse() {
        return new Collision(this.#collider1, this.#collider2);
    }
}

class Render {
    onView = true;
    strocked = false;
    #colors = {
        default: { fill: "#000000", strock: "#00000000" },
        onCollid: { fill: "#00000000", strock: "#00000000" },
        onHover: { fill: "#00000000", strock: "#00000000" },
    };
    set color({ fill, strock }) {
        this.#colors.default.fill = fill ? fill : this.#colors.default.fill;
        this.#colors.default.strock = strock ? strock : this.#colors.default.strock;
    }
    get color() {
        return { ...this.#colors.default };
    }
    set collide({ fill, strock }) {
        this.#colors.onCollid.fill = fill ? fill : this.#colors.onCollid.fill;
        this.#colors.onCollid.strock = strock ? strock : this.#colors.onCollid.strock;
    }
    get collide() {
        return { ...this.#colors.onCollid };
    }
    set hover({ fill, strock }) {
        this.#colors.onHover.fill = fill ? fill : this.#colors.onHover.fill;
        this.#colors.onHover.strock = strock ? strock : this.#colors.onHover.strock;
    }
    get hover() {
        return { ...this.#colors.onHover };
    }
}
class Collider {
    #position;
    get position() {
        return this.#position.Add(this.gameObject.transform.position);
    }
    gameObject;
    #isColliding = false;
    get isColliding() {
        return this.#isColliding;
    }
    #collisions = [];
    get collisions() {
        return [...this.#collisions];
    }
    Empty() {
        this.#collisions = [];
        this.#isColliding = false;
    }
    Collide(collision) {
        this.#collisions.push(collision);
        this.#isColliding = true;
    }
    constructor(gameObject, position = new Vector2()) {
        this.gameObject = gameObject;
        if (position instanceof Vector2) this.#position = position;
        else throw new Error("position is supposed to be Vector2");
    }

    Intersect(collider) {
        if (this.position.Equal(collider.position)) return new Collision(this, collider);
    }
}
class RectCollider extends Collider {
    width;
    height;
    constructor(gameObject, width, height, position) {
        super(gameObject, position);
        this.width = width;
        this.height = height;
    }
    Intersect(collider) {
        let collision = super.Intersect(collider);
        if (collision) return collision;
        if (collider instanceof RectCollider) {
            const c =
                collider.position.x < this.width + this.position.x &&
                collider.position.y < this.height + this.position.y &&
                this.position.x < collider.width + collider.position.x &&
                this.position.y < collider.height + collider.position.y;
            console.log(c);
            return c ? new Collision(this, collider) : undefined;
        } else if (collider instanceof CircleCollider) {
        }
    }
}
class CircleCollider extends Collider {
    r;
    constructor(gameObject, r, position) {
        super(gameObject, position);
        this.r = r;
    }
    Intersect(collider) {
        if (super.Intersect(collider)) return true;
        if (collider instanceof RectCollider) {
        } else if (collider instanceof CircleCollider) {
            return (
                (this.x - collider.x) ** 2 + (this.y - collider.y) ** 2 <=
                (collider.r + this.r) ** 2
            );
        } else false;
    }
}
class Vector2 {
    #x;
    #y;
    set x(vx) {
        if (vx != undefined && !Number.isNaN(vx)) this.#x = vx;
        else throw new Error("x is supposed to be a Number");
    }
    set y(vy) {
        if (vy != undefined && !Number.isNaN(vy)) this.#y = vy;
        else throw new Error("y is supposed to be a Number");
    }
    get x() {
        return this.#x;
    }
    get y() {
        return this.#y;
    }
    constructor(x = 0, y = 0) {
        this.#x = x;
        this.#y = y;
    }
    Set(x, y) {
        if (x) this.x = x;
        if (y) this.y = y;
    }
    Distance(v2) {
        if (v2 instanceof Vector2) return Math.sqrt((this.#x - v2.x) ** 2 + (this.#y - v2.y) ** 2);
        else throw new Error("Distance can only be applied on Vector2 objects");
    }
    Vector(v2) {
        if (v2 instanceof Vector2) return new Vector2(this.x - v2.x, this.y - v2.y);
        else throw new Error("Vector can only be applied on Vector2 objects");
    }
    NormalVector(v2) {
        if (v2 instanceof Vector2) {
            const dist = Math.sqrt((this.#x - v2.#x) ** 2 + (this.#y - v2.#y) ** 2);
            if (dist === 0) return new Vector2();
            return new Vector2((this.#x - v2.#x) / dist, (this.#y - v2.#y) / dist);
        } else throw new Error("Normal Vector can only be applied on Vector2 objects");
    }
    Equal(v2) {
        if (v2 instanceof Vector2) return this.#x === v2.#x && this.#y === v2.#y;
        else throw new Error("Equal can only be applied on Vector2 objects");
    }
    Add(v2) {
        if (v2 instanceof Vector2) return new Vector2(this.#x + v2.#x, this.#y + v2.#y);
        else throw new Error("Equal can only be applied on Vector2 objects");
    }
    Copy() {
        return new Vector2(this.x, this.y);
    }
}
class Physics {
    #vilocity;
    get vilocity() {
        return this.#vilocity;
    }
    #weight; //kg
    get weight() {
        return this.#weight;
    }
    constructor(vilocity = new Vector2(), weight = 1) {
        this.vilocity = vilocity;
        this.weight = weight;
    }
    set vilocity(v2) {
        if (v2 instanceof Vector2) this.#vilocity = v2;
        else throw new Error("vilocity is supposed to be Vector2");
    }
    set weight(w) {
        if (w != undefined && !Number.isNaN(w)) this.#weight = w;
        else throw new Error("weight is supposed to be a Number");
    }
}
class ObjectCollector {
    static objects = [];
    static AddObject(obj) {
        ObjectCollector.objects.push(obj);
        ObjectCollector.objects = ObjectCollector.objects.sort((a, b) => a.priority - b.priority);
        return true;
    }
    static GetObjectsByName(name) {
        return ObjectCollector.objects.find((elm) => elm.name === name);
    }
    static GetObjectsByTag(tag) {
        return ObjectCollector.objects.filter((elm) => elm.tag === tag);
    }
    static GetEnabledObjects() {
        return ObjectCollector.objects.filter((elm) => elm.enabled);
    }
    static GetCollidableObjects() {
        return ObjectCollector.objects.filter((elm) => elm.enabled && elm.collider);
    }
}

class GameObject {
    transform = new Transform();
    priority = 0;
    render = new Render();
    physics;
    /**
     * @param {boolean} enabled - is GameObject enabled ?
     */
    enabled = true;
    #name = `gameObject-${Date.now()}`; //unique
    get name() {
        return this.#name;
    }
    tag = "_default";

    collider;
    /**
     * Create a GameObject.
     * @param {string} name - The name of the GameObject.
     * @param {Vector2} position - The position of the GameObject
     * @param {Vector2} vilocity - The position of the GameObject
     * @param {number} mass - The mass of the GameObject.
     */
    constructor(name, position, vilocity, mass) {
        this.physics = new Physics(vilocity, mass);
        this.transform.position = position;

        if (name) {
            if (!ObjectCollector.GetObjectsByName(name)) name += Date.now();
            this.#name = name;
        }
        ObjectCollector.AddObject(this);
    }
    Render(callback) {
        let clr = this.collider.isColliding
            ? this.render.collide
            : this.collider.isHovered
            ? this.render.hover
            : this.render.color;
        GameManager.ctx.fillStyle = clr.fill;
        if (this.render.strocked) GameManager.ctx.strockStyle = clr.strock;
        GameManager.ctx.beginPath();
        callback();
        GameManager.ctx.fill();
        if (this.render.strocked) GameManager.ctx.stroke();
    }
}
class RectObject extends GameObject {
    width;
    height;
    constructor(name, position, { w, h }, vilocity, collide = false, mass) {
        super(name, position, vilocity, mass);
        if (collide) this.collider = new RectCollider(this, w, h);
        this.width = w;
        this.height = h;
    }
    Render() {
        let $this = this;
        super.Render(function () {
            GameManager.ctx.rect(
                $this.transform.position.x,
                $this.transform.position.y,
                $this.width,
                $this.height
            );
        });
    }
}
class CircleObject extends GameObject {
    raduis;

    constructor(name, position, raduis, vilocity, collide = false, mass) {
        super(name, position, vilocity, mass);
        if (collide) this.collider = new CircleCollider(this, raduis);
        this.raduis = raduis;
    }
    Render() {
        let $this = this;
        super.Render(function () {
            GameManager.ctx.arc(
                $this.transform.position.x,
                $this.transform.position.y,
                $this.raduis,
                0,
                Math.PI * 2
            );
        });
    }
}
class GameManager {
    static ctx;
    static oldTime;
    constructor(canvas) {
        GameManager.canvas = document.getElementById(canvas);
        GameManager.ctx = GameManager.canvas.getContext("2d");
        if (!GameManager.ctx) {
            alert("Upgrade your browser");
            throw new Error("Upgrade your browse");
        } else window.requestAnimationFrame(GameManager.Start);
    }
    static Start(timestamp) {
        GameManager.oldTime = timestamp;
        ObjectCollector.GetEnabledObjects().forEach((gObj) => {
            if (gObj.Start) gObj.Start();
        });
        window.requestAnimationFrame(GameManager.Update);
    }
    static Update(timestamp) {
        let deltatime = (timestamp - GameManager.oldTime) / 1000;
        GameManager.oldTime = timestamp;
        //console.log(frame);
        GameManager.CollisionUpdate(deltatime);
        GameManager.PhysicUpdate(deltatime);
        GameManager.RenderUpdate(deltatime);
        if (timestamp < 6000) window.requestAnimationFrame(GameManager.Update);
    }
    static CollisionUpdate(deltatime) {
        //console.log(deltatime);
        const gameObjects = ObjectCollector.GetEnabledObjects(),
            l = gameObjects.length;
        gameObjects.forEach((elm) => elm.collider.Empty()); //empty collisions
        for (let i = 0; i < l - 1; i++) {
            const gObj1 = gameObjects[i];
            for (let j = i + 1; j < l; j++) {
                const gObj2 = gameObjects[j];
                let collision = gObj1.collider.Intersect(gObj2.collider);
                if (collision) {
                    gObj1.collider.Collide(collision);
                    gObj2.collider.Collide(collision.Inverse());

                    if (gObj1.OnCollusion) gObj1.OnCollusion(deltatime);
                    if (gObj2.OnCollusion) gObj2.OnCollusion(deltatime);
                }
            }
        }
    }
    static PhysicUpdate(deltatime) {
        ObjectCollector.GetEnabledObjects().forEach((gObj) => {
            gObj.transform.position = new Vector2(
                gObj.transform.position.x + gObj.physics.vilocity.x * deltatime,
                gObj.transform.position.y + gObj.physics.vilocity.y * deltatime
            );

            if (gObj.Update) gObj.Update(deltatime);
        });
    }
    static RenderUpdate(deltatime) {
        GameManager.ctx.clearRect(0, 0, GameManager.canvas.width, GameManager.canvas.height);

        ObjectCollector.GetEnabledObjects().forEach((gObj) => {
            if (gObj.Render) gObj.Render(deltatime);
        });
    }
}
