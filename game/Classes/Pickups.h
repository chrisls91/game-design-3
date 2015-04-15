//
//  Pickups.h
//  MyGame
//
//  Created by Chris Stewart on 4/13/15.
//
//

#ifndef __MyGame__Pickups__
#define __MyGame__Pickups__

#include "cocos2d.h"

class SpeedPickup
{
public:
    cocos2d::SpriteBatchNode* createSpeedPickup(float x_pos, float y_pos);
    cocos2d::Sprite* getSprite();
    cocos2d::Point getPosition();
    void setPosition(float x, float y);
private:
    cocos2d::Sprite* Sprite;
};

#endif /* defined(__MyGame__Pickups__) */
