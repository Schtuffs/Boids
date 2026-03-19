#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Colour.h"
#include "Window.h"
#include "Callbacks.h"
#include "Boid.h"

#include <cmath>
#include <print>

void foo(double x, double y) {
    std::println("X: {}, Y: {}, Tan: {}, aTan: {}", x, y, std::tan(y / x), std::atan2(y, x));
}
int main(void) {
    foo(10, 0);
    foo(10, -5);
    foo(10, -10);
    foo(5, -10);
    foo(0.00001, -10);
    foo(-5, -10);
    foo(-10, -10);
    foo(-10, -5);
    foo(-10, 0);
    foo(-10, 5);
    foo(-10, 10);
    foo(-5, 10);
    foo(1, 10);
    foo(5, 10);
    foo(10, 10);
    foo(10, 5);
    // return 0;
    // Create and check main window
    Window window("Boids");
    if (!window.isCreated()) {
        return 0;
    }
    Boid b[100];
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

