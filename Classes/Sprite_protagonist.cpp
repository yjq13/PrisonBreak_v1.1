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


Sprite* Sprite_protagonist::create(int number){
    auto protagonist=Sprite::create("05.jpg");
    
    auto ManBody=PhysicsBody::createBox(protagonist->getContentSize());
    
    CCLOG("%f,%f",protagonist->getContentSize().width,protagonist->getContentSize().height);
    
    ManBody->setGravityEnable(false);
    ManBody->setContactTestBitmask(0xFFFF);
    protagonist->setPhysicsBody(ManBody);
    protagonist->setTag(PROTAGONIST_TAG+number);

    return protagonist;
    
}