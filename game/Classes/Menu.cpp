//
//  Menu.cpp
//  MyGame
//
//  Created by Chris Stewart on 4/15/15.
//
//

#include "Menu.h"

USING_NS_CC;
using namespace std;

//Main/Start menu implementation
Scene* MainMenu::createScene(){
    auto scene = Scene::create();
    auto layer = MainMenu::create();
    scene->addChild(layer);
    
    return scene;
}

bool MainMenu::init(){
    if ( !Layer::init() )
    {
        return false;
    }
    
    //Start background music
    audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->stopBackgroundMusic();
    audio->playBackgroundMusic("DeliveryManTitleMusic.mp3", true);
    audio->setBackgroundMusicVolume(1.0f);

    //Get size and origin for layout and placement
    winSize = Director::getInstance()->getWinSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    //Create background effects
    for(int i=0;i<winSize.width;i+=50){
        auto emitter = ParticleFire::createWithTotalParticles(200);
        emitter->setPosition(i,winSize.height/2-360);
        emitter->setStartSize(80.0);
        emitter->setEndSize(80.0);
        emitter->setDuration(-1);
        emitter->setLife(14);
        emitter->setEmissionRate(5);
        this->addChild(emitter);
    }
    
    //Create a TTFConfig and set settings appropriately
    TTFConfig labelConfig;
    labelConfig.fontFilePath = "fonts/chowfun.ttf";
    labelConfig.fontSize = 40;
    labelConfig.glyphs = GlyphCollection::DYNAMIC;
    labelConfig.outlineSize = 0;
    labelConfig.customGlyphs = nullptr;
    labelConfig.distanceFieldEnabled = false;
    
    //Create labels with TTFConfig
    auto playGameLabel = Label::createWithTTF(labelConfig, "Play Game");
    auto leaderboardLabel = Label::createWithTTF(labelConfig, "Leaderboards");
    auto settingsLabel = Label::createWithTTF(labelConfig, "Settings");
    auto quitLabel = Label::createWithTTF(labelConfig, "Quit");
    
    //Create MenuItems from labels
    auto playMenuItem = MenuItemLabel::create(playGameLabel, CC_CALLBACK_0(MainMenu::menuPlayCallback, this));
    auto boardMenuItem = MenuItemLabel::create(leaderboardLabel, CC_CALLBACK_0(MainMenu::menuLeaderboardCallback, this));
    auto settingsItem = MenuItemLabel::create(settingsLabel, CC_CALLBACK_0(MainMenu::menuSettingsCallback, this));
    auto quitItem = MenuItemLabel::create(quitLabel, CC_CALLBACK_0(MainMenu::menuQuitCallback, this));
    
    //Create Title Logo
    auto titleSprite = Sprite::create("DeliveryBoyTitleLogo.png");
    titleSprite->setPosition(winSize.width/2,winSize.height/2+160);
    this->addChild(titleSprite,1);
    
    //Create menu and add all the items
    auto menu = Menu::create(playMenuItem,boardMenuItem,settingsItem,quitItem,NULL);
    menu->setPosition(winSize.width/2,winSize.height/2-140);
    
    menu->setColor(Color3B(255,25,25));
    menu->alignItemsVerticallyWithPadding(10.0);
    
    this->addChild(menu,1);
    
    return true;
}

void MainMenu::menuPlayCallback(){
    audio->stopBackgroundMusic();
    auto scene = LevelSelect::createScene();
    Director::getInstance()->replaceScene(scene);
}

void MainMenu::menuLeaderboardCallback(){
  auto scene = LeaderBoard::createScene();
  Director::getInstance()->replaceScene(scene);
}

void MainMenu::menuSettingsCallback(){
    printf("Settings pressed\n");
}

void MainMenu::menuQuitCallback(){
    //This kills the application but I think it might be
    //missing a cleanup step.
    Director::getInstance()->end();
    exit(EXIT_SUCCESS);
}


//Level complete menu implementation
Scene* CompleteMenu::createScene(float score){
    auto scene = Scene::create();
    auto layer = CompleteMenu::create();
    layer->setScore(score);
    scene->addChild(layer);
    
    return scene;
}

void CompleteMenu::setScore(float value){
    score = value;
    
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
    scoreLabel->setPosition(winSize.width/2,winSize.height/2+100);
    this->addChild(scoreLabel,1);
}

bool CompleteMenu::init(){
    if ( !Layer::init() )
    {
        return false;
    }
    
    //Set music
    audio=CocosDenshion::SimpleAudioEngine::getInstance();
    audio->stopBackgroundMusic();
    
    //Get size and origin for layout and placement
    winSize = Director::getInstance()->getWinSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    //Create TTFConfig for main label
    TTFConfig mainLabelConfig;
    mainLabelConfig.fontFilePath = "fonts/chowfun.ttf";
    mainLabelConfig.fontSize = 62;
    mainLabelConfig.glyphs = GlyphCollection::DYNAMIC;
    mainLabelConfig.outlineSize = 0;
    mainLabelConfig.customGlyphs = nullptr;
    mainLabelConfig.distanceFieldEnabled = false;
    
    //Create a TTFConfig for buttons
    TTFConfig labelConfig;
    labelConfig.fontFilePath = "fonts/chowfun.ttf";
    labelConfig.fontSize = 42;
    labelConfig.glyphs = GlyphCollection::DYNAMIC;
    labelConfig.outlineSize = 0;
    labelConfig.customGlyphs = nullptr;
    labelConfig.distanceFieldEnabled = false;
    
    //Create labels with TTFConfig
    auto levelCompleteLabel = Label::createWithTTF(mainLabelConfig, "Level Complete!");
    levelCompleteLabel->setPosition(winSize.width/2,winSize.height/2+200);
    this->addChild(levelCompleteLabel,1);
    
    auto nextLabel = Label::createWithTTF(labelConfig, "Next");
    auto replayLabel = Label::createWithTTF(labelConfig, "Replay");
    auto postLabel = Label::createWithTTF(labelConfig, "Post to Leaderboard");
    auto menuLabel = Label::createWithTTF(labelConfig, "Main Menu");
    
    //Create MenuItems from labels
    auto nextMenuItem = MenuItemLabel::create(nextLabel, CC_CALLBACK_0(CompleteMenu::menuNextCallback, this));
    auto replayMenuItem = MenuItemLabel::create(replayLabel, CC_CALLBACK_0(CompleteMenu::menuReplayCallback, this));
    auto postItem = MenuItemLabel::create(postLabel, CC_CALLBACK_0(CompleteMenu::menuPostToBoardCallback, this));
    auto menuItem = MenuItemLabel::create(menuLabel, CC_CALLBACK_0(CompleteMenu::menuMainMenuCallback, this));
    
    //Create menu and add all the items
    auto menu = Menu::create(nextMenuItem,replayMenuItem,postItem,menuItem,NULL);
    menu->setPosition(winSize.width/2,winSize.height/2-100);
    
    menu->setColor(Color3B(255,25,25));
    menu->alignItemsVerticallyWithPadding(1.0);
    
    this->addChild(menu,1);
    
    //Create fireworks effect
    emitter = ParticleExplosion::create();
    emitter->retain();
    emitter->setPosition(winSize.width/2,winSize.height/2);
    this->addChild(emitter,-1);
    
    return true;
}

void CompleteMenu::menuNextCallback(){
    auto scene = LevelSelect::createScene();
    Director::getInstance()->replaceScene(scene);
}

void CompleteMenu::menuReplayCallback(){
    audio->stopBackgroundMusic();
    auto scene = Game::createScene();
    Director::getInstance()->replaceScene(scene);
}

void CompleteMenu::menuPostToBoardCallback(){
  auto scene = PostToLeaderBoard::createScene();
  PostToLeaderBoard::setScore(score);
  Director::getInstance()->replaceScene(scene);
}

void CompleteMenu::menuMainMenuCallback(){
    audio->stopBackgroundMusic();
    auto scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(scene);
}

Scene* LevelSelect::createScene(){
    auto scene = Scene::create();
    auto layer = LevelSelect::create();
    scene->addChild(layer);
    
    return scene;
}

bool LevelSelect::init(){
    if ( !Layer::init() )
    {
        return false;
    }
    
    //Get size and origin for layout and placement
    winSize = Director::getInstance()->getWinSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    //Create TTFConfig for main label
    TTFConfig labelConfig;
    labelConfig.fontFilePath = "fonts/Metropolian-Display.ttf";
    labelConfig.fontSize = 22;
    labelConfig.glyphs = GlyphCollection::DYNAMIC;
    labelConfig.outlineSize = 0;
    labelConfig.customGlyphs = nullptr;
    labelConfig.distanceFieldEnabled = false;
    
    auto lvl1Label = Label::createWithTTF(labelConfig, "First delivery");
    auto lvl2Label = Label::createWithTTF(labelConfig, "Bad part of town");
    
    auto lvl1Btn = MenuItemLabel::create(lvl1Label, CC_CALLBACK_0(LevelSelect::level1Callback, this));
    auto lvl2Btn = MenuItemLabel::create(lvl2Label, CC_CALLBACK_0(LevelSelect::level2Callback, this));
    
    auto menu = Menu::create(lvl1Btn,lvl2Btn,NULL);
    
    menu->setPosition(winSize.width/2-120,winSize.height/2);
    menu->setColor(Color3B(255,255,255));
    menu->alignItemsVerticallyWithPadding(1.0);

    
    this->addChild(menu);

    return true;
}

void LevelSelect::level1Callback(){
    Game::setLevel(1);
    auto scene = Game::createScene();
    Director::getInstance()->replaceScene(scene);
}

void LevelSelect::level2Callback(){
    Game::setLevel(2);
    auto scene = Game::createScene();
    Director::getInstance()->replaceScene(scene);
}