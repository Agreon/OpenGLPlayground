//
// Created by daniel on 23.04.20.
//

#ifndef PHYSICS_ENTITY_H
#define PHYSICS_ENTITY_H

#include <map>
#include "Components/Component.h"

using namespace std;

class Entity {
public:
    ~Entity();
    void update();
    void draw() const;

    void addComponent(Component* component);
    void setComponent(const std::string& componentName, Component* component);

    Component* getComponent(const std::string& componentName);
protected:
    map<string, Component*> components;
};


#endif //PHYSICS_ENTITY_H
