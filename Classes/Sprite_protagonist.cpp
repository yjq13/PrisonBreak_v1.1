//
//  Sprite_Component.cpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 10/22/15.
//
//
#include "protagonistListener.h"
#include "Sprite_protagonist.h"
#include "cocos2d.h"
#include "Constant_Use.h"
USING_NS_CC;


void Sprite_protagonist::setPro(int number,cocos2d::Sprite* getSprite){
    auto ManBody=PhysicsBody::createBox(getSprite->getContentSize());
    
    ManBody->setGravityEnable(false);
    ManBody->setContactTestBitmask(0xFFFF);
    getSprite->setPhysicsBody(ManBody);
    getSprite->setTag(PROTAGONIST_TAG+number);
    
}


