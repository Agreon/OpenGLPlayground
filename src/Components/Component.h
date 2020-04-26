//
// Created by daniel on 26.04.20.
//

#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

class Entity;

#include <string>

using namespace std;

class Component {
public:
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void addToEntity(Entity* entity) = 0;

    virtual void setEntity(Entity *entity) {
        this->entity = entity;
    }

protected:
    Entity* entity;
};

#endif //PHYSICS_COMPONENT_H
