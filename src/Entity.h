//
// Created by daniel on 23.04.20.
//

#ifndef PHYSICS_ENTITY_H
#define PHYSICS_ENTITY_H

#include <map>
#include <type_traits>
#include "Components/Component.h"

class Entity {
public:
    ~Entity();
    void update();
    void draw() const;

    void addComponent(Component* component);
    void setComponent(const std::string& componentName, Component* component);

    template<typename T>
    typename std::enable_if<std::is_base_of<Component,T>::value,T*>::type
    getComponent(const std::string& componentName) {
        return dynamic_cast<T*>(this->components[componentName]);
    }

protected:
    map<string, Component*> components;
};


#endif //PHYSICS_ENTITY_H
