#include "myglwindow.h"
#include <iostream>

int main()
{
    std::cout
            << "*****************************************************************\n"
            << "**                        -INSTRUCTIONS-                       **\n"
            << "*****************************************************************\n"
            << "| Press:                                                        |\n"
            << "|   ESC                     => exit                             |\n"
            << "|   F1                      => toggle shading / wire-frame mode |\n"
            << "|   F11                     => toggle fullscreen                |\n"
            << "|   c                       => toggle camera orbit/viewer       |\n"
            << "|                                                               |\n"
            << "| Mouse:                                                        |\n"
            << "|   Left Drag               => navigate world                   |\n"
            << "|   Middle Drag             => pan                              |\n"
            << "|                                                               |\n"
            << "*****************************************************************\n";
    MyGLWindow *myWindow = new MyGLWindow(
                sf::VideoMode(800, 600, 32),
                "Test SFML OpenGL Window");
    myWindow->run();
    delete myWindow;

    return 0;
}

