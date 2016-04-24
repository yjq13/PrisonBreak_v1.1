//
//  Move_action.cpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 10/23/15.
//
//

#include "ContactManager.h"
#include "cocos2d.h"
#include <iostream>
#include "Constant_Use.h"
#include "CacheData.h"
#include "MenuManager.h"
#include "SchedulerManager.h"
#include "SpriteManager.h"
#include "Constant.h"
USING_NS_CC;

EventListenerPhysicsContact* ContactManager::createProAction(){
    
    EventListenerPhysicsContact* contactListener=EventListenerPhysicsContact::create();
    
    contactListener->onContactBegin=CC_CALLBACK_1(ContactManager::switchMoveAction, this);
    //contactListener->onContactPreSlove=CC_CALLBACK_1(moveAction::switchMoveAction, this);
    contactListener->onContactSeparate=CC_CALLBACK_1(ContactManager::switchMoveActionAfter, this);
    //timeLine = _TIMELINE;
    
    //Sprite* node  = NodeL->getChildByName<Sprite*>("Sprite_Mouse_1");
    
    CCLOG("contact is OK!!!!!");
    
    return contactListener;
    
}

bool ContactManager::switchMoveAction(const cocos2d::PhysicsContact &contact){
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
            ContactManager::onContactBeginPro_Section();
            break;
        }
        case JAILER_TAG:{
            ContactManager::onContactBeginPro_Jailer();
            break;
        }
        case MOUSE_TAG:{
            ContactManager::onContactBeginPro_Mouse();
            break;
        }
        case COIN_TAG:{
            ContactManager::onContactBeginPro_Coin();
            break;
        }
        case WALL_TAG:{
            ContactManager::onContactBeginPro_Wall();
            break;
        }
        case SECTION_END_TAG:{
            ContactManager::onContactBeginPro_End();
            break;
        }
    }
    
    
    return false;
}



bool ContactManager::switchMoveActionAfter(const cocos2d::PhysicsContact &contact){
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
            ContactManager::onContactSeparatePro_Section();
            break;
        }
    }
    
    
    return false;
}

ContactManager::~ContactManager(){
    CCLOG("GOODBYE MOVEACTION");
}

bool ContactManager::onContactBeginPro_End(){
    
    target_pro = node_Pro->getScheduler()->pauseAllTargets();
    MenuManager menuManager;
    
    Node* layer =menuManager.create_Menu(SUCCESS_LAYER);
    
    updateConstant();
    
    node_else->getParent()->addChild(layer);
    
    MenuManager::move_in(layer);

    
    
    return false;
}



bool ContactManager::onContactBeginPro_Jailer(){
    //node_Pro->getScheduler()->setTimeScale(0.0f);
    if(node_else->isVisible()){
        SpriteManager::setStopJailer(node_else->getTag());
        
        SchedulerManager::stopTimeLine(node_else->getTag());
        node_else->setVisible(false);
        target_pro = node_Pro->getScheduler()->pauseAllTargets();
        MenuManager menuManager;
        
        Node* layer =menuManager.create_Menu(FAIL_LAYER);
        node_else->getParent()->addChild(layer);
        
        MenuManager::move_in(layer);
    }
    
    //layer->setVisible(true);
    CCLOG("Pro_Jailer boom!!!!");
    return false;
}



bool ContactManager::onContactBeginPro_Mouse(){
    if(node_else->isVisible()){
        
        SchedulerManager::stopTimeLine(node_else->getTag());
        node_else->setVisible(false);
        DIAMOND_GET++;
    }
    CCLOG("Pro_Mouse boom and diamond = %d!!!!",DIAMOND_GET);
    return false;
}



bool ContactManager::onContactBeginPro_Wall(){
    
    CCLOG("Pro_Wall boom!!!!");
    //    removeChild(protagonist);
    return false;
}




bool ContactManager::onContactBeginPro_Coin(){
    CCLOG("Pro_coin boom!!!!");
    //    removeChild(protagonist);
    return false;
}




bool ContactManager::onContactBeginPro_Section(){
    
    Scheduler* sched = node_Pro->getScheduler();
    
    //sched->pauseAllTargets();
    
    sched->setTimeScale(0.2f);
    
    //node_Pro->runAction(action);
        CCLOG("Pro_Section boom!!!!");
    return true;
}




bool ContactManager::onContactSeparatePro_Section(){
    
    Scheduler* sched = node_Pro->getScheduler();
    
    sched->setTimeScale(1.0f);

    return false;
}
