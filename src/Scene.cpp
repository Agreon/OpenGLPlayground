//
// Created by daniel on 24.04.20.
//

#include <GL/gl.h>
#include <GL/freeglut.h>
#include <chrono>

#include "Scene.h"
#include "CollisionManager/QuadTree/QuadTreeCollisionManager.h"
#include "CollisionManager/Simple/SimpleCollisionManager.h"
#include "Components/PhysicsComponent/PhysicsComponent.h"
#include "Components/GraphicsComponent/GraphicsComponent.h"

// TODO: Extract to factory
Entity* createEntity(CollisionManager* manager, const Vec2D& position, const Vec2D& velocity = Vec2D()) {
    auto entity = new Entity();

    entity->addComponent(new PhysicsComponent(manager, position, velocity));
    entity->addComponent(new GraphicsComponent());

    return entity;
}

Scene::Scene(int width, int height) {
    //this->manager = new SimpleCollisionManager();
    this->manager = new QuadTreeCollisionManager(3, width, height);

    entities.push_back(createEntity(manager, Vec2D(140, 100), Vec2D(2,0)));
    entities.push_back(createEntity(manager, Vec2D(440, 100), Vec2D(-1,0)));
/*

    // Overlap Right-Left
    entities.push_back(createEntity(manager, Vec2D(148,20)));
    entities.push_back(createEntity(manager, Vec2D(151,20)));

    // Overlap Bottom-Top
    entities.push_back(createEntity(manager, Vec2D(50,148)));
    entities.push_back(createEntity(manager, Vec2D(50,151)));

*/
    for(int i = 0; i < 1000; i++){
        float rX = rand()%width;
        float rY = rand()%height;

        Vec2D vel(rX > width / 2.0 ? -1 : 1, rY > height / 2.0 ? -1 : 1);
        entities.push_back(createEntity(manager, Vec2D(rX, rY), vel));
    }
}

Scene::~Scene() {
    for(const auto& entity: entities) {
        delete entity;
    }
    delete this->manager;
}

auto lastTime = std::time(0);
int nbFrames = 0;

void Scene::update() {
    auto currentTime = std::time(0);
    nbFrames++;
    if ( currentTime - lastTime >= 1.0 ){
        printf("%f ms/frame\n", 1000.0/double(nbFrames));
        nbFrames = 0;
        lastTime += 1.0;
    }

    for(const auto& entity: entities){
        entity->update();
    }
}

void drawChildren (Box *box){
    if(box->children.empty()){
        float centerX = box->left + ((box->right - box->left ) / 2);
        float centerY = box->top + ((box->bottom - box->top) / 2);
        glPushMatrix();
        glTranslatef(centerX, centerY, 0);
        glColor3f(0, 1, 0);
        glutWireCube(box->right - box->left);
        glPopMatrix();
    }

    for(const auto& child: box->children) {
        drawChildren(child);
    }
}

void Scene::draw() {

    auto bvhManager = dynamic_cast<QuadTreeCollisionManager*>(manager);
    if(bvhManager != nullptr) {
        drawChildren(bvhManager->getRoot());
    }

    for(const auto& entity: entities) {
        entity->draw();
    }
}

