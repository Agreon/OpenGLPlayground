//
// Created by daniel on 23.04.20.
//

#include "Entity.h"

#include <iostream>

Entity::~Entity() {
    for(const auto& component : components) {
        delete component.second;
    }
}

void Entity::update() {
    for(const auto& component : components) {
        component.second->update();
    }
}

void Entity::draw() const {
    for(const auto& component : components) {
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

