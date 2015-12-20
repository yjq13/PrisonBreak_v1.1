//
//  Sprite_wall.cpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 10/22/15.
//
//

#include "Sprite_wall.h"
#include "cocos2d.h"
#include "Constant_Use.h"

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

void Sprite_wall::setWall(int number,cocos2d::Sprite* getSprite){
    auto ManBody=PhysicsBody::createBox(getSprite->getContentSize());
    
    //CCLOG("%f,%f",getSprite->getContentSize().width,getSprite->getContentSize().height);
    ManBody->setGravityEnable(false);
    ManBody->setContactTestBitmask(0xFFFF);
    getSprite->setPhysicsBody(ManBody);
    getSprite->setTag(WALL_TAG+number);
    
}