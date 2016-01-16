//
//  SpriteListener.cpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 1/15/16.
//
//

#include "SpriteListener.h"
#include "cocos2d.h"
#include "GameCommonScene.h"
#include "Constant_Use.h"
USING_NS_CC;

EventListenerTouchOneByOne* SpriteListener::create(cocos2d::Sprite* getSprite){
    
    auto listener=EventListenerTouchOneByOne::create();
    
    listener->onTouchMoved =CC_CALLBACK_2(SpriteListener::onTouchMoved,this);
    listener->onTouchBegan =CC_CALLBACK_2(SpriteListener::onTouchBegan,this);
    listener->onTouchEnded =CC_CALLBACK_2(SpriteListener::onTouchEnded,this);
    protagonist = getSprite;
    CCLOG("SpriteListener is OK!!!!!");
    return listener;
}



//获取精灵的位置
Rect  SpriteListener::getRect()
{
    return Rect(protagonist->getPositionX() - protagonist->getContentSize().width * protagonist->getAnchorPoint().x,
                      protagonist->getPositionY() - protagonist->getContentSize().height * protagonist->getAnchorPoint().y,
                      protagonist->getContentSize().width, protagonist->getContentSize().height);
    // 为了能够自定义自己的位置大小采用了低效的函数而不是直接用成员变量
}

void SpriteListener::onTouchEnded(Touch* pTouch, Event* event)
{
}

//点击事件，开始点击，判断点击on坐标是在精灵的区域内
bool SpriteListener::onTouchBegan(Touch* touch, Event* event)
{
    
    Point touchLocation = touch->getLocation(); // 返回GL坐标
    Point localPos = protagonist->convertToNodeSpace(touchLocation);
    Rect rc = getRect();
    rc.origin = Point::ZERO;
    bool isTouched = rc.containsPoint(localPos);
    if(isTouched)
    {
        printf("我被点中了!\n");
        
        return true;
        
    }else{
        printf("没有点中");
        return false;
    }
    
}

void SpriteListener::onTouchMoved(Touch* touch, Event* event)
{
    
}