//
//  Pickups.cpp
//  MyGame
//
//  Created by Chris Stewart on 4/13/15.
//
//

#include "Pickups.h"
#include <iostream>

USING_NS_CC;
using namespace std;

SpriteBatchNode* SpeedPickup::createSpeedPickup(float x_pos, float y_pos){
    // Create pickup sprite
    SpriteBatchNode* spritebatch = SpriteBatchNode::create("cookie_pickup.png");
    Sprite = Sprite::create("cookie_pickup.png");
    spritebatch->addChild(Sprite);
    Sprite->setTag(4);
    //Sprite->getContentSize()
    auto physicsBody = PhysicsBody::createBox(Size(60,47), PhysicsMaterial(1.0f,0.0f,0.f));
    physicsBody->setContactTestBitmask(0x01);
    physicsBody->setRotationEnable(false);
    physicsBody->setGravityEnable(false);
    Sprite->setPhysicsBody(physicsBody);
    Sprite->setPosition(x_pos,y_pos);
    return spritebatch;
}

Sprite* SpeedPickup::getSprite(){
    return Sprite;
}

Point SpeedPickup::getPosition(){
    return Sprite->getPosition();
}

void SpeedPickup::setPosition(float x, float y){
    Sprite->setPosition(x,y);
}