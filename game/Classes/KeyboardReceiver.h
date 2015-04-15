#include "cocos2d.h"

#define JUMP_KEY 0
#define SLIDE_KEY 1

class Receiver{
 public:
  cocos2d::EventListenerKeyboard* create();
  bool IsKeyPressed(int key);
  void releaseKey(int key);
 private:
  cocos2d::EventListenerKeyboard* receiver;
  // keys[JumpKey|SlideKey]
  bool keys[2];
};
