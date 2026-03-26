#include "window/Colour.h"
#include "window/Window.h"
#include "Callbacks.h"
#include "Boid.h"
#include "Vec2.h"

#include <print>

#define SIZE(_array) (sizeof(_array) / sizeof(_array[0]))
constexpr int64_t SCALE = 100;

void seekVelocity(Boid* boids, uint64_t size) {
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
    // Calculate center
    Vec2 center(0, 0);
    for (uint64_t i = 0; i < size; i++) {
        center.add(boids[i].position());
    }
    center.divide(size);
    
    // Move all to center
    for (uint64_t i = 0; i < size; i++) {
        Vec2 pos = boids[i].position();
        boids[i].addAcceleration((center.x - pos.x) / (SCALE * SCALE), (center.y - pos.y) / (SCALE * SCALE));
    }
}

int main(void) {
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
        .run(60, true, [&](){
            seekVelocity(boids, SIZE(boids));
            seekCenter(boids, SIZE(boids));
        });
    
    Window::await();
    return 0;
}

