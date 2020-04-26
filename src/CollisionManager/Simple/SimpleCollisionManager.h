//
// Created by daniel on 24.04.20.
//

#ifndef PHYSICS_SIMPLECOLLISIONMANAGER_H
#define PHYSICS_SIMPLECOLLISIONMANAGER_H


#include "../CollisionManager.h"
#include "../../Components/PhysicsComponent/PhysicsComponent.h"

/**
 * Just an array with registered entities
 * => On collision loop
 */
class SimpleCollisionManager : public CollisionManager  {
public:
    void registerEntity(PhysicsComponent *entity) override;
    vector<PhysicsComponent*> getCollisionObjects(PhysicsComponent *entity) override;
private:
    vector<PhysicsComponent*> entities;
};


#endif //PHYSICS_SIMPLECOLLISIONMANAGER_H
