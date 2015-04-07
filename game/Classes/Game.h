#include "cocos2d.h"
#include "Player.h"
#include "Obstacles.h"
#include "Camera.h"
#include "KeyboardReceiver.h"

// Velocity per seconds
#define BASE_VEL 100

USING_NS_CC;

class Game : public cocos2d::Layer
{
 public:
    static cocos2d::Scene* createScene();
    virtual bool init() override;
    CREATE_FUNC(Game);
    void update(float dt) override;
    bool onContactBegin(PhysicsContact& contact);
 private:
    CameraControl camera;
    Receiver receiver;
    float time = 0.0;
    Player player;
    Node* wall;
    bool status = false;
};
