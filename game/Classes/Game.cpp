#include "Game.h"
#include <iomanip>
#include <iostream>

USING_NS_CC;
using namespace std;

// Collision Detection
bool Game::onContactBegin(PhysicsContact& contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    if (nodeA && nodeB)
    {
        if (nodeA->getTag() == WALL)
        {
	  cout << "WALL" << endl;
        }
        else if (nodeB->getTag() == WALL)
        {
	  cout << "WALL" << endl;
        }
    }

    return true;
}

Scene* Game::createScene()
{
    auto scene = Scene::createWithPhysics();
    auto layer = Game::create();
    scene->addChild(layer);   
    return scene;
}

bool Game::init()
{   
  if ( !Layer::init() ){
        return false;
  }

  // Setting collision manager
  //adds contact event listener
  auto contactListener = EventListenerPhysicsContact::create();
  contactListener->onContactBegin = CC_CALLBACK_1(Game::onContactBegin, this);
  _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

  // Creating Ground   
  auto rectWithBorder = DrawNode::create();
  Vec2 vertices[] = { 
    Vec2(3,100), 
    Vec2(1000,100), 
    Vec2(1000,4), 
    Vec2(3,4)
  };
  
  rectWithBorder->drawPolygon(vertices, 4, Color4F(1.0f,0.3f,0.3f,1), 3, Color4F(0.2f,0.2f,0.2f,1));
  auto physicsBody = PhysicsBody::createPolygon(vertices,4);
  addChild(rectWithBorder);
  physicsBody->setDynamic(false);
  rectWithBorder->setTag(GROUND);
  physicsBody->setContactTestBitmask(0x02);
  physicsBody->setVelocity(Vec2(-player.getVelocity(),0));
  rectWithBorder->setPhysicsBody(physicsBody); 
  
  // Testing wall    
  rectWithBorder = DrawNode::create();
  Vec2 vertices2[] = { 
    Vec2(510,900), 
    Vec2(510,0), 
    Vec2(500,0), 
    Vec2(500,900)
  };   
  rectWithBorder->drawPolygon(vertices2, 4, Color4F(1.0f,0.3f,0.3f,1), 3, Color4F(0.2f,0.2f,0.2f,1));
  physicsBody = PhysicsBody::createPolygon(vertices2, 4);
  this->addChild(rectWithBorder);
  physicsBody->setDynamic(false);
  rectWithBorder->setTag(WALL);
  physicsBody->setContactTestBitmask(0x01);
  rectWithBorder->setPhysicsBody(physicsBody);
  
  // Create Player
  this->addChild(player.createPlayer(150));
  
  // Create Following Camera
  auto size = Director::getInstance()->getWinSize();

  // Code mess up with the following camera
  //this->runAction(Follow::create(player.getSprite(), Rect(-500,0,size.width*100000, size.height*2)));

  this->scheduleUpdate();
  return true;
}

void Game::update(float dt){    
  player.setVelocity();
  Point p = player.getPosition();
  Vec2 bp = player.getSprite()->getPhysicsBody()->getPosition();
  if(p.y < 0){
    player.setPosition(100,163.9);
    p = player.getPosition();
  }
  /*
  cout << "============" << endl;
  cout << "Sprite:" << p.x << " " << p.y << endl;
  cout << "Body:" << bp.x << " " << bp.y << endl;
  cout << "Total:" << p.x - bp.x << " " << p.y - bp.y << endl;
  cout << "============" << endl;
  */
  //player.setPosition(p.x + player.getVelocity() * dt, p.y );
  //player.setPosition(p.x, p.y);
}
