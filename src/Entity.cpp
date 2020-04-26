//
// Created by daniel on 23.04.20.
//

#include "Entity.h"

Entity::~Entity() {
    for(const auto& component : components) {
        delete component.second;
    }
}

void Entity::update() {
    for(auto component : components) {
        component.second->update();
    }
}

void Entity::draw() const {
    for(auto component : components) {
        component.second->draw();
    }

}

void Entity::addComponent(Component* component) {
    component->addToEntity(this);
}

void Entity::setComponent(const std::string& componentName, Component* component) {
    component->setEntity(this);
    this->components[componentName] = component;
}

// TODO: Generic
Component* Entity::getComponent(const string &componentName) {
    return this->components[componentName];
}

