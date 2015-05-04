#include "Player.h"
#include <iostream>

USING_NS_CC;
using namespace std;

SpriteBatchNode* Player::createPlayer(float vel, float x, float y){
   // Creating Caracter and Physics  
    SpriteBatchNode* spritebatch = SpriteBatchNode::create("stick.png");

    cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("stick.plist");

    Sprite = Sprite::createWithSpriteFrameName("jump-9.png");
    spritebatch->addChild(Sprite);
    Sprite->setTag(3);
    //Sprite->getContentSize()
    auto physicsBody = PhysicsBody::createBox(Size(60,128), PhysicsMaterial(1.0f,0.0f,0.f));
    physicsBody->setVelocity(Vec2(100,0));
    physicsBody->setContactTestBitmask(0x01);
    physicsBody->setRotationEnable(false);
    Sprite->setPhysicsBody(physicsBody);
    
    // Running animation
    Vector<SpriteFrame*> animFrames(5);

    char str[100] = {0};
    for(int i = 1; i < 5; i++) {
	sprintf(str, "run-%d.png", i);
	SpriteFrame* frame = cache->getSpriteFrameByName( str );
	animFrames.pushBack(frame);
    }

    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
    Sprite->runAction( RepeatForever::create( Animate::create(animation) ) );
    Sprite->setPosition(x,y);
    Sprite->setFlippedX(true);
    normalVelocity = vel;
    return spritebatch;
}

Sprite* Player::getSprite(){
  return Sprite;
}

float Player::getCurrentVelocity(){
  Vec2 vel = Sprite->getPhysicsBody()->getVelocity();
  return vel.x;
}

Point Player::getPosition(){
  return Sprite->getPosition();
}

float Player::getNormalVelocity(){
    return normalVelocity;
}

void Player::setPosition(float x, float y){
  Sprite->setPosition(x,y);
}

void Player::resetPlayer(float x, float y){
  setPosition(x,y);
  Sprite->resumeSchedulerAndActions();
  Sprite->getPhysicsBody()->setVelocity(Vec2(100,0));
}

//Increases X velocity by a given multiple
void Player::increaseXVelocity(float multiple){
    Vec2 currentV = Sprite->getPhysicsBody()->getVelocity();
    Sprite->getPhysicsBody()->setVelocity(Vec2((currentV.x*multiple),currentV.y));
}

void Player::setVelocity(float vel){
  Sprite->getPhysicsBody()->setVelocity(Vec2(vel,0));
}

void Player::updateVelocity(float velocity){
  Vec2 vel = Sprite->getPhysicsBody()->getVelocity();
  Sprite->getPhysicsBody()->setVelocity(Vec2(((vel.x+velocity>MAXVELOCITY)?MAXVELOCITY:(vel.x+velocity)),vel.y));
}

void Player::stopPlayer(){
  Sprite->pauseSchedulerAndActions();
  Sprite->getPhysicsBody()->setVelocity(Vec2(0,0));
}

void Player::setJumping(int x){
  jumping = x;
}

int Player::isJumping(){
  return jumping; //((Sprite->getPhysicsBody()->getVelocity().y != 0)?true:false);
}

void Player::jump(int n){
  // Jumping animation
  Vector<SpriteFrame*> animFrames(5);
  
  char str[100] = {0};
  for(int i = 1; i < 5; i++) {
    sprintf(str, "jump-%d.png", i);
    SpriteFrame* frame = cache->getSpriteFrameByName( str );
    animFrames.pushBack(frame);
  }

  Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
  //Sprite->runAction( Animate::create(animation) );
  auto vel = getCurrentVelocity()-BASE_VEL/3;
  Sprite->getPhysicsBody()->setVelocity(Vec2(((vel>0)? vel:0), 150 * 2.5));
  jumping = n;
}

void Player::slide(){
  
  // Sliding animation
  Vector<SpriteFrame*> animFrames(1);
  
  char str[100] = {0};
  for(int i = 8; i < 9; i++) {
    sprintf(str, "jump-%d.png", i);
    SpriteFrame* frame = cache->getSpriteFrameByName( str );
    animFrames.pushBack(frame);
  }

  Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
  Sprite->runAction( Animate::create(animation) );  
  Sprite->setRotation(-90);
  Vec2 p = Sprite->getPhysicsBody()->getPosition();
  setPosition(p.x, p.y - 1.8);
}

void Player::endSlide(){
  Vec2 p = Sprite->getPhysicsBody()->getPosition();
  setPosition(p.x, p.y + 50);
  Sprite->setRotation(0);
}
