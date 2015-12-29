//
//  Move_action.cpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 10/23/15.
//
//

#include "Move_action.h"
#include "cocos2d.h"
#include <iostream>
#include "Constant_Use.h"
USING_NS_CC;

EventListenerPhysicsContact* moveAction::createProAction(TIMELINE rootTimeLine){
    
    EventListenerPhysicsContact* contactListener=EventListenerPhysicsContact::create();
    
    contactListener->onContactBegin=CC_CALLBACK_1(moveAction::switchMoveAction, this);
    //contactListener->onContactPreSlove=CC_CALLBACK_1(moveAction::switchMoveAction, this);
    contactListener->onContactSeparate=CC_CALLBACK_1(moveAction::switchMoveActionAfter, this);
    timeLine = rootTimeLine;
    
    //Sprite* node  = NodeL->getChildByName<Sprite*>("Sprite_Mouse_1");
    
    CCLOG("contact is OK!!!!!");
    
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
        node_else = contact.getShapeA()->getBody()->getNode();
        body_tag = node_else->getTag();
    }
    
    switch((body_tag/1000)*1000){
        case SECTION_TAG:{
            moveAction::onContactBeginPro_Section();
            break;
        }
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
    
    
    return false;
}



bool moveAction::switchMoveActionAfter(const cocos2d::PhysicsContact &contact){
    int body_tag = 0;
    //找到碰撞物体
    
    if(contact.getShapeA()->getBody()->getNode()->getTag()==PROTAGONIST_TAG){
        node_Pro = contact.getShapeA()->getBody()->getNode();
        node_else =contact.getShapeB()->getBody()->getNode();
        body_tag = node_else->getTag();
    }else{
        node_Pro = contact.getShapeB()->getBody()->getNode();
        node_else = contact.getShapeA()->getBody()->getNode();
        body_tag = node_else->getTag();
    }
    
    switch((body_tag/1000)*1000){
            
        case SECTION_TAG:{
            moveAction::onContactSeparatePro_Section();
            break;
        }
    }
    
    
    return false;
}

moveAction::~moveAction(){
    CCLOG("GOODBYE MOVEACTION");
}

bool moveAction::onContactBeginPro_Jailer(){

    CCLOG("Pro_Jailer boom!!!!");
    return false;
}

bool moveAction::onContactBeginPro_Mouse(){
    if(node_else->isVisible()){
    for(int i = 0;i<20;i++){
        //CCLOG("timeline:%d",timeLine.TimeLine[i]->getTag());
        if(timeLine.TimeLine[i]->getTag()!=157)
            break;
        CCLOG("timeline:%d",timeLine.TimeLine[i]->getFlags());
        if((signed)timeLine.TimeLine[i]->getFlags()==node_else->getTag()){
            
            timeLine.TimeLine[i]->pause();
            break;
        }
    }
        node_else->setVisible(false);

    }
    CCLOG("Pro_Mouse boom!!!!");
    return false;
}


bool moveAction::onContactBeginPro_Coin(){
    CCLOG("Pro_coin boom!!!!");
    //    removeChild(protagonist);
    return false;
}

bool moveAction::onContactBeginPro_Section(){

    Scheduler* sched1 = node_Pro->getScheduler();
    
    sched1->setTimeScale(0.2f);
    
    //node_Pro->runAction(action);
        CCLOG("Pro_Section boom!!!!");
    return true;
}


bool moveAction::onContactSeparatePro_Section(){
    
    Scheduler* sched1 = node_Pro->getScheduler();
    
    sched1->setTimeScale(1.0f);

    CCLOG("王宁是水杯!!!!");
    return false;
}


