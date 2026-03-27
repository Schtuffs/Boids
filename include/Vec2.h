#pragma once

typedef struct Vec2 {
    double x, y;
    Vec2(double x = 0., double y = 0.);

    void add(const Vec2& o);
    void sub(const Vec2& o);
    void multiply(double scalar);
    void divide(double scalar);
} Vec2;

