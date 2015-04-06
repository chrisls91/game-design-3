#include "cocos2d.h"

#define WALL_TAG 1
#define GROUND_TAG 2
#define PLAYER_TAG 3
#define OBSTACLE_SIZE 40
#define JUMP_HEIGHT 100

class Obstacles
{
 public:
  cocos2d::DrawNode* create(float xi, float level, float size, int direction , int type);
};
