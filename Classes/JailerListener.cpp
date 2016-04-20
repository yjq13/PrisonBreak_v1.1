//
//  JailerListener.cpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 1/18/16.
//
//


#include "JailerListener.h"
#include "cocos2d.h"
#include "Constant_Use.h"
#include "SchedulerManager.h"
#include "GameManager.h"
#include "ListenerManager.h"
#include "SpriteManager.h"
USING_NS_CC;

EventListenerTouchOneByOne* JailerListener::create(cocos2d::Sprite* getSprite){
    
    EventListenerTouchOneByOne* listener=EventListenerTouchOneByOne::create();
    
    listener->onTouchMoved =CC_CALLBACK_2(JailerListener::onTouchMoved,this);
    listener->onTouchBegan =CC_CALLBACK_2(JailerListener::onTouchBegan,this);
    listener->onTouchEnded =CC_CALLBACK_2(JailerListener::onTouchEnded,this);
    jailer = getSprite;
    CCLOG("JailerListener is OK!!!!!");
    return listener;
}



//获取精灵的位置
Rect  JailerListener::getRect()
{
    CCLOG("@@@@%d",jailer->getTag());
    return Rect(jailer->getPositionX() - jailer->getContentSize().width * jailer->getAnchorPoint().x,
                jailer->getPositionY() - jailer->getContentSize().height * jailer->getAnchorPoint().y,
                jailer->getContentSize().width, jailer->getContentSize().height);
    // 为了能够自定义自己的位置大小采用了低效的函数而不是直接用成员变量
}

void JailerListener::onTouchEnded(Touch* pTouch, Event* event)
{
}

//点击事件，开始点击，判断点击on坐标是在精灵的区域内
bool JailerListener::onTouchBegan(Touch* touch, Event* event)
{
    
    Point touchLocation = touch->getLocation(); // 返回GL坐标
    Point localPos = jailer->convertToNodeSpace(touchLocation);
    Rect rc = getRect();
    rc.origin = Point::ZERO;
    bool isTouched = rc.containsPoint(localPos);
    //CCLOG("我被点啦！！！！");
    if(isTouched)
    {
        SpriteManager::setStopJailer(jailer->getTag());
        
        
        //jailer->getParent()->scheduleOnce(schedule_selector(this->Delay), 1.0f);
        //Director::getInstance()->getActionManager()->pauseTarget(jailer);
        SchedulerManager::stopTimeLine(jailer->getTag());
        //jailer->getParent()->stopAction(timeline);
        //jailer->getParent()->runAction(timeline);
        //timeline->setTimeSpeed(1);
       // timeline->pause();
        ListenerManager::removeListenerJailer();
        return false;
        
    }else{
        
    }
    return false;
}

void JailerListener::onTouchMoved(Touch* touch, Event* event){
    
    
    
}


void JailerListener::Delay(float dt){
    //CCLOG("%d",jailer->getTag());
    SchedulerManager::resumeTimeLine(jailer->getTag());
    }