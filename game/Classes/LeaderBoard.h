//
//  LeaderBoard.h
//  gamename2
//
//  Created by will harrison on 4/23/15.
//
//

#ifndef __gamename2__LeaderBoard__
#define __gamename2__LeaderBoard__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string>
#include "Game.h"
#include "Menu.h"

USING_NS_CC;

class LeaderBoard : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init() override;
    CREATE_FUNC(LeaderBoard);
    void lbBackCallback();
private:
    Size winSize;
};


class PostToLeaderBoard : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init() override;
    CREATE_FUNC(PostToLeaderBoard);
    void lbSubmitCallback();
    static void setScore(float score);
private:
    Size winSize;
  static float score;
};

#endif /* defined(__gamename2__LeaderBoard__) */
