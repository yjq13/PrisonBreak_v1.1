//
//  Sprite_wall.cpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 10/22/15.
//
//

#include "Sprite_wall.h"
#include "cocos2d.h"

USING_NS_CC;

Sprite* Sprite_wall::create(){
    auto wall=Sprite::create("05.jpg");
    
    auto ManBody=PhysicsBody::createBox(wall->getContentSize());
    
    CCLOG("%f,%f",wall->getContentSize().width,wall->getContentSize().height);
    
    ManBody->setGravityEnable(false);
    ManBody->setContactTestBitmask(0xFFFF);
    wall->setPhysicsBody(ManBody);
    //protagonist->setTag(1);
    
    return wall;
    
}