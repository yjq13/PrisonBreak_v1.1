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

EventListenerTouchOneByOne* moveListener::create(Layer* layer){
    auto listener=EventListenerTouchOneByOne::create();
    listener->onTouchMoved=CC_CALLBACK_2(moveListener::onTouchMoved, this,layer);
    listener->onTouchBegan=CC_CALLBACK_2(moveListener::onTouchBegan, this);
    listener->onTouchEnded=CC_CALLBACK_2(moveListener::onTouchEnded, this, layer);
    
   
    return listener;
}


bool moveListener::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    
    CCLOG("begin with (%f,%f)",touch->getLocation().x,touch->getLocation().y);
    //计数器归零,数组清空
    index=0;
    for (int i=0;i<10000;i++){
        points[i]=ccp(0,0);
    }
    //计算玩家触摸点是否在起始点内
    //auto p=touch->getLocation();
    // CCLOG("(%f,%f)",startPosition->getPositionX(),p.y);
    //注意，下面的调用是个空值，为了不报错加的
    return START_SECTION.isInside(touch);
    return true;
}

void moveListener::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event, Layer* layer){
    isMoved=true;
    points[index]=touch->getLocation();
    auto p=touch->getLocation();
    auto r=DrawNode::create();
    layer->addChild(r);
    if(index>0){
        r->setTag(index);
        r->drawSegment(points[index-1], p, 10, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
    }
    index++;
}

void moveListener::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event, Layer* layer){
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

        Sprite* protagonist = Sprite_protagonist::create(1);
        protagonist->setPosition(points[0]);
        
        //layer->addChild(protagonist);
        //s->autorelease();
        
        layer->addChild(protagonist);
        
        
        auto allAction=Sequence::create(actionVector);
        protagonist->runAction(allAction);
        
        
    } else {
        for(int i = 0; i<=index;i++){
            layer->removeChildByTag(i);
        }
        
    }
    isMoved=false;
    
    
}


