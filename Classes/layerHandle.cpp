//
//  MoveListener.cpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 10/23/15.
//
//

#include "layerHandle.h"
#include "Sprite_protagonist.h"
#include "cocos2d.h"
#include "Section.h"
#include "GameCommonScene.h"
#include "Constant_Use.h"
USING_NS_CC;

EventListenerTouchOneByOne* moveListener::create(Node* layer,cocostudio::timeline::ActionTimeline* rootTimeLine){
    
    auto listener=EventListenerTouchOneByOne::create();
    
    listener->onTouchMoved=CC_CALLBACK_2(moveListener::onTouchMoved, this,layer);
    listener->onTouchBegan=CC_CALLBACK_2(moveListener::onTouchBegan, this,rootTimeLine);
    listener->onTouchEnded=CC_CALLBACK_2(moveListener::onTouchEnded, this, layer,rootTimeLine);
    
   
    return listener;
}


bool moveListener::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event,cocostudio::timeline::ActionTimeline* rootTimeLine){
    if(!moveLock){
        return false;
    }
    CCLOG("begin with (%f,%f)",touch->getLocation().x,touch->getLocation().y);
    //计数器归零,数组清空
    index=0;
    for (int i=0;i<10000;i++){
        points[i]=ccp(0,0);
    }
    if(START_SECTION.isInside(touch)){
        rootTimeLine->gotoFrameAndPause(0);
    }
    return START_SECTION.isInside(touch);
    return true;
}

void moveListener::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event, Node* layer){
    
    isMoved=true;
    points[index]=touch->getLocation();
    auto p=touch->getLocation();
    auto r=DrawNode::create();
    layer->addChild(r);
    if(index>0){
        r->setTag(index+10000);
        r->drawSegment(points[index-1], p, 10, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
    }
    index++;
}

void moveListener::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event, Node* layer,cocostudio::timeline::ActionTimeline* rootTimeLine){
    printf("ed");
    auto p=touch->getLocation();
    if (isMoved&&(STOP_SECTION.isInside(touch)||DESTINATION_SECTION.isInside(touch)))
    {
        //下面是主角跟随路线移动
        //下面是填装动作的容器
        Vector<FiniteTimeAction*> actionVector;
        for (int i=0;i<10000;i++){
            if (i!=0&&points[i].x!=0) {
                actionVector.pushBack(MoveTo::create(ccpSub(points[i-1], points[i]).length()/100, points[i]));
            }
        }
        
        Sprite* protagonist = layer->getChildByName<Sprite*>("Sprite_Protagonist");
        
        protagonist->setPosition(points[0]);
        
        moveLock = false;
        
        
        
        
        auto allAction=Sequence::create(actionVector);
        protagonist->runAction(allAction);
        
        
    }
        for(int i = 10000; i<=index+10000;i++){
            layer->removeChildByTag(i);
        }
    
    rootTimeLine->gotoFrameAndPlay(0, true);
    
    isMoved=false;
    
    
    
}


