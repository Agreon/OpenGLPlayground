//
// Created by daniel on 26.04.20.
//

#include "PhysicsComponent.h"
#include "../../Entity.h"


PhysicsComponent::PhysicsComponent(CollisionManager* collisionManager, const Vec2D &position, const Vec2D &velocity, const float &mass) {
    this->collisionManager = collisionManager;
    this->position = position;
    this->velocity = velocity;
    this->nextVelocity = velocity;
    this->mass = mass;
    this->width = 10;
    this->height = 10;
    this->halfWidth = this->width / 2;
    this->halfHeight = this->height / 2;
    this->collisionManager->registerEntity(this);
}

void PhysicsComponent::update() {
    this->position.x += this->velocity.x;
    this->position.y += this->velocity.y;

    if(this->velocity.x != 0 || this->velocity.y != 0) {
        vector<PhysicsComponent*> collisions = collisionManager->getCollisionObjects(this);
        for(const auto& collision: collisions) {
            /**
             * ForEach set nextVelocity to calculated value
             */
          //  collision->nextVelocity = this->velocity + collision->velocity;
        }
    }


}


void PhysicsComponent::addToEntity(Entity *entity) {
    // TODO: Why doesnt this work with variables
    entity->setComponent("PHYSICS_COMPONENT", this);
    //entity->setComponent(PHYSICS_COMPONENT, this);
}

bool PhysicsComponent::collides(PhysicsComponent *other) {
    bool tooFarRight = other->position.x - other->halfWidth > this->position.x + this->halfWidth;
    bool tooFarLeft = other->position.x + other->halfWidth < this->position.x - this->halfWidth;
    bool tooFarUp = other->position.y + other->halfHeight < this->position.y - this->halfHeight ;
    bool tooFarBottom = other->position.y - other->halfHeight > this->position.y + this->halfHeight;

    return !(tooFarRight || tooFarLeft || tooFarBottom || tooFarUp);
}
