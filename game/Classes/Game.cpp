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
        else if (nodeA->getTag() == PICKUP_TAG and nodeB->getTag() == PLAYER_TAG){
          player.updateVelocity(player.getCurrentVelocity()*2.5);
          nodeA->getPhysicsBody()->removeFromWorld();
          auto parentNode = nodeA->getParent();
          nodeA->removeFromParentAndCleanup(true);
          parentNode->removeFromParentAndCleanup(true);
        }
        else if (nodeB->getTag() == PICKUP_TAG and nodeA->getTag() == PLAYER_TAG){
          player.updateVelocity(player.getCurrentVelocity()*2.5);
          nodeB->getPhysicsBody()->removeFromWorld();
          auto parentNode = nodeB->getParent();
          nodeB->removeFromParentAndCleanup(true);
          parentNode->removeFromParentAndCleanup(true);
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
  SpeedPickup pickup;
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
  // Creating pickup 1
  this->addChild(pickup.createSpeedPickup(4320.0, 250));
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
  // Creating pickup1
  this->addChild(pickup.createSpeedPickup(8200,3080));
  this->addChild(pickup.createSpeedPickup(8600, 3080));
  this->addChild(pickup.createSpeedPickup(8900, 3080));
  

  // lvl 3
  // Creating GROUND2 1
  this->addChild(obs.create(3400.0, 1, 1000.0,GROUND2_TAG));
  // Creating WALL 1
  this->addChild(obs.create(3800.0, 0.5, 500.0,WALL_TAG));
  //Creating Pickup1
  this->addChild(pickup.createSpeedPickup(3800.0, 450));

  // lvl 4
  // Creating GROUND2 1
  this->addChild(obs.create(4400.0, 1, 1200.0,GROUND2_TAG));
  // Creating GROUND2 1
  this->addChild(obs.create(6000.0, 0, 1900.0,GROUND2_TAG));
  // Creating WALL 1
  this->addChild(obs.create(5200.0, 0, 75.0,WALL_TAG));
  // Creating WALL 2
  this->addChild(obs.create(5200.0, 1.5, 350.0,WALL_TAG));
  // Creating pickup 1
  this->addChild(pickup.createSpeedPickup(5800, 375.0));
  // Creating pickup 2
  this->addChild(pickup.createSpeedPickup(6000, 1000));
  
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
  
  //Start BGM
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bg1.mp3", true);
  
  this->scheduleUpdate();
  return true;
}

void Game::reloadPickups(){
  //todo: Have a for loop that reads the number of pickups
  //and their coordinates from a file
  SpeedPickup pickup;
  auto node=pickup.createSpeedPickup(900.0, 80);
  this->addChild(node);
  node=pickup.createSpeedPickup(400.0, 120);
  this->addChild(node);
}

void Game::update(float dt){ 
  if(paused){
    if(receiver.IsKeyPressed(SLIDE_KEY)){
      player.resetPlayer(100,163.9);
      time = 0.0;
      paused = false;
      auto tmpScene = this->createScene();
      Director::getInstance()->replaceScene(tmpScene);
    }
    return;
  }
  // Updating camera, following player
  Point p = player.getPosition();
  camera.update(Vec3(p.x, p.y, 0));

  // Updating player velocity
  if(player.getCurrentVelocity()>player.getNormalVelocity()){
    player.updateVelocity(dt*(-BASE_VEL));
  }
  else{
    player.updateVelocity(dt*BASE_VEL);
  }
  
  // Timer
  time += dt*1000;
  int ms = (int) time%1000;
  int sec = (int) (time/1000)%60;
  int min = (time/1000)/60;
  label->setString(((min>0)?to_string(min) + ":":"") + to_string(sec) + ":" + to_string(ms));
  
  //Player jumping
  if(receiver.IsKeyPressed(JUMP_KEY)){
    receiver.releaseKey(JUMP_KEY);
    if(!player.isJumping()){
      CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("jump.wav");
      player.jump(1);
    }
    else if(player.isJumping() == 1){
      CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("jump.wav");
      player.jump(2);
    }
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
    player.resetPlayer(100,163.9);
    time = 0.0;
    auto tmpScene = this->createScene();
    Director::getInstance()->replaceScene(tmpScene);
  }
  if(p.x > 10930){
    paused = true;
    player.stopPlayer();
  }
}
