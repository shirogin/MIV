#include "predef.h"

int main()
{
    App *app = new App(640, 500, "OpenGL Tp1");
    app->setBgColor(new Color(0, 150, 100));
    Color *c1 = new Color(255, 255, 255),
          *c2 = new Color(255, 0, 0),
          *c3 = new Color(0, 255, 0),
          *c4 = new Color(0, 0, 255);
    Traingle *t1 = new Traingle(new Point(320, 0), new Point(-320, 0), new Point(0, 200)),
             *t2 = new Traingle(new Point(250, 20), new Point(-250, 20), new Point(0, 180)),
             *qt1 = new Traingle(new Point(150, -100), new Point(50, -100), new Point(100, -50)),
             *qt2 = new Traingle(new Point(150, -100), new Point(50, -100), new Point(100, -150));
    QUAD *q = new QUAD(new Point(-150, -50), new Point(-50, -50), new Point(-50, -150), new Point(-150, -150));

    while (!app->windowOpen())
    {
        app->startDraw();
        app->drawTraingle(c1, t1);
        app->drawTraingle(c2, t2);
        app->drawTraingle(c3, qt1);
        app->drawTraingle(c3, qt2);
        app->drawQUAD(c4, q);
        app->endDraw();
    }
    app->End();

    return 0;
}
