#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdlib.h>
#include <list>
using namespace std;
class Color
{

public:
    float red, green, blue, alpha;

public:
    Color(int r = 0, int g = 0, int b = 0, int a = 100)
    {
        red = r / 255.0f;
        green = g / 255.0f;
        blue = b / 255.0f;
        alpha = a / 100.0f;
    }
};
class Point
{
public:
    int x, y;

public:
    Point(int X, int Y)
    {
        x = X;
        y = Y;
    }
};

class Traingle
{
public:
    Point *p1, *p2, *p3;

public:
    Traingle(Point *P1, Point *P2, Point *P3)
    {
        p1 = P1;
        p2 = P2;
        p3 = P3;
    }
};
class QUAD
{
public:
    Point *p1, *p2, *p3, *p4;

public:
    QUAD(Point *P1, Point *P2, Point *P3, Point *P4)
    {
        p1 = P1;
        p2 = P2;
        p3 = P3;
        p4 = P4;
    }
};
class App
{
public:
    GLFWwindow *window;

public:
    int Width, Height;
    float widthH, heightH;

public:
    App(int width, int height, char *title)
    {
        widthH = width / 2;
        heightH = height / 2;
        Width = width;
        Height = height;
        if (!glfwInit())
        {
            printf("Could not initialize glfw.\n");
            exit(-1);
        }
        window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            exit(-1);
        }
        glfwMakeContextCurrent(window);
    }

public:
    bool windowOpen()
    {
        return glfwWindowShouldClose(window);
    }

public:
    void startDraw()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        //draw
    }

public:
    void endDraw()
    {

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

public:
    void drawTraingle(Color *color, Traingle *traingle)
    {
        // Drawing with GL_TRIANGLES
        glColor3f(color->red, color->green, color->blue);
        glBegin(GL_TRIANGLES);
        glVertex2f(traingle->p1->x / widthH, traingle->p1->y / heightH);
        glVertex2f(traingle->p2->x / widthH, traingle->p2->y / heightH);
        glVertex2f(traingle->p3->x / widthH, traingle->p3->y / heightH);

        glEnd();
    }

public:
    void drawQUAD(Color *color, QUAD *quad)
    {
        // Drawing with GL_TRIANGLES
        glColor3f(color->red, color->green, color->blue);
        glBegin(GL_QUADS);
        glVertex2f(quad->p1->x / widthH, quad->p1->y / heightH);
        glVertex2f(quad->p2->x / widthH, quad->p2->y / heightH);
        glVertex2f(quad->p3->x / widthH, quad->p3->y / heightH);
        glVertex2f(quad->p4->x / widthH, quad->p4->y / heightH);

        glEnd();
    }

public:
    void End()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

public:
    void setBgColor(Color *color)
    {
        glClearColor(color->red, color->green, color->blue, color->alpha);
    }
};
