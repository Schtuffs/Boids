#pragma once

#include <iostream>
#include <mutex>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Colour.h"
#include "Renderable.h"

class Window {
public:
    // ----- Creation ----- Destruction -----

    Window(const std::string& title = "Window");
    bool isCreated();
    ~Window();

    // Returns when main window is closed
    static void await();


    
    // ----- Setters -----
    
    // Sets this windows as the main window
    // If this window is closed, program ends
    void setMain();
    
    // Set background to specified colour
    void setBackground(Colour col);

    // Changes the size of the window
    void setSize(int width, int height);
    
    // Chooses callback overload based on passed param
    
    // Sets the key callback for the window
    void setCallback(GLFWkeyfun callback);
    // Sets the cursor position callback for the window
    void setCallback(GLFWcursorposfun callback);
    // Sets the mouse button callback for the window
    void setCallback(GLFWmousebuttonfun callback);
    // Sets the character pressed callback for the window
    void setCallback(GLFWcharfun callback);
    // Sets the window resize callback for the window
    void setCallback(GLFWframebuffersizefun callback);
    // Sets the window refresh callback for the window
    void setCallback(GLFWwindowrefreshfun callback);

    // Add a new drawable into the screen
    void add(Renderable& obj);
    // Removes a renderable from the screen
    // Allows removal by index
    bool remove(int index);
    // Removes a renderable from the screen
    // Allows removal by object
    bool remove(Renderable& obj);

    // Runs window with current args
    void run(uint64_t frames = 60, bool upsMatchFps = true);



    // ----- Getters -----

    std::vector<Renderable&> renderables();

private:
    // Holds the window data
    GLFWwindow* m_window;
    bool m_created;
    int m_width, m_height;

    // Updates window size
    std::mutex m_sizeLock;
    bool m_sizeChanged;

    // Rendering objects
    std::vector<Renderable*> m_renderObjects;

    // Time since previous render
    uint64_t m_prevTime, m_frameTime;

    // For rendering frames at defined frame rate
    bool hasFrameTimePassed(bool upsMatchFps);
    
    // Required OpenGL functions for a window to function

    // Main window loop
    void showWindow(bool upsMatchFps);

    // Main function to check for looping
    bool shouldClose();

    // Checks and updates window for any changes
    void checkChanges();

    // Checks the size changes
    void checkSizeChange();

    // Render window
    void render(bool upsMatchFps);

    // On close
    void close();
};

