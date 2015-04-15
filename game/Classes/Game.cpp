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
	  //cout << "WALL" << endl;
        }
        else if (nodeB->getTag() == WALL_TAG)
        {
	  //cout << "WALL" << endl;
        }
	else if(nodeB->getTag() == GROUND_TAG || nodeA->getTag() == GROUND_TAG || nodeB->getTag() == GROUND2_TAG || nodeA->getTag() == GROUND2_TAG)
	  player.setJumping(0);
    }
    return true;
}

Scene* Game::createScene()
{
    auto scene = Scene::createWithPhysics();
    auto layer = Game::create();
    scene->addChild(layer);   
    // Increasing Gravity
    scene->getPhysicsWorld()->setGravity(Vec2(0,-500));
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
  // lvl1
  //create(float xi, float level, float size, int type)
  // Creating GROUND 1
  this->addChild(obs.create(0.0, 0, 1200.0,GROUND_TAG));
  // Creating GROUND 2
  this->addChild(obs.create(1500, 0, 4000.0,GROUND_TAG));
  // Creating GROUND 3
  this->addChild(obs.create(6000, 0, 2000.0,GROUND_TAG));
  // Creating WALL 1
  this->addChild(obs.create(700.0, 0.5, 900.0,WALL_TAG));
  // Creating WALL 2
  this->addChild(obs.create(2500.0, 0.5, 63.0,WALL_TAG));
  // Creating WALL 4
  this->addChild(obs.create(4300.0, 0, 100.0,WALL_TAG));
  // Creating WALL 5
  this->addChild(obs.create(4800.0, 0.5, 100.0,WALL_TAG));
  // Creating WALL 6
  this->addChild(obs.create(6800.0, 0, 75.0,WALL_TAG));
  // Creating WALL 7
  this->addChild(obs.create(7000.0, 1, 320.0,WALL_TAG));
  // Creating WALL 5
  this->addChild(obs.create(7200.0, 0, 100.0,WALL_TAG));
  

  // lvl 2
  // Creating GROUND2 1
  this->addChild(obs.create(2250.0, 1, 1200.0,GROUND2_TAG));
  // Creating WALL 1
  this->addChild(obs.create(2800.0, 0.5, 400.0,WALL_TAG));
  // Creating GROUND2 2
  this->addChild(obs.create(7950.0, 0, 3000.0,GROUND2_TAG));
  

  // lvl 3
  // Creating GROUND2 1
  this->addChild(obs.create(3400.0, 1, 1000.0,GROUND2_TAG));
  // Creating WALL 1
  this->addChild(obs.create(3800.0, 0.5, 500.0,WALL_TAG));

  // lvl 4
  // Creating GROUND2 1
  this->addChild(obs.create(4400.0, 1, 1200.0,GROUND2_TAG));
  // Creating GROUND2 1
  this->addChild(obs.create(6000.0, 0, 1900.0,GROUND2_TAG));
  // Creating WALL 1
  this->addChild(obs.create(5200.0, 0, 75.0,WALL_TAG));
  // Creating WALL 2
  this->addChild(obs.create(5200.0, 1.5, 350.0,WALL_TAG));


  // Creating Player
  this->addChild(player.createPlayer(350));
  
  Point p = player.getPosition();
  
  // Creating Camera
  winSize = Director::getInstance()->getWinSize();  
  this->setCameraMask((unsigned short)CameraFlag::USER2, true);
  camera.create(winSize);
  this->addChild(camera.getCamera());

  //Creating timer display
  label = Label::createWithTTF("","fonts/arial.ttf",32);
  label->setPosition(Point(winSize.width/2, winSize.height-50));
  this->addChild(label);
  
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
  int min = (int) time/60;
  int sec = (int) time%60;
  label->setString(((min>0)?to_string(min) + ":":"") + to_string(sec));
  
  //Player jumping
  if(receiver.IsKeyPressed(JUMP_KEY)){
    receiver.releaseKey(JUMP_KEY);
    if(!player.isJumping())
      player.jump(1);
    else if(player.isJumping() == 1)
      player.jump(2);
  }
  else if(receiver.IsKeyPressed(SLIDE_KEY)){
    player.slide();
    status = true;
  }
  else if(status){
    player.endSlide();
    status = false;
  }
  // Reseting player position if it died
  Vec2 bp = player.getSprite()->getPhysicsBody()->getPosition();
  if(p.y < 0){
    player.setPosition(100,163.9);
    player.resetVelocity();
    p = player.getPosition();
    time = 0.0;
  }
}
