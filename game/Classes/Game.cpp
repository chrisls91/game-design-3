#include "Game.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

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
          player.increaseXVelocity(2.4);
          nodeA->getPhysicsBody()->removeFromWorld();
          auto parentNode = nodeA->getParent();
          nodeA->removeFromParentAndCleanup(true);
          parentNode->removeFromParentAndCleanup(true);
        }
        else if (nodeB->getTag() == PICKUP_TAG and nodeA->getTag() == PLAYER_TAG){
          player.increaseXVelocity(2.4);
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
  
  //Add and setup touch event listener
  #if ((CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID))
  auto touchListener = EventListenerTouchOneByOne::create();
  touchListener->onTouchBegan = CC_CALLBACK_2(Game::onTouchBegan, this);
  touchListener->onTouchEnded = CC_CALLBACK_2(Game::onTouchEnded, this);
  _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
  #endif

  Obstacles obs;
  SpeedPickup pickup;

  float startX, startY;
  ifstream source;
  //string levelStr = "Resources/data/data" + to_string(level);
  string levelStr = "data/data" + to_string(level);
  source.open(levelStr, ios_base::in);
  
  if(!source)
    cerr << "Can't open Data!\n";
  
  for(string line; getline(source, line); ){
    istringstream in(line);
    int option, x4;
    float x1, x2, x3;
    in >> option >> x1 >> x2 >> x3 >> x4;
    switch(option){
      // Setting start position
    case 0:
      startX = x1;
      startY = x2;
      break;
      // Adding ground type 1
    case 1:
      this->addChild(obs.create(x1, x2, x3, GROUND_TAG, x4));
      break;
      // Adding ground type 2
    case 2:
      this->addChild(obs.create(x1, x2, x3, GROUND2_TAG, x4));
      break;
      // Adding Wall
    case 3:
      this->addChild(obs.create(x1, x2, x3, WALL_TAG, x4));
      break;
      // Adding PickUps
    case 4:
      this->addChild(pickup.createSpeedPickup(x1, x2));
      break;
    case 5:
      endX = x1;
      break;
    }
  }
 
  // Creating Player
  this->addChild(player.createPlayer(350, startX, startY));
  
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
  audio = CocosDenshion::SimpleAudioEngine::getInstance();
  audio->playBackgroundMusic("bg1.mp3", true);
  audio->preloadEffect("jump.wav");
  audio->setBackgroundMusicVolume(10.0f);
  audio->setEffectsVolume(0.5f);

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

#if ((CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID))
bool Game::onTouchBegan(Touch* touch,Event* event){
  if(touch->getLocation().x <= winSize.width/2){
    if(!player.isJumping()){
      audio->playEffect("jump.wav");
      player.jump(1);
    }
    else if(player.isJumping() == 1){
      audio->playEffect("jump.wav");
      player.jump(2);
    }
  }
  else{
    slideTouchHeld = true;
  }
  
  return true;
}

void Game::onTouchEnded(Touch* touch, Event* event){
  if(touch->getLocation().x > winSize.width/2){
    slideTouchHeld = false;
  }
}
#endif

void Game::update(float dt){ 
  if(paused){
    if(receiver.IsKeyPressed(SLIDE_KEY)){      
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
    player.updateVelocity(dt*(-BASE_VEL/3));
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
   
  // Slide Timing
  if((receiver.IsKeyPressed(SLIDE_KEY) || slideTouchHeld) && !slideTimer)
    slideTimer = 1;

  if(slideTimer < 0)
    slideTimer = (slideTimer + dt*1000 > 0)? 0:slideTimer + dt*1000;

  //Player jumping
  if(receiver.IsKeyPressed(JUMP_KEY) && !slideTimer){
    receiver.releaseKey(JUMP_KEY);
  if(!player.isJumping()){
      audio->playEffect("jump.wav");
      player.jump(1);
    }
    else if(player.isJumping() == 1){
      audio->playEffect("jump.wav");
      player.jump(2);
    }
  }
  else if(slideTimer > SLIDE_TIME){
    slideTimer = -SLIDE_TIME/2;
    player.endSlide();
  }
  else if(slideTimer > 0){
    player.slide();
    slideTimer += dt*1000;
  }
 
  // Reseting player position if it died
  Vec2 bp = player.getSprite()->getPhysicsBody()->getPosition();
  if(p.y < 0){        
    auto tmpScene = this->createScene();
    Director::getInstance()->replaceScene(tmpScene);
  }
  if(p.x > endX){
    auto scene = CompleteMenu::createScene(time);
    Director::getInstance()->replaceScene(scene);
  }
}
