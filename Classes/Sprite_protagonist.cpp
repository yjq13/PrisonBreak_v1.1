//
//  Sprite_Component.cpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 10/22/15.
//
//

#include "Sprite_protagonist.h"
#include "cocos2d.h"
#include "Constant_Use.h"
USING_NS_CC;


Sprite* Sprite_protagonist::create(int number,cocos2d::Sprite* getSprite){
    auto protagonist=getSprite;
    
    auto ManBody=PhysicsBody::createBox(protagonist->getContentSize()*0.1);
    
    CCLOG("%f,%f",protagonist->getContentSize().width,protagonist->getContentSize().height);
    
    ManBody->setGravityEnable(false);
    ManBody->setContactTestBitmask(0xFFFF);
    protagonist->setPhysicsBody(ManBody);
    protagonist->setTag(PROTAGONIST_TAG+number);

    
    return protagonist;
    
}

void Sprite_protagonist::setPro(int number,cocos2d::Sprite* getSprite){
    auto ManBody=PhysicsBody::createBox(getSprite->getContentSize()*0.1);
     CCLOG("%f,%f",getSprite->getContentSize().width,getSprite->getContentSize().height);
    
    ManBody->setGravityEnable(false);
    ManBody->setContactTestBitmask(0xFFFF);
    getSprite->setPhysicsBody(ManBody);
    getSprite->setTag(PROTAGONIST_TAG+number);
    
}