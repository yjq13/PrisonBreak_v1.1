//
//  Special_Section.cpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 12/21/15.
//
//

#include "Special_Section.h"
#include "cocos2d.h"
#include "Constant_Use.h"

void Sprite_SpecialSection::setSpecialSection(int number,cocos2d::Sprite* getSprite){
    auto ManBody=PhysicsBody::createBox(getSprite->getContentSize());
    //CCLOG("%f,%f",getSprite->getContentSize().width,getSprite->getContentSize().height);
    
    ManBody->setGravityEnable(false);
    ManBody->setContactTestBitmask(0xFFFF);
    getSprite->setPhysicsBody(ManBody);
    getSprite->setTag(SECTION_TAG+number);
    
}