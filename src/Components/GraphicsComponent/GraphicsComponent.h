//
// Created by daniel on 26.04.20.
//

#ifndef PHYSICS_GRAPHICSCOMPONENT_H
#define PHYSICS_GRAPHICSCOMPONENT_H

#include <string>

#include "../Component.h"

const string GRAPHICS_COMPONENT = "GRAPHICS_COMPONENT";

class GraphicsComponent : public Component {
public:
    void update() override;
    void draw() override;
    void addToEntity(Entity* entity) override;
};


#endif //PHYSICS_GRAPHICSCOMPONENT_H
