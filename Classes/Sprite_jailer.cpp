//
//  Sprite_jailer.cpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 10/22/15.
//
//

#include "JailerListener.h"
#include   "Sprite_jailer.h"
#include "cocos2d.h"
USING_NS_CC;

void Sprite_jailer::setJailer(int number,cocos2d::Sprite* getSprite){
    auto ManBody=PhysicsBody::createBox(getSprite->getContentSize());
    ManBody->setGravityEnable(false);
    ManBody->setContactTestBitmask(0xFFFF);
    getSprite->setPhysicsBody(ManBody);
    getSprite->setTag(JAILER_TAG+number);
    sprite = getSprite;
    CCLOG("精灵设置");
}

void Sprite_jailer::setTimeline(TIMELINE timeLine){
    for(int i = 0;i<20;i++){
        if(timeLine.TimeLine[i]->getTag()!=157)
            break;
        if((signed)timeLine.TimeLine[i]->getFlags()==sprite->getTag()){
            
            timeline = timeLine.TimeLine[i];
            
            break;
        }
    }

}

cocostudio::timeline::ActionTimeline* Sprite_jailer::getTimeLine(){
    return timeline;
}


void Sprite_jailer::setListener(JailerListener* listener){
    Listener = listener;
}