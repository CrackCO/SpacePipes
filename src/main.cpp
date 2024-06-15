#include <iostream>

#include "Window.hpp"

int main()
{
    Window window(800, 600, "GLFW + ImGui");

    if (!window.initialize()) {
        fprintf(stderr, "Failed to initialize the window\n");
        return -1;
    }

    window.update();
    window.shutdown();

    return 0;
}
