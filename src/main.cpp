#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Colour.h"
#include "Window.h"
#include "Callbacks.h"
#include "Boid.h"

void foo(Renderable& f) {
    f.render();
}

int main(void) {
    // Create and check main window
    Window window("Boids");
    if (!window.isCreated()) {
        return 0;
    }
    Boid b[] {
        Boid(WINDOW_SIZE_X, WINDOW_SIZE_Y),
        Boid(WINDOW_SIZE_X, WINDOW_SIZE_Y),
        Boid(WINDOW_SIZE_X, WINDOW_SIZE_Y),
        Boid(WINDOW_SIZE_X, WINDOW_SIZE_Y),
        Boid(WINDOW_SIZE_X, WINDOW_SIZE_Y),
        Boid(WINDOW_SIZE_X, WINDOW_SIZE_Y),
        Boid(WINDOW_SIZE_X, WINDOW_SIZE_Y),
        Boid(WINDOW_SIZE_X, WINDOW_SIZE_Y),
        Boid(WINDOW_SIZE_X, WINDOW_SIZE_Y),
        Boid(WINDOW_SIZE_X, WINDOW_SIZE_Y),
    };
    for (size_t i = 0; i < sizeof(b) / sizeof(Boid); i++) {
        window.add(b[i]);
    }
    window.setSize(WINDOW_SIZE_X, WINDOW_SIZE_Y)
        .setBackground(Colour(0, 0, 0))
        .setCallback(key_callback_main)
        .run();
    
    Window::await();
    return 0;
}

