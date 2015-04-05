#include "cocos2d.h"

#define WALL 1
#define GROUND 2
#define PLAYER 3
#define SIZE 40
#define JUMP 100

class Obstacles
{
 public:
  cocos2d::DrawNode* create(float xi, float level, float size, int direction , int type);
};
