#include "cocos2d.h"

#define MAXVELOCITY 300

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
 private:
  float normalVelocity;
  cocos2d::Sprite* Sprite;
};
