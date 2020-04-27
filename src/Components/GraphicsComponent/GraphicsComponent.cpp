//
// Created by daniel on 26.04.20.
//

#include <GL/gl.h>
#include <GL/freeglut.h>

#include "GraphicsComponent.h"
#include "../PhysicsComponent/PhysicsComponent.h"
#include "../../Entity.h"


void GraphicsComponent::draw() {
    auto body = entity->getComponent<PhysicsComponent>(PHYSICS_COMPONENT);

    glPushMatrix();
    glTranslatef(body->position.x, body->position.y, 0);
    glColor3f(1,1,1);
    glutSolidCube(body->width);
    glPopMatrix();
}

void GraphicsComponent::addToEntity(Entity *entity) {
    entity->setComponent("GRAPHICS_COMPONENT", this);
}
