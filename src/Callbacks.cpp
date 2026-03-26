#include "Callbacks.h"

#include <print>

#include "window/Window.h"

void key_callback([[maybe_unused]]GLFWwindow* window, [[maybe_unused]]int key, [[maybe_unused]]int scancode, [[maybe_unused]]int action, [[maybe_unused]]int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void window_callback(GLFWwindow* window, int width, int height) {
    try {
        Window& w = Window::find(window);
        w.setSize(width, height);
    } catch (std::string& err) {
        std::println(stderr, "{}", err);
    }
}
