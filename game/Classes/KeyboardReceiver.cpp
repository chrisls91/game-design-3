#include "KeyboardReceiver.h"

USING_NS_CC;

EventListenerKeyboard* Receiver::create(){
  auto eventListener = EventListenerKeyboard::create();

  eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event){
    
    // Just add more keys here for keybinds
    switch(keyCode){
    case EventKeyboard::KeyCode::KEY_SPACE:
    keys[JUMP_KEY] = true;
    break;
    case EventKeyboard::KeyCode::KEY_S:
    keys[SLIDE_KEY] = true;
    break;
    }
  };

  eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event){
    // Just add more keys here for keybinds
    switch(keyCode){
    case EventKeyboard::KeyCode::KEY_SPACE:
    keys[JUMP_KEY] = false;
    break;
    case EventKeyboard::KeyCode::KEY_S:
    keys[SLIDE_KEY] = false;
    break;
    }
  };
  
  return eventListener;
}

bool Receiver::IsKeyPressed(int key){
  return keys[key];
}
