//
// Created by daniel on 24.04.20.
//

#ifndef PHYSICS_QUADTREECOLLISIONMANAGER_H
#define PHYSICS_QUADTREECOLLISIONMANAGER_H

#include <map>

#include "../CollisionManager.h"
#include "Box.h"

class QuadTreeCollisionManager : public CollisionManager {
public:
    QuadTreeCollisionManager(const int& depth, const int& sceneWidth, const int& sceneHeight);
    void registerEntity(PhysicsComponent *entity) override;
    vector<PhysicsComponent*> getCollisionObjects(PhysicsComponent *entity) override;

    Box& getRoot();
private:
    Box root;
    map<PhysicsComponent*, vector<Box*>> entityBoxes;

    void constructBoxes(Box& parent, const int& depth);
    void assignEntityToBox(PhysicsComponent* entity, Box& box);

    vector<Vec2D> generateSearchPointsForAdjacentBoxes(Box* originBox, PhysicsComponent* entity, const float& overlapLeft, const float& overlapRight, const float& overlapTop, const float& overlapBottom) const;
    Box* findBoxByPointUpward(Box* originBox, const Vec2D& point);
    Box* findBoxByPointDownward(Box* parent, const Vec2D& point);
};


#endif //PHYSICS_QUADTREECOLLISIONMANAGER_H
