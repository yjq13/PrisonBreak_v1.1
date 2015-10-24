//
//  Sprite_Component.cpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 10/22/15.
//
//

#include "Sprite_protagonist.h"
#include "cocos2d.h"

USING_NS_CC;
Sprite_protagonist::Sprite_protagonist(){
    Sprite_protagonist::create("05.jpg");
    
    auto ManBody=PhysicsBody::createBox(this->getContentSize());
    
    CCLOG("%f,%f",this->getContentSize().width,this->getContentSize().height);
    
    ManBody->setGravityEnable(false);
    ManBody->setContactTestBitmask(0xFFFF);
    this->setPhysicsBody(ManBody);
}


//  Sprite* Sprite_protagonist::create(const std::string& filename){
//    auto protagonist=Sprite::create("05.jpg");
//    
//    auto ManBody=PhysicsBody::createBox(protagonist->getContentSize());
//    
//    CCLOG("%f,%f",protagonist->getContentSize().width,protagonist->getContentSize().height);
//    
//    ManBody->setGravityEnable(false);
//    ManBody->setContactTestBitmask(0xFFFF);
//    protagonist->setPhysicsBody(ManBody);
//    //protagonist->setTag(1);
//
//    return protagonist;
//    
//}