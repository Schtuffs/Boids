#include "Vec2.h"

Vec2::Vec2(double x, double y) : x(x), y(y) {}

void Vec2::add(const Vec2& other) {
    this->x += other.x;
    this->y += other.y;
}

void Vec2::sub(const Vec2& other) {
    this->x -= other.x;
    this->y -= other.y;
}

void Vec2::multiply(double scalar) {
    this->x *= scalar;
    this->y *= scalar;
}

void Vec2::divide(double scalar) {
    this->x /= scalar;
    this->y /= scalar;
}

