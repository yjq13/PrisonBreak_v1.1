//
//  Sprite_mouse.cpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 10/22/15.
//
//

#include "Sprite_mouse.h"
#include "cocos2d.h"
#include "Constant_Use.h"
USING_NS_CC;

Sprite* Sprite_mouse::create(int number,Sprite* getSprite){
    auto mouse = getSprite;
    
    auto ManBody=PhysicsBody::createBox(mouse->getContentSize());
    
    CCLOG("%f,%f",mouse->getContentSize().width,mouse->getContentSize().height);
    
    ManBody->setGravityEnable(false);
    ManBody->setContactTestBitmask(0xFFFF);
    mouse->setPhysicsBody(ManBody);
    mouse->setTag(MOUSE_TAG+number);
    
    return mouse;
    
}

void Sprite_mouse::setMouse(int number,cocos2d::Sprite* getSprite){
    auto ManBody=PhysicsBody::createBox(getSprite->getContentSize()*0.1);
    CCLOG("%f,%f",getSprite->getContentSize().width,getSprite->getContentSize().height);
    
    ManBody->setGravityEnable(false);
    ManBody->setContactTestBitmask(0xFFFF);
    getSprite->setPhysicsBody(ManBody);
    getSprite->setTag(MOUSE_TAG+number);
    
}