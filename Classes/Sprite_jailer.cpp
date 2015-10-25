//
//  Sprite_jailer.cpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 10/22/15.
//
//

#include "Sprite_jailer.h"
#include "cocos2d.h"
#include "Constant_Use.h"
USING_NS_CC;

Sprite* Sprite_jailer::create(int number){
    auto jailer=Sprite::create("05.jpg");
    
    auto ManBody=PhysicsBody::createBox(jailer->getContentSize());
    
    CCLOG("%f,%f",jailer->getContentSize().width,jailer->getContentSize().height);
    
    ManBody->setGravityEnable(false);
    ManBody->setContactTestBitmask(0xFFFF);
    jailer->setPhysicsBody(ManBody);
    jailer->setTag(JAILER_TAG+number);
    
    return jailer;
    
}