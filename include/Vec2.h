#pragma once

typedef struct Vec2 {
    double x = 0, y = 0;
    Vec2(double x, double y);

    void add(const Vec2& o);
    void sub(const Vec2& o);
    void multiply(double scalar);
    void divide(double scalar);
} Vec2;

