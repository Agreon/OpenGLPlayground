//
// Created by daniel on 26.04.20.
//

#ifndef PHYSICS_PHYSICSCOMPONENT_H
#define PHYSICS_PHYSICSCOMPONENT_H

#include "../Component.h"
#include "../../util/Vec2D.h"
#include "../../CollisionManager/CollisionManager.h"

const string PHYSICS_COMPONENT = "PHYSICS_COMPONENT";

class PhysicsComponent : public Component {
public:
    PhysicsComponent(CollisionManager* collisionManager, const Vec2D& position, const Vec2D& velocity = Vec2D(), const float& mass = 1.0);
    void update() override;
    void draw() override;
    void addToEntity(Entity* entity) override;

    virtual bool collides(PhysicsComponent* other);

    Vec2D position;
    Vec2D velocity;
    Vec2D nextVelocity;
    float mass;
    float width;
    float height;
    float halfWidth;
    float halfHeight;
protected:
    CollisionManager* collisionManager;

};


#endif //PHYSICS_PHYSICSCOMPONENT_H
