#define GLFW_INCLUDE_GLU
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

int main()
{
    if (!glfwInit())
    {
        printf("Could not initialize glfw.\n");
        return -1;
    }
    GLFWwindow *window;
    window = glfwCreateWindow(640, 640, "OpenGL TP 1", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    float r = 45.0;

    while (!glfwWindowShouldClose(window))
    {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef(r, 0.0, 0.0, 1.0);
        glScalef(0.50, 0.50, 0.5);
        gluLookAt(0, 1, 5, 0, 0, 0, 0, 1, 0);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45, 1, 0.1, 100);

        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0f, 0.0f, 0.0f);

        // Drawing with GL_TRIANGLES
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        // top
        glColor3f(1.0f, 0.0f, 0.0f);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);

        glEnd();

        glBegin(GL_QUADS);
        // front
        glColor3f(0.0f, 1.0f, 0.0f);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f, -0.5f, 0.5f);

        glEnd();

        glBegin(GL_QUADS);
        // right
        glColor3f(0.0f, 0.0f, 1.0f);
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.5f, 0.5f, -0.5f);
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);

        glEnd();

        glBegin(GL_QUADS);
        // left
        glColor3f(0.0f, 0.0f, 0.5f);
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);
        glVertex3f(-0.5f, -0.5f, -0.5f);

        glEnd();

        glBegin(GL_QUADS);
        // bottom
        glColor3f(0.5f, 0.0f, 0.0f);
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);

        glEnd();

        glBegin(GL_QUADS);
        // back
        glColor3f(0.0f, 0.5f, 0.0f);
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(0.5f, 0.5f, -0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);

        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
        r += 0.01;
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
