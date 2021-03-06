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
    return listener;
}



//获取精灵的位置
Rect  JailerListener::getRect()
{
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


        jailer->getParent()->scheduleOnce({CC_CALLBACK_1(JailerListener::Delay, this,jailer->getTag())}, 5.0f, "yjq is so diao");

        //Director::getInstance()->getActionManager()->pauseTarget(jailer);
        SchedulerManager::stopTimeLine(jailer->getTag());
        //jailer->getParent()->stopAction(timeline);
        //jailer->getParent()->runAction(timeline);
        //timeline->setTimeSpeed(1);
       // timeline->pause();
        ListenerManager::removeListenerJailer();
        GameManager::Button_Tool_1->setEnabled(false);
        return false;
        
    }else{
        ListenerManager::removeListenerJailer();
        CCLOG("没有点中");
    }
    return false;
}

void JailerListener::onTouchMoved(Touch* touch, Event* event){
    
    
    
}
void resumeCompensate(float dt ,int Tag){
    SchedulerManager::resumeTimeLine(Tag);
}

void JailerListener::Delay(float dt,int Tag){
    //CCLOG("%d",jailer->getTag());

        SchedulerManager::resumeTimeLine(Tag);
    }