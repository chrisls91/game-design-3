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
#include "network/HttpClient.h"
#include <string>
#include "Game.h"
#include "Menu.h"
#include "external/json/document.h"
#include "external/json/writer.h"
#include "external/json/stringbuffer.h"

USING_NS_CC;

class LeaderBoard : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init() override;
    CREATE_FUNC(LeaderBoard);
    void lbBackCallback();
    void onHttpRequestCompleted();
private:
    Size winSize;
    cocos2d::network::HttpResponse *response;
};


class PostToLeaderBoard : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene(float value, int level);
    virtual bool init() override;
    CREATE_FUNC(PostToLeaderBoard);
    void lbSubmitCallback();
    void setScore();
private:
    Size winSize;
    float score;
    int level;
    std::string name;
    cocos2d::ui::EditBox* editbox;
};

#endif /* defined(__gamename2__LeaderBoard__) */
