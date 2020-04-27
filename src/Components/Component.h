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
    virtual ~Component() { }
    virtual void update(){};
    virtual void draw(){};
    virtual void addToEntity(Entity* entity) = 0;

    void setEntity(Entity *_entity) {
        this->entity = _entity;
    }

protected:
    Entity* entity;
};

#endif //PHYSICS_COMPONENT_H
