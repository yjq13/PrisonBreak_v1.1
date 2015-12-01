//
//  MoveListener.hpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 10/23/15.
//
//

#ifndef MoveListener_h
#define MoveListener_h

#include <cocos2d.h>
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "Section.h"
class moveListener : public cocos2d::EventListenerTouchOneByOne{
private:
    cocos2d::Point points[10000];//手指画出来的点集
    int index = 0;//计数器
    bool isMoved=false;
    bool moveLock=true;
   
public:
    virtual EventListenerTouchOneByOne* create(cocos2d::Node* layer,cocostudio::timeline::ActionTimeline* rootTimeLine);
    
    bool onTouchBegan(cocos2d::Touch* touch,cocos2d::Event* event,cocostudio::timeline::ActionTimeline* rootTimeLine);
    
    void onTouchMoved(cocos2d::Touch* touch,cocos2d::Event* event, cocos2d::Node* layer);
    
    void onTouchEnded(cocos2d::Touch* touch,cocos2d::Event* event, cocos2d::Node* layer,cocostudio::timeline::ActionTimeline* rootTimeLine);

    //bool isMoveValid();
};

#endif /* MoveListener_hpp */
