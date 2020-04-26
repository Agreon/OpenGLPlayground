//
// Created by daniel on 24.04.20.
//

#include <iostream>
#include "QuadTreeCollisionManager.h"

QuadTreeCollisionManager::QuadTreeCollisionManager(const int &depth, const int &sceneWidth,
                                                   const int &sceneHeight) {
    this->root = Box(nullptr, 0, 0, sceneWidth, sceneHeight);
    this->constructBoxes(this->root, depth );
}

vector<PhysicsComponent *> QuadTreeCollisionManager::getCollisionObjects(PhysicsComponent *entity) {

    vector<Box*> boxes = this->entityBoxes[entity];
    vector<Box*> newBoxes = boxes;

    bool checkedAdjacent = false;

    for(auto box : boxes) {
        float overlapLeft = box->left - (entity->position.x - entity->halfWidth);
        float overlapRight = (entity->position.x + entity->halfWidth) - box->right;
        float overlapTop = box->top - (entity->position.y - entity->halfHeight);
        float overlapBottom = (entity->position.y + entity->halfHeight) - box->bottom;

        /**
         * Here we have three cases
         * 1: The entity is still in the box. (Most common)
         * 2: The entity left the box completely.
         * 3: The entity is still in the box, but touches other boxes => just Check the other boxes
         */

        // 1: No other boxes are touched => Just continue
        if(overlapLeft < 0 && overlapRight < 0 && overlapBottom < 0 && overlapTop < 0) {
            continue;
        }

        // 2: Entity left the box => Remove the relation
        if((overlapRight > entity->width || overlapLeft > entity->width || overlapTop > entity->height || overlapBottom > entity->height)) {
            // Delete entity from box-list
            box->removeEntity(entity);

            // Delete box from entity-map
            int pos2 = 0;
            for(int i = 0; i< newBoxes.size(); i++){
                if(newBoxes[i] == box) {
                    pos2 = i;
                    break;
                }
            }
            newBoxes.erase(newBoxes.begin() + pos2);
        }

        /**
          * Now we are sure the entity touches other boxes. So we got to find them.
        */

        /** The search just hast to be executed once.
          * Done in the loop, because overlaps are already calculated
        */
        if(checkedAdjacent) continue;
        else checkedAdjacent = true;

        vector<Vec2D> searchPoints = generateSearchPointsForAdjacentBoxes(box, entity, overlapLeft, overlapRight, overlapTop, overlapBottom);

        // Find searched boxes
        for(auto point : searchPoints) {
            // TODO: Can this be done better?
            // Filter search by existing boxes
            bool foundExistingBox = false;
            for(auto existingBox : newBoxes) {
                if(existingBox != box && existingBox->includes(point)) {
                    foundExistingBox = true;
                    break;
                }
            }

            // Just skip because box was or will be checked
            if(foundExistingBox) continue;

            // Otherwise we will have to search in the tree
            Box* b = this->findBoxByPointUpward(box, point);

            newBoxes.push_back(b);
            newBoxes.back()->addEntity(entity);
        }
    }

    this->entityBoxes[entity] = newBoxes;

    // Check all relevant boxes
    vector<PhysicsComponent*> collisions;

    for(auto box : this->entityBoxes[entity]) {
        for(auto e : box->entities){
            if(e != entity && entity->collides(e)) {
                collisions.push_back(e);
            }
        }
    }

    return collisions;
}

/**
 * Generates points where we have to search for adjacent boxes.
 * Exclude those outside of the world.
 */
vector<Vec2D> QuadTreeCollisionManager::generateSearchPointsForAdjacentBoxes(Box *originBox, PhysicsComponent *entity,
                                                                             const float &overlapLeft,
                                                                             const float &overlapRight,
                                                                             const float &overlapTop,
                                                                             const float &overlapBottom) const {
    vector<Vec2D> searchPoints;
    float searchX = 0, searchY = 0;

    if(overlapLeft > 0) {
        searchX = originBox->left - overlapLeft;
        if(searchX > 0 && !(entity->position.y < 0 || entity->position.y > root.bottom)){
            searchPoints.emplace_back(Vec2D(searchX, entity->position.y));
        }
    } else if(overlapRight > 0) {
        searchX = originBox->right + overlapRight;
        if(searchX < root.right && !(entity->position.y < 0 || entity->position.y > root.bottom)){
            searchPoints.emplace_back(Vec2D(searchX, entity->position.y));
        }
    }

    if(overlapTop > 0) {
        searchY = originBox->top - overlapTop;
        if(searchY > 0 && !(entity->position.x < 0 || entity->position.x > root.right)) {
            searchPoints.emplace_back(Vec2D(entity->position.x, searchY));
        }
    } else if(overlapBottom > 0) {
        searchY = originBox->bottom + overlapBottom;
        if (searchY < root.bottom && !(entity->position.x < 0 || entity->position.x > root.right)){
            searchPoints.emplace_back(Vec2D(entity->position.x, searchY));
        }
    }

    // Worst case: Entity overlaps 4 boxes
    if(searchPoints.size() == 2){
        searchPoints.emplace_back(Vec2D(searchX, searchY));
    }

    return searchPoints;
}


/**
 * Searches the tree upward for a box containing the searched point.
 * @param originBox
 * @param point
 * @return The Box containing the point
 */
Box* QuadTreeCollisionManager::findBoxByPointUpward(Box *originBox, const Vec2D &point) {
    vector<Box*> &siblings = originBox->parent->children;

    for(auto sibling : siblings) {
        if(originBox != sibling && sibling->includes(point)){
            // Otherwise we have to search downward
            return findBoxByPointDownward(sibling, point);
        }
    }

    // If point was not part of the siblings, we have to search a level higher
    return findBoxByPointUpward(originBox->parent, point);
}

/**
 * Searches the tree downward for a box containing the searched point.
 * @param originBox
 * @param point
 * @return The Box containing the point
 */
Box* QuadTreeCollisionManager::findBoxByPointDownward(Box *parent, const Vec2D& point){
    if(parent->children.empty()) {
        return parent;
    }

    for(auto child : parent->children) {
        if(child->includes(point)) {
            return findBoxByPointDownward(child, point);
        }
    }

    return nullptr;
}

void QuadTreeCollisionManager::constructBoxes(Box &parent, const int &depth) {

    float boxWidth = (parent.right - parent.left) / 2;
    float boxHeight = (parent.bottom - parent.top) / 2;

    // Upper Left
    parent.children.push_back(new Box(&parent, parent.left, parent.top, parent.left + boxWidth, parent.bottom - boxHeight));
    // Upper Right
    parent.children.push_back(new Box(&parent, parent.left + boxWidth, parent.top, parent.right, parent.bottom - boxHeight));
    // Lower Left
    parent.children.push_back(new Box(&parent, parent.left, parent.top + boxHeight, parent.left + boxWidth, parent.bottom));
    // Lower Right
    parent.children.push_back(new Box(&parent, parent.left + boxWidth, parent.top + boxHeight, parent.right, parent.bottom));

    if(depth > 1){
        for(auto child: parent.children){
            this->constructBoxes(*child, depth - 1);
        }
    }
}

void QuadTreeCollisionManager::registerEntity(PhysicsComponent *entity) {
    this->assignEntityToBox(entity, this->root);
}


void QuadTreeCollisionManager::assignEntityToBox(PhysicsComponent *entity, Box &parent) {
    if(parent.children.empty()) {
        parent.addEntity(entity);
        this->entityBoxes[entity].push_back(&parent);
        return;
    }

    for(auto child : parent.children) {
        if(child->includes(*entity)) {
            assignEntityToBox(entity, *child);
        }
    }
}

Box &QuadTreeCollisionManager::getRoot() {
    return root;
}

