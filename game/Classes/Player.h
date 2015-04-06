#include "cocos2d.h"

#define MAXVELOCITY 600

class Player
{
 public:
  cocos2d::SpriteBatchNode* createPlayer(float vel);
  cocos2d::Sprite* getSprite();
  float getNormalVelocity();
  float getCurrentVelocity();
  cocos2d::Point getPosition();
  void setPosition(float x, float y);  
  void updateVelocity(float velocity);
  void jump();
  bool isJumping();
  void setJumping(bool x);
 private:
  cocos2d::SpriteFrameCache* cache;
  float normalVelocity;
  cocos2d::Sprite* Sprite;
  bool jumping = false;
};
