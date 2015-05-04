#include "Obstacles.h"

USING_NS_CC;


/*  
 *   xi = First x position
 *   level = high of the platform 0 for ground, 1 for above the ground
 *   size = the size of the obstacle
 *   direction = 1: Vertical  |   0: Horizontal
 *   type = Definifion types on Obstacles.h
*/

Sprite* Obstacles::create(float xi, float level, float size, int type, int textureType)
{
  DrawNode* tmp_obstacle = DrawNode::create();
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
  tmp_obstacle->drawPolygon(vertices2, 4, Color4F(1.0f,0.3f,0.3f,0.7f), 3, Color4F(0.2f,0.2f,0.2f,0.7f));

  //The way textures are being applied is a temporary hack to avoid changing
  //the existing code that generates vertices
  float textureWidth, textureHeight;
  if(type == WALL_TAG){
    textureWidth = WALL_SIZE;
    textureHeight = size;
  }
  else if(type == GROUND_TAG){
    textureWidth = size;
    textureHeight = GROUND_SIZE;
  }
  else{
    textureWidth = size;
    textureHeight = WALL_SIZE;
  }
  
  auto rt = RenderTexture::create(textureWidth,textureHeight);
  rt->beginWithClear(255,255,255,255);
  auto fill = Sprite::create("redbricktext.png");
  fill->setBlendFunc((BlendFunc){GL_DST_COLOR,GL_ZERO});
  fill->setPosition(0,textureHeight/2);
  fill->visit();
  //TODO: This is a crappy way of making sure all of the obstacles are filled
  //probably should implement a for loop and use smaller fill png files
  auto fill2 = Sprite::create("redbricktext.png");
  fill2->setBlendFunc((BlendFunc){GL_DST_COLOR,GL_ZERO});
  fill2->setPosition(2806,textureHeight/2);
  fill2->visit();

  rt->end();
  auto obstacle = Sprite::createWithTexture(rt->getSprite()->getTexture());
  
  //Use tmp_obstacle to set position of textured obstacle
  obstacle->setPosition(xi+(textureWidth/2),yi+(textureHeight/2));
  auto physicsBody = PhysicsBody::createBox(Size(textureWidth,textureHeight), PhysicsMaterial(1.0f,0.0f,0.f));
//  auto physicsBody = PhysicsBody::createPolygon(vertices2, 4);
  physicsBody->setDynamic(false);
  physicsBody->setContactTestBitmask(0x01);
  obstacle->setTag(type);
  obstacle->setPhysicsBody(physicsBody);
  return obstacle;
}
