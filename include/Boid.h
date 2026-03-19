#pragma once

#include "Colour.h"
#include "Renderable.h"

constexpr double BOID_MAGNITUDE    = 0;//1.;

class Boid : public Renderable {
public:
    Boid(int width, int height);
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
};

