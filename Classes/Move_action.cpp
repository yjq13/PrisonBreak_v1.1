//
//  Move_action.cpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 10/23/15.
//
//

#include "Move_action.h"
#include "cocos2d.h"
USING_NS_CC;

EventListenerPhysicsContact* moveAction::create(){
    EventListenerPhysicsContact* contactListener=EventListenerPhysicsContact::create();
    contactListener->onContactBegin=CC_CALLBACK_1(moveAction::onContactBegin, this);
    return contactListener;
}


bool moveAction::onContactBegin(const cocos2d::PhysicsContact &contact){
    CCLOG("OKKKK!!!!!!!");
//    removeChild(protagonist);
    return true;
}