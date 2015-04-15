#include "Obstacles.h"

USING_NS_CC;


/*  
 *   xi = First x position
 *   level = high of the platform 0 for ground, 1 for above the ground
 *   size = the size of the obstacle
 *   direction = 1: Vertical  |   0: Horizontal
 *   type = Definifion types on Obstacles.h
*/

DrawNode* Obstacles::create(float xi, float level, float size, int type)
{
  DrawNode* obstacle = DrawNode::create();
  float x, yi , y;
  if(type == WALL_TAG){
    x = xi + WALL_SIZE;
    yi = lastGround + (level * JUMP_HEIGHT);
    y = yi + size;
  }
  else if(type == GROUND_TAG){
    x = xi + size;
    yi = 0;
    y = yi + GROUND_SIZE;
    lastGround = y;
    lastSize = GROUND_SIZE;
  }
  else{
    x = xi + size;
    if(level)
      yi = lastGround + (JUMP_HEIGHT * level);
    else
      yi = lastGround - lastSize;
    y = yi + WALL_SIZE;
    lastGround = y;
    lastSize = WALL_SIZE;
  }
  Vec2 vertices2[] = { 
    Vec2(x,y), 
    Vec2(x,yi), 
    Vec2(xi,yi), 
    Vec2(xi,y)
  };   
  obstacle->drawPolygon(vertices2, 4, Color4F(1.0f,0.3f,0.3f,1), 3, Color4F(0.2f,0.2f,0.2f,1));
  auto physicsBody = PhysicsBody::createPolygon(vertices2, 4);
  physicsBody->setDynamic(false);
  physicsBody->setContactTestBitmask(0x01);
  obstacle->setTag(type);
  obstacle->setPhysicsBody(physicsBody);
  return obstacle;
}
