#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Colour.h"
#include "Window.h"
#include "Callbacks.h"

#include <thread>
using namespace std::chrono_literals;

int main(void) {
    // Create and check main window
    Window window("Boids");
    if (!window.isCreated()) {
        return 0;
    }
    window.setSize(800, 800);
    window.setBackground(Colour(0, 0, 0));
    window.setCallback(key_callback_main);
    window.run();

    Window::await();
    return 0;
}

