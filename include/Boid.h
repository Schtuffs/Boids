#pragma once

#include "window/Colour.h"
#include "window/Renderable.h"
#include "window/Window.h"

#include "Vec2.h"

class Boid : public Renderable {
public:
    static constexpr double BOID_MAGNITUDE      = 1.;
    static constexpr double BOID_WIDTH          = 20.;
    static constexpr double BOID_HEIGHT         = 20.;

    static constexpr double ACCELERATION_MIX    = -1.;
    static constexpr double ACCELERATION_MAX    = 1.;
    
    /**
     * @brief Create boid within bounds of window.
     * @param width The width of the window.
     * @param height The height of the window.
     * @author Kyle Wagler
     * @date 2026-03-19
     */
    Boid(int width = Window::DEFAULT_WINDOW_WIDTH, int height = Window::DEFAULT_WINDOW_HEIGHT);
    /**
     * @brief Destroys the boid.
     * @author Kyle Wagler
     * @date 2026-03-19
     */
    ~Boid();
    
    /**
     * @brief Updates the velocity of the boid.
     * @param accX The x-acceleration to add to the boid.
     * @param accY The y-acceleration to add to the boid.
     * @author Kyle Wagler
     * @date 2026-03-26
     */
    void addAcceleration(double accX, double accY);
    /**
     * @brief Updates the velocity of the boid.
     * @param acc The acceleration Vec2 to add to the boid.
     * @author Kyle Wagler
     * @date 2026-03-26
     */
    void addAcceleration(const Vec2& vec);

    /**
     * @brief Normalizes the length of the velocity vector to magnitude
     * @param magnitude the magnitude of the velocity
     * @author Kyle Wagler
     * @date 2026-03-19
     */
    void normalize(double magnitude);

    /**
     * @brief Gets the current position of the boid.
     * @return `Vec2` position.
     * @author Kyle Wagler
     * @date 2026-03-26
     */
    Vec2 position() const noexcept;
    /**
     * @brief Gets the current velocity of the boid.
     * @return `Vec2` velocity.
     * @author Kyle Wagler
     * @date 2026-03-26
     */
    Vec2 velocity() const noexcept;
    
private:
    double m_x, m_y, m_velX, m_velY, m_accX, m_accY;
    Colour m_colour;
    static GLuint s_shader;
    
    void update();
    void checkEdges();
    
    void render();
};

