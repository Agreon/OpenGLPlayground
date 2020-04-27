//
// Created by daniel on 23.04.20.
//

#ifndef PHYSICS_VEC2D_H
#define PHYSICS_VEC2D_H


class Vec2D {
public:
    Vec2D();
    Vec2D(float x, float y);
    Vec2D operator+(const Vec2D& other) const;
    float x;
    float y;
};


#endif //PHYSICS_VEC2D_H
