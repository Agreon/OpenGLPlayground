//
// Created by daniel on 24.04.20.
//

#include "SimpleCollisionManager.h"

void SimpleCollisionManager::registerEntity(PhysicsComponent *entity) {
    // TODO: Check for existence
    this->entities.push_back(entity);
}

vector<PhysicsComponent*> SimpleCollisionManager::getCollisionObjects(PhysicsComponent *entity) {
    vector<PhysicsComponent*> collisions;

    for(const auto& e : this->entities){
        if(e != entity && entity->collides(e)) {
            collisions.push_back(e);
        }
    }

    return collisions;
}
