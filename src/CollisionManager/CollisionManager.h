//
// Created by daniel on 24.04.20.
//


#ifndef PHYSICS_COLLISIONMANAGER_H
#define PHYSICS_COLLISIONMANAGER_H

using namespace std;
#include <vector>

class PhysicsComponent;

class CollisionManager {
public:
    virtual ~CollisionManager() { }
    virtual void registerEntity(PhysicsComponent *entity) = 0;
    virtual vector<PhysicsComponent*> getCollisionObjects(PhysicsComponent *entity) = 0;
};

#endif //PHYSICS_COLLISIONMANAGER_H
