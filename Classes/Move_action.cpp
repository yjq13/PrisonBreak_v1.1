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
        node_Pro = contact.getShapeA()->getBody()->getNode();
        node_else =contact.getShapeB()->getBody()->getNode();
        body_tag = node_else->getTag();
            }else{
        node_Pro = contact.getShapeB()->getBody()->getNode();
        node_else =contact.getShapeA()->getBody()->getNode();
        body_tag = node_else->getTag();
        
    }
    
    switch((body_tag/1000)*1000){
            
        case JAILER_TAG:{
            moveAction::onContactBeginPro_Jailer();
            node_Pro->stopAllActions();
            
            node_else->setVisible(false);
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





