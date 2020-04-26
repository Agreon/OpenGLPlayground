//
// Created by daniel on 24.04.20.
//

#ifndef PHYSICS_SCENE_H
#define PHYSICS_SCENE_H


#include "CollisionManager/CollisionManager.h"
#include "Entity.h"

class Scene {
public:
    Scene(int width, int height);
    ~Scene();
    void update();
    void draw();

private:
    CollisionManager* manager;
    vector<Entity*> entities;
};


#endif //PHYSICS_SCENE_H
