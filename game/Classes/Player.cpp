#include "Player.h"
#include <iostream>

USING_NS_CC;

SpriteBatchNode* Player::createPlayer(float vel){
   // Creating Caracter and Physics  
    SpriteBatchNode* spritebatch = SpriteBatchNode::create("stick.png");

    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("stick.plist");

    Sprite = Sprite::createWithSpriteFrameName("jump-9.png");
    spritebatch->addChild(Sprite);
    Sprite->setTag(3);
    auto physicsBody = PhysicsBody::createBox(Sprite->getContentSize(), PhysicsMaterial(1.0f,0.0f,0.f));
    physicsBody->setVelocity(Vec2(vel,0));
    physicsBody->setContactTestBitmask(0x01);
    physicsBody->setRotationEnable(false);
    //physicsBody->setGravityEnable(false);
    Sprite->setPhysicsBody(physicsBody);
    
    Vector<SpriteFrame*> animFrames(5);

    char str[100] = {0};
    for(int i = 1; i < 5; i++) {
	sprintf(str, "run-%d.png", i);
	SpriteFrame* frame = cache->getSpriteFrameByName( str );
	animFrames.pushBack(frame);
    }

    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
    Sprite->runAction( RepeatForever::create( Animate::create(animation) ) );
    Sprite->setPosition(100,163.9);
    Sprite->setFlippedX(true);
    Velocity = vel;
    return spritebatch;
}

Sprite* Player::getSprite(){
  return Sprite;
}

float Player::getVelocity(){
  return Velocity;
}

Point Player::getPosition(){
  return Sprite->getPosition();
}

void Player::setPosition(float x, float y){
  Sprite->setPosition(x,y);
}

void Player::setVelocity(){
  Vec2 vel = Sprite->getPhysicsBody()->getVelocity();
  Sprite->getPhysicsBody()->setVelocity(Vec2(Velocity,vel.y));
}
