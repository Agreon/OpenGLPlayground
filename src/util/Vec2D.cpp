//
// Created by daniel on 23.04.20.
//

#include "Vec2D.h"


Vec2D::Vec2D() {
    this->x = 0;
    this->y = 0;
}

Vec2D::Vec2D(float x, float y) {
    this->x = x;
    this->y = y;
}

Vec2D Vec2D::operator+(const Vec2D& other) const {
    return {x + other.x, y + other.y};
}

