#pragma once
#include "cocos2d.h"

class CameraControl
{
 public:
  void create(cocos2d::Size size);
  void update(cocos2d::Vec3 playerPos);
  cocos2d::Camera* getCamera();;
 private:
  cocos2d::Camera* camera;
  cocos2d::Size winSize;
};
