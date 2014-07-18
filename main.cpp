#include "myglwindow.h"

int main()
{
    MyGLWindow *myWindow = new MyGLWindow(
                sf::VideoMode(800, 600, 32),
                "Test SFML OpenGL Window");
    myWindow->run();
    delete myWindow;

    return 0;
}

