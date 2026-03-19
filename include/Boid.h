#pragma once

#include "Colour.h"
#include "Renderable.h"

constexpr double BOID_MAGNITUDE     = 1.;
constexpr double BOID_WIDTH         = 20.;
constexpr double BOID_HEIGHT        = 20.;

class Boid : public Renderable {
public:
    Boid(int width = WINDOW_SIZE_X, int height = WINDOW_SIZE_Y);
    Boid(double x, double y, double velX, double velY);
    ~Boid();

    /**
     * @brief Normalizes the length of the velocity vector to magnitude
     * @param magnitude the magnitude of the velocity
     * @author Kyle Wagler
     * @date 2026-03-19
     */
    void normalize(double magnitude);

    void render() override;

private:
    double m_x, m_y, m_velX, m_velY;
    Colour m_colour;

    void update();
    void checkEdges();
};

