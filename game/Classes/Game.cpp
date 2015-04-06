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
        if (nodeA->getTag() == WALL_TAG)
        {
	  cout << "WALL" << endl;
        }
        else if (nodeB->getTag() == WALL_TAG)
        {
	  cout << "WALL" << endl;
        }
	else if(nodeB->getTag() == GROUND_TAG || nodeA->getTag() == GROUND_TAG)
	  player.setJumping(false);
    }

    return true;
}

Scene* Game::createScene()
{
    auto scene = Scene::createWithPhysics();
    auto layer = Game::create();
    scene->addChild(layer);   
    // Increasing Gravity
    scene->getPhysicsWorld()->setGravity(Vec2(0,-150));
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
  // Creating GROUND 1
  this->addChild(obs.create(0.0,0.0,1200.0,0,GROUND_TAG));
  // Creating GROUND 2
  this->addChild(obs.create(1500,0.0,300.0,0,GROUND_TAG));
  // Creating GROUND 3
  this->addChild(obs.create(2385.0,0.0,1200.0,0,GROUND_TAG));
  // Creating WALL
  this->addChild(obs.create(3000.0,1.0,900.0,1,WALL_TAG));
 
  // Creating Player
  this->addChild(player.createPlayer(250));
  
  Point p = player.getPosition();
  
  // Creating Camera
  auto size = Director::getInstance()->getWinSize();  
  this->setCameraMask((unsigned short)CameraFlag::USER2, true);
  camera.create(size);
  this->addChild(camera.getCamera());

  // Creating Keyboard listener
  this->_eventDispatcher->addEventListenerWithSceneGraphPriority(receiver.create(),this);

  this->scheduleUpdate();
  return true;
}

void Game::update(float dt){ 
  // Updating camera, following player
  Point p = player.getPosition();
  camera.update(Vec3(p.x, p.y, 0));

  // Updating player velocity
  player.updateVelocity(dt*BASE_VEL);
  
  // Timer
  time += dt;
  cout << time << endl;
  
  //Player jumping
  if(receiver.IsKeyPressed(JUMP_KEY) && !player.isJumping())
    player.jump();

  // Reseting player position if it died
  Vec2 bp = player.getSprite()->getPhysicsBody()->getPosition();
  if(p.y < 0){
    player.setPosition(100,163.9);
    p = player.getPosition();
    time = 0.0;
  }
}
