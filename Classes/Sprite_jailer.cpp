//
//  Sprite_jailer.cpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 10/22/15.
//
//

#include "JailerListener.h"
#include   "Sprite_jailer.h"
#include "cocos2d.h"
USING_NS_CC;

void Sprite_jailer::setJailer(int number,cocos2d::Sprite* getSprite){
    auto ManBody=PhysicsBody::createBox(getSprite->getContentSize());
    ManBody->setGravityEnable(false);
    ManBody->setContactTestBitmask(0xFFFF);
    getSprite->setPhysicsBody(ManBody);
    getSprite->setTag(JAILER_TAG+number);
    //sprite = getSprite;
    Tag = JAILER_TAG+number;
    isStop = false;
}


void Sprite_jailer::setIsStop(bool stop){
    isStop = stop;
}


bool Sprite_jailer::getIsStop(){
    return isStop;
}


int Sprite_jailer::getTag(){
    return Tag;
}