#include <cmath>

#include "window/Colour.h"
#include "window/Window.h"
#include "Callbacks.h"
#include "Boid.h"
#include "Vec2.h"

#define SIZE(_array) (sizeof(_array) / sizeof(_array[0]))

void seekVelocity(Boid* boids, uint64_t size) {
    constexpr int64_t SCALE = 3;

    // Calculate average velocity
    Vec2 avgVel(0, 0);
    for (uint64_t i = 0; i < size; i++) {
        avgVel.add(boids[i].velocity());
    }
    avgVel.divide(size);
    
    // Adjust velocities
    for (uint64_t i = 0; i < size; i++) {
        boids[i].addAcceleration(avgVel.x / SCALE, avgVel.y / SCALE);
    }
}

void seekCenter(Boid* boids, uint64_t size) {
    constexpr int64_t SCALE = 1250;
    
    // Calculate center
    Vec2 center(0, 0);
    for (uint64_t i = 0; i < size; i++) {
        center.add(boids[i].position());
    }
    center.divide(size);
    
    // Move all to center
    for (uint64_t i = 0; i < size; i++) {
        Vec2 pos = boids[i].position();
        boids[i].addAcceleration((center.x - pos.x) / (SCALE), (center.y - pos.y) / (SCALE));
    }
}

double dist(const Vec2& pos1, const Vec2& pos2) {
    return (std::sqrt((pos2.x - pos1.x) * (pos2.x - pos1.x) + (pos2.y - pos1.y) * (pos2.y - pos1.y)));
}

void avoidNeighbours(Boid* boids, uint64_t size) {
    constexpr double MIN_DIST = Boid::BOID_WIDTH * 1.5;
    constexpr int64_t SCALE = 1;
    
    // Please optimize this :(
    for (uint64_t current = 0; current < size - 1; current++) {
        Vec2 curPos = boids[current].position();
        for (uint64_t other = current + 1; other < size; other++) {
            Vec2 othPos = boids[other].position();
            double distance = dist(curPos, othPos);
            if (distance < MIN_DIST) {
                // Push away by calculating slope between
                Vec2 center(std::abs(othPos.x + curPos.x) / 2, std::abs(othPos.y + curPos.y) / 2);
                Vec2 curSeparate(curPos.x - center.x, curPos.y - center.y);
                Vec2 othSeparate(othPos.x - center.x, othPos.y - center.y);
                curSeparate.multiply((1.0 / distance) / SCALE);
                othSeparate.multiply((1.0 / distance) / SCALE);
                boids[current].addAcceleration(curSeparate);
                boids[other].addAcceleration(othSeparate);
            }
        }
    }
}

int main(void) {
    srand(time(nullptr));
    
    // Create and check main window
    Window window("Boids");
    if (!window.isCreated()) {
        return 0;
    }

    Boid boids[100];
    for (size_t i = 0; i < SIZE(boids); i++) {
        window.add(&boids[i]);
    }

    window.setBackground(Colour(0, 0, 0))
    .setCallback(key_callback)
    .setCallback(window_callback)
    .run(60, true, [&]() {
            seekVelocity(boids, SIZE(boids));
            seekCenter(boids, SIZE(boids));
            avoidNeighbours(boids, SIZE(boids));
        });
    
    Window::await();
    return 0;
}

