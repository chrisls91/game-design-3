//
//  LeaderBoard.cpp
//  gamename2
//
//  Created by will harrison on 4/23/15.
//
//

#include "LeaderBoard.h"
USING_NS_CC;
using namespace std;

Scene* LeaderBoard::createScene(){
  auto scene = Scene::create();
  auto layer = LeaderBoard::create();
  scene->addChild(layer);
  
  return scene;
}

bool LeaderBoard::init(){
  if ( !Layer::init() )
  {
    return false;
  }
  
  //Get size and origin for layout and placement
  winSize = Director::getInstance()->getWinSize();
  Point origin = Director::getInstance()->getVisibleOrigin();
  
  //Create a TTFConfig and set settings appropriately
  TTFConfig labelConfig;
  labelConfig.fontFilePath = "fonts/chowfun.ttf";
  labelConfig.fontSize = 42;
  labelConfig.glyphs = GlyphCollection::DYNAMIC;
  labelConfig.outlineSize = 0;
  labelConfig.customGlyphs = nullptr;
  labelConfig.distanceFieldEnabled = false;
  
  auto label1 = Label::createWithTTF("Leaderboard", "fonts/chowfun.ttf", 44);
  label1->setPosition(Point(winSize.width/2 - 150, winSize.height - 100 ));
  label1->setAnchorPoint(Point(0.0f, 0.0f));
  this->addChild(label1);
  
  for (int i = 0; i < 10; i++)
  {
    
    auto temp = Label::createWithTTF(std::to_string(i + 1) + ".    Leaderboard", "fonts/chowfun.ttf", 24);
    temp->setPosition(Point(winSize.width/2 - 250, winSize.height - 120 - (40 * (i + .5))));
    temp->setAnchorPoint(Point(0.0f, 0.0f));
    this->addChild(temp);
  }
  //Create labels with TTFConfig
  auto backLabel = Label::createWithTTF(labelConfig, "Back");
  
  auto backItem = MenuItemLabel::create(backLabel, CC_CALLBACK_0(LeaderBoard::lbBackCallback, this));
  
  //Create menu and add all the items
  auto menu = Menu::create(backItem,NULL);
  
  menu->setPosition(winSize.width/2,100);
  
  menu->setColor(Color3B(255,25,25));
  menu->alignItemsVerticallyWithPadding(20.0);
  
  this->addChild(menu,1);
  return true;
}

void LeaderBoard::lbBackCallback(){
  auto scene = MainMenu::createScene();
  Director::getInstance()->replaceScene(scene);
}
