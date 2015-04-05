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

  Obstacles obs;
  //create(float xi, float level, float size, int direction , int type)
  // Creating GROUND
  this->addChild(obs.create(0.0,0.0,1200.0,0,GROUND));
  // Creating WALL
  //this->addChild(obs.create(500.0,1.0,900.0,1,WALL));
 
  // Creating Player
  this->addChild(player.createPlayer(150));
  
  Point p = player.getPosition();
  
  // Creating Camera
  auto size = Director::getInstance()->getWinSize();  
  this->setCameraMask((unsigned short)CameraFlag::USER2, true);
  camera.create(size);
  this->addChild(camera.getCamera());

  this->scheduleUpdate();
  return true;
}

void Game::update(float dt){ 
  // Updating camera, following player
  Point p = player.getPosition();
  camera.update(Vec3(p.x, p.y, 0));
  
  // Updating player velocity
  player.updateVelocity(dt*BASEVEL);
  
  // Timer
  time += dt;
  //cout << total << endl;
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
