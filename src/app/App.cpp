#include <iostream>

#include "window/Window.hpp"
#include "App.hpp"


void App::Run()
{
    Window window{ 800, 600, "GLFW + ImGui" };
    if (!window.IsReady()) {
        fprintf(stderr, "Failed to initialize the window\n");
        return;
    }

    window.StartAppLoop();
    window.Shutdown();
}