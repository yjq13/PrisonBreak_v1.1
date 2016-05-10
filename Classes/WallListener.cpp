//
//  WallListener.cpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 1/18/16.
//
//

#include "WallListener.h"
#include "cocos2d.h"
#include "Constant_Use.h"
#include "GameManager.h"
#include "ListenerManager.h"
USING_NS_CC;

EventListenerTouchOneByOne* wallListener::create(cocos2d::Sprite* getSprite){
    
    auto listener=EventListenerTouchOneByOne::create();
    
    listener->onTouchMoved =CC_CALLBACK_2(wallListener::onTouchMoved,this);
    listener->onTouchBegan =CC_CALLBACK_2(wallListener::onTouchBegan,this);
    listener->onTouchEnded =CC_CALLBACK_2(wallListener::onTouchEnded,this);
    wall = getSprite;
    return listener;
}



//获取精灵的位置
Rect  wallListener::getRect()
{
    return Rect(wall->getPositionX() - wall->getContentSize().width * wall->getAnchorPoint().x,
                wall->getPositionY() - wall->getContentSize().height * wall->getAnchorPoint().y,
                wall->getContentSize().width, wall->getContentSize().height);
    // 为了能够自定义自己的位置大小采用了低效的函数而不是直接用成员变量
}

void wallListener::onTouchEnded(Touch* pTouch, Event* event)
{
}

//点击事件，开始点击，判断点击on坐标是在精灵的区域内
bool wallListener::onTouchBegan(Touch* touch, Event* event)
{
    Point touchLocation = touch->getLocation(); // 返回GL坐标
    Point localPos = wall->convertToNodeSpace(touchLocation);
    Rect rc = getRect();
    rc.origin = Point::ZERO;
    bool isTouched = rc.containsPoint(localPos);
    if(isTouched&&wall->isVisible())
    {
        wall->setVisible(false);
        wall->getPhysicsBody()->setEnable(false);
        ListenerManager::removeListenerWall();
        GameManager::Button_Tool_2->setEnabled(false);
    }else{
        ListenerManager::removeListenerWall();
    }
    return false;
}

void wallListener::onTouchMoved(Touch* touch, Event* event)
{
    
}