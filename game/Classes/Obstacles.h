#include "cocos2d.h"

#define WALL_TAG 1
#define GROUND_TAG 2
#define GROUND2_TAG 3
#define PLAYER_TAG 3
#define GROUND_SIZE 96
#define WALL_SIZE 25
#define JUMP_HEIGHT 135

class Obstacles
{
 public:
  cocos2d::DrawNode* create(float xi, float level, float size, int type);
 private:
  float lastGround = 0;
  float lastSize = 0
};
