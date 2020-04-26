//
// Created by daniel on 24.04.20.
//

#include "Box.h"

Box::Box(Box *parent, const float &left, const float &top, const float &right, const float &bottom) {
    this->parent = parent;
    this->left = left;
    this->top = top;
    this->right = right;
    this->bottom = bottom;
}

Box::Box() {
    this->parent = nullptr;
    this->left = 0;
    this->top = 0;
    this->right = 0;
    this->bottom = 0;
}

/**
 * Checks whether the entity somehow collides with this box
 */
bool Box::includes(const PhysicsComponent& entity) const {
    return (
        (entity.position.x + entity.halfWidth) > this->left &&
        (entity.position.x - entity.halfWidth) < this->right &&
        (entity.position.y + entity.halfHeight) > this->top &&
        (entity.position.y - entity.halfHeight) < this->bottom
    );
}

bool Box::includes(const Vec2D& point) const {
    return (
        point.x >= this->left &&
        point.x <= this->right &&
        point.y >= this->top &&
        point.y <= this->bottom
    );
}

void Box::removeEntity(PhysicsComponent *entity) {
    int pos = 0;
    for(int i = 0; i < this->entities.size(); i++){
        if(this->entities[i] == entity) {
            pos = i;
            break;
        }
    }
    this->entities.erase(this->entities.begin() + pos);
}

void Box::addEntity(PhysicsComponent *entity) {
    this->entities.push_back(entity);
}
