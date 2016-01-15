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
#include "SpriteListener.h"
USING_NS_CC;


Sprite* Sprite_protagonist::create(int number,cocos2d::Sprite* getSprite){
    auto protagonist=getSprite;
    
    auto ManBody=PhysicsBody::createBox(protagonist->getContentSize());
    
    
    
    //CCLOG("%f,%f",protagonist->getContentSize().width,protagonist->getContentSize().height);
    
    ManBody->setGravityEnable(false);
    ManBody->setContactTestBitmask(0xFFFF);
    protagonist->setPhysicsBody(ManBody);
    protagonist->setTag(PROTAGONIST_TAG+number);

    
    return protagonist;
    
}

void Sprite_protagonist::setPro(int number,cocos2d::Sprite* getSprite){
    auto ManBody=PhysicsBody::createBox(getSprite->getContentSize());
     //CCLOG("%f,%f",getSprite->getContentSize().width,getSprite->getContentSize().height);
    
    Director* pDirector = Director::getInstance();
    
    SpriteListener spritelistener;
    EventListenerTouchOneByOne* listener = spritelistener.create(getSprite);
    
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, getSprite);
    //添加一个触摸委托给dispatcher的列表,委托对象this,
    pDirector->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, getSprite);
    
    ManBody->setGravityEnable(false);
    ManBody->setContactTestBitmask(0xFFFF);
    getSprite->setPhysicsBody(ManBody);
    getSprite->setTag(PROTAGONIST_TAG+number);
    
}


