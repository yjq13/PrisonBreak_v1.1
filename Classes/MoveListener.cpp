//
//  MoveListener.cpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 10/23/15.
//
//

#include "MoveListener.h"
#include "Sprite_protagonist.h"
#include "cocos2d.h"
USING_NS_CC;

EventListenerTouchOneByOne* moveListener::create(Layer* layer){
    auto listener=EventListenerTouchOneByOne::create();
    listener->onTouchMoved=CC_CALLBACK_2(moveListener::onTouchMoved, this, layer);
    listener->onTouchBegan=CC_CALLBACK_2(moveListener::onTouchBegan, this);
    listener->onTouchEnded=CC_CALLBACK_2(moveListener::onTouchEnded, this, layer);
    
    return listener;
}


bool moveListener::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    CCLOG("begin");
    //计数器归零,数组清空
    index=0;
    for (int i=0;i<10000;i++){
        points[i]=ccp(0,0);
    }
    //获得起始点坐标
    auto p=touch->getLocation();
    
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
    //下面是主角跟随路线移动
        //下面是填装动作的容器
    bool isValid = moveListener::isMoveValid();
    Vector<FiniteTimeAction*> actionVector;
    for (int i=0;i<10000;i++){
        if (i!=0&&points[i].x!=0) {
            actionVector.pushBack(MoveTo::create(ccpSub(points[i-1], points[i]).length()/100, points[i]));
        }
    }
    if(isMoved&&isValid){
        Sprite_protagonist spritePro;
        
        Sprite* protagonist = spritePro.create();
        
        layer->addChild(protagonist);
        //s->autorelease();
        protagonist->setPosition(points[0]);
        layer->addChild(protagonist);

        
        auto allAction=Sequence::create(actionVector);
        protagonist->runAction(allAction);
        
    }
//    else{
//        if(!isValid){
//            for(int i = 0; i<=index;i++){
//            layer->removeChildByTag(i);
//            }
//        }
//    }
    
    isMoved=false;
}

//判断是否有效地移动
bool moveListener::isMoveValid(){
    
    bool isValid = false;
    if(isStart&&isDestination){
        isValid = true;
    }
    
    return isValid;
}
