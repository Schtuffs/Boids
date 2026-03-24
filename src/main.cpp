#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Colour.h"
#include "Window.h"
#include "Callbacks.h"
#include "Boid.h"

int main(void) {
    // Create and check main window
    Window window("Boids");
    if (!window.isCreated()) {
        return 0;
    }
    Boid b[100];
    for (size_t i = 0; i < sizeof(b) / sizeof(Boid); i++) {
        window.add(&b[i]);
    }
    window.setBackground(Colour(0, 0, 0))
        .setCallback(key_callback)
        .setCallback(window_callback)
        .run();
    
    Window::await();
    return 0;
}

