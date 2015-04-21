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
    
    //Create labels with TTFConfig
    auto playGameLabel = Label::createWithTTF(labelConfig, "Play Game");
    auto leaderboardLabel = Label::createWithTTF(labelConfig, "Leaderboards");
    auto settingsLabel = Label::createWithTTF(labelConfig, "Settings");
    auto quitLabel = Label::createWithTTF(labelConfig, "Quit");
    
    //Create MnuItems from labels
    auto playMenuItem = MenuItemLabel::create(playGameLabel, CC_CALLBACK_0(MainMenu::menuPlayCallback, this));
    auto boardMenuItem = MenuItemLabel::create(leaderboardLabel, CC_CALLBACK_0(MainMenu::menuLeaderboardCallback, this));
    auto settingsItem = MenuItemLabel::create(settingsLabel, CC_CALLBACK_0(MainMenu::menuSettingsCallback, this));
    auto quitItem = MenuItemLabel::create(quitLabel, CC_CALLBACK_0(MainMenu::menuQuitCallback, this));
    
    //Create menu and add all the items
    auto menu = Menu::create(playMenuItem,boardMenuItem,settingsItem,quitItem,NULL);
    menu->setPosition(winSize.width/2,winSize.height/2);
    
    menu->setColor(Color3B(255,25,25));
    menu->alignItemsVerticallyWithPadding(20.0);
    
    this->addChild(menu,1);
    
    return true;
}

void MainMenu::menuPlayCallback(){
    auto scene = Game::createScene();
    Director::getInstance()->replaceScene(scene);
}

void MainMenu::menuLeaderboardCallback(){
    printf("leaderboard presed\n");
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