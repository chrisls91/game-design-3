#pragma once
#include "cocos2d.h"

#define MAXVELOCITY 1500
#define BASE_VEL 200
#define SLIDE_TIME 800

class Player
{
 public:
  cocos2d::SpriteBatchNode* createPlayer(float vel, float x, float y);
  cocos2d::Sprite* getSprite();
  float getNormalVelocity();
  float getCurrentVelocity();
  cocos2d::Point getPosition();
  void setPosition(float x, float y);  
  void updateVelocity(float velocity);
  void increaseXVelocity(float velocity);
  void setVelocity(float vel);
  void jump(int n);
  int isJumping();
  void setJumping(int x);
  void slide();
  void endSlide();
  void resetPlayer(float x, float y);
  void stopPlayer();

 private:
  cocos2d::SpriteFrameCache* cache;
  float normalVelocity;
  cocos2d::Sprite* Sprite;
  int jumping = false;
};
