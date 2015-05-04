#pragma once
#include "cocos2d.h"
#include "Player.h"
#include "Obstacles.h"
#include "Camera.h"
#include "Pickups.h"
#include "KeyboardReceiver.h"
#include "SimpleAudioEngine.h"
#include "Menu.h"

USING_NS_CC;

class Game : public cocos2d::Layer
{
 public:
    static cocos2d::Scene* createScene();
    virtual bool init() override;
    CREATE_FUNC(Game);
    void update(float dt) override;
    bool onContactBegin(PhysicsContact& contact);
    void reloadPickups();
    int level = 1;
    
    //Touchscreen callbacks
#if ((CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID))
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
#endif
    
 private:
    bool paused = false;
    CameraControl camera;
    Receiver receiver;
    float time = 0.0;
    Player player;
    Node* wall;
    Size winSize;
    Label* label;
    CocosDenshion::SimpleAudioEngine* audio;
    //Flag for touch-control sliding
    bool slideTouchHeld = false;
    float slideTimer = 0;
};
