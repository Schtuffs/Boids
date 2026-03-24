#pragma once

#include "Colour.h"
#include "Renderable.h"
#include "Window.h"

constexpr double BOID_MAGNITUDE     = 1.;
constexpr double BOID_WIDTH         = 20.;
constexpr double BOID_HEIGHT        = 20.;

class Boid : public Renderable {
public:
    /**
     * @brief Create boid within bounds of window.
     * @param width The width of the window.
     * @param height The height of the window.
     * @author Kyle Wagler
     * @date 2026-03-19
     */
    Boid(int width = Window::DEFAULT_WINDOW_WIDTH, int height = Window::DEFAULT_WINDOW_HEIGHT);
    /**
     * @brief Create a boid at a specific location with a specific velocity.
     * @param x The starting X position for the boid.
     * @param y The starting Y position for the boid.
     * @param velX The initial X velocity for the boid.
     * @param velY The initial Y velocity for the boid.
     * @author Kyle Wagler
     * @date 2026-03-19
     */
    Boid(double x, double y, double velX, double velY);
    /**
     * @brief Destroys the boid.
     * @author Kyle Wagler
     * @date 2026-03-19
     */
    ~Boid();

    /**
     * @brief Normalizes the length of the velocity vector to magnitude
     * @param magnitude the magnitude of the velocity
     * @author Kyle Wagler
     * @date 2026-03-19
     */
    void normalize(double magnitude);
    
private:
    double m_x, m_y, m_velX, m_velY;
    Colour m_colour;
    static GLuint s_shader;
    
    void update();
    void checkEdges();
    
    void render();
};

