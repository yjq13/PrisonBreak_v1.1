//
//  SpriteListener.cpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 1/15/16.
//
//

#include "protagonistListener.h"
#include "cocos2d.h"
#include "GameCommonScene.h"
#include "Constant_Use.h"
#include "GameManager.h"
USING_NS_CC;

EventListenerTouchOneByOne* protagonistListener::create(cocos2d::Sprite* getSprite){
    
    auto listener=EventListenerTouchOneByOne::create();
    
    listener->onTouchMoved =CC_CALLBACK_2(protagonistListener::onTouchMoved,this);
    listener->onTouchBegan =CC_CALLBACK_2(protagonistListener::onTouchBegan,this);
    listener->onTouchEnded =CC_CALLBACK_2(protagonistListener::onTouchEnded,this);
    protagonist = getSprite;

    return listener;
}



//获取精灵的位置
Rect  protagonistListener::getRect()
{
    return Rect(protagonist->getPositionX() - protagonist->getContentSize().width * protagonist->getAnchorPoint().x,
                      protagonist->getPositionY() - protagonist->getContentSize().height * protagonist->getAnchorPoint().y,
                      protagonist->getContentSize().width, protagonist->getContentSize().height);
    // 为了能够自定义自己的位置大小采用了低效的函数而不是直接用成员变量
}

void protagonistListener::onTouchEnded(Touch* pTouch, Event* event)
{
}

//点击事件，开始点击，判断点击on坐标是在精灵的区域内
bool protagonistListener::onTouchBegan(Touch* touch, Event* event)
{
    
    Point touchLocation = touch->getLocation(); // 返回GL坐标
    Point localPos = protagonist->convertToNodeSpace(touchLocation);
    Rect rc = getRect();
    rc.origin = Point::ZERO;
    bool isTouched = rc.containsPoint(localPos);
    if(isTouched)
    {
        GameManager::isTouchPro = true;
        return false;
        
    }else{
        return false;
    }
    
}

void protagonistListener::onTouchMoved(Touch* touch, Event* event)
{
    
}