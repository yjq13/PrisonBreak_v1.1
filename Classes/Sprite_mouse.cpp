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

Sprite* Sprite_mouse::create(int number){
    auto mouse=Sprite::create("05.jpg");
    
    auto ManBody=PhysicsBody::createBox(mouse->getContentSize());
    
    CCLOG("%f,%f",mouse->getContentSize().width,mouse->getContentSize().height);
    
    ManBody->setGravityEnable(false);
    ManBody->setContactTestBitmask(0xFFFF);
    mouse->setPhysicsBody(ManBody);
    mouse->setTag(MOUSE_TAG+number);
    
    return mouse;
    
}