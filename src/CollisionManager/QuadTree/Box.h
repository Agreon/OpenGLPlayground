//
// Created by daniel on 24.04.20.
//

#ifndef PHYSICS_BOX_H
#define PHYSICS_BOX_H


#include "../../Components/PhysicsComponent/PhysicsComponent.h"

class Box {
public:
    Box();
    Box(Box* parent, const float& left, const float& top, const float& right, const float& bottom);

    bool includes(const PhysicsComponent& entity) const;
    bool includes(const Vec2D& point) const;

    void addEntity(PhysicsComponent* entity);
    void removeEntity(PhysicsComponent* entity);

    float left;
    float top;
    float right;
    float bottom;

    Box* parent;
    vector<Box*> children;

    vector<PhysicsComponent*> entities;
};


#endif //PHYSICS_BOX_H
