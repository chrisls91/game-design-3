#include "Obstacles.h"

USING_NS_CC;


/*  
 *   xi = First x position
 *   level = high of the platform 0 for ground, 1 for above the ground
 *   size = the size of the obstacle
 *   direction = 1: Vertical  |   0: Horizontal
 *   type = Definifion types on Obstacles.h
*/

DrawNode* Obstacles::create(float xi, float level, float size, int direction , int type)
{
  DrawNode* obstacle = DrawNode::create();
  float x, yi , y;
  if(direction && type != GROUND){
    x = xi + SIZE;
    yi = level * JUMP;
    y = yi + size;
  }
  else{
    x = xi + size;
    yi = level * JUMP;
    y = yi + ((type==GROUND)?96:SIZE);
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
  physicsBody->setContactTestBitmask(((type==GROUND)?0x01:0x02));
  obstacle->setTag(type);
  obstacle->setPhysicsBody(physicsBody);
  return obstacle;
}
