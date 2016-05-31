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
#include <strstream>
#include "GameVo.h"
#include "OC_callGameInfo.h"
#include "GameManager.h"
USING_NS_CC;

EventListenerPhysicsContact* ContactManager::createProAction(){
    
    EventListenerPhysicsContact* contactListener=EventListenerPhysicsContact::create();
    
    contactListener->onContactBegin=CC_CALLBACK_1(ContactManager::switchMoveAction, this);
    //contactListener->onContactPreSlove=CC_CALLBACK_1(moveAction::switchMoveAction, this);
    contactListener->onContactSeparate=CC_CALLBACK_1(ContactManager::switchMoveActionAfter, this);
    //timeLine = _TIMELINE;
    
    //Sprite* node  = NodeL->getChildByName<Sprite*>("Sprite_Mouse_1");
    
    
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


bool ContactManager::onContactBeginPro_End(){
    
    target_pro = node_Pro->getScheduler()->pauseAllTargets();
    MenuManager menuManager;
    
    Node* layer =menuManager.create_Menu(SUCCESS_LAYER);
    
    getScore();
    strstream ss;
    string score;
    ss<<SCORE_GET;
    ss>>score;
    
    auto text_score=layer->getChildByName<ui::TextBMFont*>("Text_Score");
    text_score->setString(score);

    
    if(GameManager::stepNow==STEP){
        STEP++;
    }

    //此处应该有个算星星的方法
    int stateN = getState();
     strstream ss1;
    string state;
    ss1<<stateN;
    ss1>>state;
    CCLOG("星星：%d",stateN);
    auto text_state=layer->getChildByName<ui::TextBMFont*>("Text_State");
    text_state->setString(state);
    GameVo gVo;
    GameVo gvoG = getGameInfo(GameManager::stepNow);
    
    if(gvoG._score<SCORE_GET){
        gVo.setData(SCORE_GET, 3, getState());
        setGameInfo(gVo,GameManager::stepNow);
    }
    
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

    return false;
}



bool ContactManager::onContactBeginPro_Mouse(){
    if(node_else->isVisible()){
        
        SchedulerManager::stopTimeLine(node_else->getTag());
        node_else->setVisible(false);
        DIAMOND_GET++;
    }
    
    return false;
}



bool ContactManager::onContactBeginPro_Wall(){

    target_pro = node_Pro->getScheduler()->pauseAllTargets();
    MenuManager menuManager;
    
    Node* layer =menuManager.create_Menu(FAIL_LAYER);
    node_else->getParent()->addChild(layer);
    
    MenuManager::move_in(layer);

    return false;
}




bool ContactManager::onContactBeginPro_Coin(){

    //    removeChild(protagonist);
    return false;
}




bool ContactManager::onContactBeginPro_Section(){
    
    Scheduler* sched = node_Pro->getScheduler();
    
    if(node_else->getTag()>= 6500){
    sched->setTimeScale(1.5f);
    }else{
    sched->setTimeScale(0.5f);
    }
    //node_Pro->runAction(action);

    return true;
}




bool ContactManager::onContactSeparatePro_Section(){
    
    Scheduler* sched = node_Pro->getScheduler();
    
    sched->setTimeScale(1.0f);

    return false;
}
