//
//  LeaderBoard.cpp
//  gamename2
//
//  Created by will harrison on 4/23/15.
//
//

#include "LeaderBoard.h"
#include <iostream>
#include <stdio.h>
USING_NS_CC;
using namespace std;

std::string exec(char* cmd) {
  FILE* pipe = popen(cmd, "r");
  if (!pipe) return "ERROR";
  char buffer[128];
  std::string result = "";
  while(!feof(pipe)) {
    if(fgets(buffer, 128, pipe) != NULL)
    		result += buffer;
  }
  pclose(pipe);
  return result;
}


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
  
  /*
  auto request = new cocos2d::network::HttpRequest();
  request->setUrl("http://localhost:8000/index.php/leaders");
  request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
  response = new cocos2d::network::HttpResponse(request);
  request->setResponseCallback(CC_CALLBACK_0(LeaderBoard::onHttpRequestCompleted, this));
  request->setTag("GET leaders");
  cocos2d::network::HttpClient::getInstance()->send(request);
  request->release();
  */
  
  string results = exec("curl -i -H \"Accept: application/json\" \"localhost:8000/index.php/leaders\" ");
  std::size_t found = results.find("[");
  
  results = results.substr(found, results.size() - 2);
  
  //cout << results << endl;
  rapidjson::Document jsonDoc; // create the object
  jsonDoc.Parse<0>(results.c_str());
  
  cout << jsonDoc.Size() << endl;
  
  int loopsize = 10;
  if (jsonDoc.Size() < 10) {
    loopsize = jsonDoc.Size();
  }
  
  for (int i = 0; i < loopsize; i++)
  {
    auto temp = Label::createWithTTF(std::to_string(i + 1) + ". " + jsonDoc[i]["name"].GetString() + " -- " + jsonDoc[i]["time"].GetString() + " -- Level: " + jsonDoc[i]["level"].GetString(), "fonts/chowfun.ttf", 24);
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

void LeaderBoard::onHttpRequestCompleted()
{
  
  std::vector<char>* buffer = response->getResponseData();
  printf("Http Test, dump data: ");
  cout << response->getResponseHeader() << endl;
  cout << response->getResponseCode() << endl;
  for (unsigned int i = 0; i < buffer->size(); i++)
  {
    printf("%c", (*buffer)[i]);
  }
  printf("\n");

}

void LeaderBoard::lbBackCallback(){
  auto scene = MainMenu::createScene();
  Director::getInstance()->replaceScene(scene);
}


/*
 *
 *
 *
 * Post to LeaderBoard
 *
 *
 *
 */

Scene* PostToLeaderBoard::createScene(float value, int level){
  auto scene = Scene::create();
  auto layer = PostToLeaderBoard::create();
  layer->score = value / 1000;
  layer->level = level;
  layer->setScore();
  scene->addChild(layer);
  
  return scene;
}

void PostToLeaderBoard::setScore()
{
  //Create TTFConfig for main label
  TTFConfig mainLabelConfig;
  mainLabelConfig.fontFilePath = "fonts/chowfun.ttf";
  mainLabelConfig.fontSize = 62;
  mainLabelConfig.glyphs = GlyphCollection::DYNAMIC;
  mainLabelConfig.outlineSize = 0;
  mainLabelConfig.customGlyphs = nullptr;
  mainLabelConfig.distanceFieldEnabled = false;
  
  auto scoreLabel = Label::createWithTTF(mainLabelConfig, "");;
  int ms = (int) score%1000;
  int sec = (int) (score/1000)%60;
  int min = (score/1000)/60;
  scoreLabel->setString(((min>0)?to_string(min) + ":":"") + to_string(sec) + ":" + to_string(ms));
  scoreLabel->setPosition(winSize.width/2,winSize.height - 200);
  this->addChild(scoreLabel,1);
}

bool PostToLeaderBoard::init(){
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
  
  auto label1 = Label::createWithTTF("Post To Leaderboard", "fonts/chowfun.ttf", 44);
  label1->setPosition(Point(winSize.width/2 - 230, winSize.height - 100 ));
  label1->setAnchorPoint(Point(0.0f, 0.0f));
  this->addChild(label1);
  
  cocos2d::ui::EditBox* nameBox  = cocos2d::ui::EditBox::create(Size(400, 20), "WhiteBox.jpg");
  nameBox->setPosition(Vec2(winSize.width/2, winSize.height - 300));
  nameBox->setFontColor(Color3B::BLACK);
  nameBox->setPlaceHolder("Name:");
  nameBox->setPlaceholderFontColor(Color3B::GRAY);
  nameBox->setMaxLength(100);
  nameBox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
  addChild(nameBox);
  
  editbox = nameBox;
  
  //Create labels with TTFConfig
  auto submitLabel = Label::createWithTTF(labelConfig, "Submit");
  
  auto submitItem = MenuItemLabel::create(submitLabel, CC_CALLBACK_0(PostToLeaderBoard::lbSubmitCallback, this));
  
  //Create menu and add all the items
  auto menu = Menu::create(submitItem,NULL);
  
  menu->setPosition(winSize.width/2,100);
  
  menu->setColor(Color3B(255,25,25));
  menu->alignItemsVerticallyWithPadding(20.0);
  
  this->addChild(menu,1);
  return true;
}

void PostToLeaderBoard::lbSubmitCallback(){
  auto scene = MainMenu::createScene();
  
  auto request = new cocos2d::network::HttpRequest();
  request->setUrl("http://localhost:8000/index.php/leaders");
  request->setRequestType(cocos2d::network::HttpRequest::Type::POST);
  std::vector<std::string> headers;
  headers.push_back("Content-Type: application/json; charset=utf-8");
  request->setHeaders(headers);  // write the post data
  char data[4096];
  sprintf(data, "%s%s%s%f%s%d%s", "{\"name\": \"", editbox->getText(), "\",\"time\": \"", score, "\",\"level\": \"", level, "\"}");
  request->setRequestData(data, strlen(data));
  
  request->setTag("POST leaders");
  cocos2d::network::HttpClient::getInstance()->send(request);
  request->release();
  Director::getInstance()->replaceScene(scene);
}

