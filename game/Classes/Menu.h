//
//  Menu.h
//  MyGame
//
//  Created by Chris Stewart on 4/15/15.
//
//

#ifndef __MyGame__Menu__
#define __MyGame__Menu__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Game.h"
#include "LeaderBoard.h"

USING_NS_CC;

class MainMenu : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init() override;
    CREATE_FUNC(MainMenu);
    void menuPlayCallback();
    void menuLeaderboardCallback();
    void menuSettingsCallback();
    void menuQuitCallback();
    void reloadPickups();
private:
    Size winSize;
};

#endif /* defined(__MyGame__Menu__) */
