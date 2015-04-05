#include "Camera.h"
#include <iostream>

USING_NS_CC;

void CameraControl::create(Size size){
  camera = Camera::createPerspective(60, (float)size.width/size.height, 1.0, 1000);
  camera->setCameraFlag(CameraFlag::USER2);
  winSize = size;
}

void CameraControl::update(Vec3 playerPos){
  camera->setPosition3D(playerPos + Vec3(0,winSize.height/2,800));
  camera->lookAt(playerPos + Vec3(0,winSize.height/2,0) , Vec3(0.0,1.0,0.0));
}

Camera* CameraControl::getCamera(){
  return camera;
}
