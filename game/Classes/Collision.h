#include "cocos2d.h"

#define WALL 1
#define GROUND 2
#define PLAYER 3

using namespace cocos2d;

class CollisionManager
{
  bool onContactBegin(PhysicsContact& contact);
};
