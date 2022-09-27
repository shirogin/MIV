#include <GLFW/glfw3.h>
#include <stdio.h>

int main()
{

    if (!glfwInit())
    {
        printf("Could not initialize glfw.\n");
        return -1;
    }
    //- Créer la fenêtre :
    GLFWwindow *window;
    window = glfwCreateWindow(640, 480, "OpenGL TP 1", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    //- Définir la couleur de l’arrière plan :
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    //- Définir la boucle d’affichage. Elle sera appelée à chaque fois que la fenêtre sera rafraîchie.
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    //A la sortie de la boucle, on détruit la fenêtre:
    glfwDestroyWindow(window);
    glfwTerminate();
    return 1;
}