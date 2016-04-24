
//
//  Section.cpp
//  PrisonBreak_v1.1
//
//  Created by 马长松 on 15/10/24.
//
//

#include "Section.h"
#include "Constant_Use.h"
void End_Section::setEnd_Section(int number,cocos2d::Sprite* getSprite){
    auto ManBody=cocos2d::PhysicsBody::createBox(getSprite->getContentSize());
    //CCLOG("%f,%f",getSprite->getContentSize().width,getSprite->getContentSize().height);
    
    ManBody->setGravityEnable(false);
    ManBody->setContactTestBitmask(0xFFFF);
    getSprite->setPhysicsBody(ManBody);
    getSprite->setTag(SECTION_END_TAG+number);
    
}