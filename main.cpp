#include "myglwindow.h"
#include "elephantwindow.h"
#include <iostream>

int main()
{
    std::cout
            << "*****************************************************************\n"
            << "**                        -INSTRUCTIONS-                       **\n"
            << "*****************************************************************\n"
            << "| Press:                                                        |\n"
            << "|   U, H, J, K, O, L        => move light                       |\n"
            << "|   ESC                     => exit                             |\n"
            << "|   F11                     => toggle fullscreen                |\n"
            << "|   c                       => toggle camera orbit/viewer       |\n"
            << "|   4                       => wireframe display                |\n"
            << "|   7                       => shaded display                   |\n"
            << "|   8                       => flat shade display               |\n"
            << "|                                                               |\n"
            << "| Mouse:                                                        |\n"
            << "|   Left Drag               => navigate world                   |\n"
            << "|   Middle Drag             => pan                              |\n"
            << "|   Scroll Wheel            => zoom in/out                      |\n"
            << "|                                                               |\n"
            << "*****************************************************************\n";
//    MyGLWindow *myWindow = new MyGLWindow(
//                sf::VideoMode(800, 600, 32),
//                "Test SFML OpenGL Window");
    ElephantWindow *myWindow = new ElephantWindow(
                sf::VideoMode(800, 600, 32),
                "Test SFML OpenGL Window");
    myWindow->run();
    delete myWindow;

    return 0;
}

