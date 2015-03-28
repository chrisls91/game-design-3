#include "cocos2d.h"
#include "Player.h"
#include "Collision.h"

class Game : public cocos2d::Layer
{
 public:
    static cocos2d::Scene* createScene();
    virtual bool init() override;
    CREATE_FUNC(Game);
    void update(float dt) override;
    bool onContactBegin(PhysicsContact& contact);
 private:
    Player player;
    Node* wall;
};
