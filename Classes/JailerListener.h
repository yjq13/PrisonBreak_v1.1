//
//  JailerListener.hpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 1/18/16.
//
//

#ifndef JailerListener_hpp
#define JailerListener_hpp


#include <stdio.h>
#include <cocos2d.h>
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

class JailerListener : public cocos2d::EventListenerTouchOneByOne{
private:
    cocos2d::EventListenerTouchOneByOne* listener;
    
    cocos2d::Sprite* jailer;
    
    cocostudio::timeline::ActionTimeline* timeline;
public:
    float speed;
    
    virtual EventListenerTouchOneByOne* create(cocos2d::Sprite* getSprite,cocostudio::timeline::ActionTimeline* Timeline);
    
    cocos2d::Rect getRect();
    
    void Delay(float dt);
    
    JailerListener(){
        CCLOG("hello JailerListener");
    }
    
    ~JailerListener(){
        CCLOG("goodbye Jailerlistener");
    };
    
    bool onTouchBegan(cocos2d::Touch* touch,cocos2d::Event* event);
    
    void onTouchMoved(cocos2d::Touch* touch,cocos2d::Event* event);
    
    void onTouchEnded(cocos2d::Touch* touch,cocos2d::Event* event);
    
    //bool isMoveValid();
};
#endif /* JailerListener_hpp */
