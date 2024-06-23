#include "App.hpp"

#include <iostream>

#include "window/Window.hpp"

App::App()
{

}

void App::run()
{
    Window window;
    if (!window.initialize(800, 600, "GLFW + ImGui")) {
        fprintf(stderr, "Failed to initialize the window\n");
        //return -1;
    }

    window.update();
    window.shutdown();
}