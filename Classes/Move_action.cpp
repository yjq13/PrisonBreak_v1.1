//
//  Move_action.cpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 10/23/15.
//
//

#include "Move_action.h"
#include "cocos2d.h"
#include "Constant_Use.h"
USING_NS_CC;

EventListenerPhysicsContact* moveAction::createProAction(){
    EventListenerPhysicsContact* contactListener=EventListenerPhysicsContact::create();
    
    contactListener->onContactBegin=CC_CALLBACK_1(moveAction::switchMoveAction, this);
    return contactListener;
}

bool moveAction::switchMoveAction(const cocos2d::PhysicsContact &contact){
    int body_tag = 0;
    //找到碰撞物体
    if(contact.getShapeA()->getBody()->getNode()->getTag()==PROTAGONIST_TAG){
        body_tag = contact.getShapeB()->getBody()->getNode()->getTag();
    }else{
        body_tag = contact.getShapeA()->getBody()->getNode()->getTag();
    }
    
    switch((body_tag/1000)*1000){
            
        case JAILER_TAG:{
            moveAction::onContactBeginPro_Jailer();
            break;
        }
        case MOUSE_TAG:{
            moveAction::onContactBeginPro_Mouse();
            break;
        }
        case COIN_TAG:{
            moveAction::onContactBeginPro_Coin();
            break;
        }
    }
    
    
    return true;
}


bool moveAction::onContactBeginPro_Jailer(){
    CCLOG("Pro_Jailer boom!!!!");
//    removeChild(protagonist);
    return true;
}

bool moveAction::onContactBeginPro_Mouse(){
    CCLOG("Pro_mouse boom!!!!");
    //    removeChild(protagonist);
    return true;
}


bool moveAction::onContactBeginPro_Coin(){
    CCLOG("Pro_coin boom!!!!");
    //    removeChild(protagonist);
    return true;
}





