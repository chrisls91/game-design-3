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
    static int level;
    static void setLevel(int lvl);
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
    Sprite* background;
    Size winSize;
    Label* label;
    CocosDenshion::SimpleAudioEngine* audio;
    float endX;
    //Flag for touch-control sliding
    bool slideTouchHeld = false;
    float slideTimer = 0;
    const char* bgLut[7] = {"citytrace.png","citytrace2.png","citytrace3.png","citytrace4.png","citytrace5.png","citytrace6.png","citytrace7.png"};
    const char* muLut[3] = {"bg1.mp3","bg2.mp3","bg3.mp3"};
};
