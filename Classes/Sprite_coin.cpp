//
//  Sprite_coin.cpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 10/22/15.
//
//

#include "Sprite_coin.h"
#include "cocos2d.h"
#include "Constant_Use.h"
USING_NS_CC;

Sprite* Sprite_coin::create(int number,Sprite* getSprite){
    auto coin= getSprite;
    
    auto ManBody=PhysicsBody::createBox(coin->getContentSize());
    
    CCLOG("%f,%f",coin->getContentSize().width,coin->getContentSize().height);
    
    ManBody->setGravityEnable(false);
    ManBody->setContactTestBitmask(0xFFFF);
    coin->setPhysicsBody(ManBody);
    coin->setTag(COIN_TAG+number);
    
    return coin;
    
}