//
//  SpriteListener.hpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 1/15/16.
//
//

#ifndef SpriteListener_hpp
#define SpriteListener_hpp

#include <stdio.h>
#include <cocos2d.h>
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "Section.h"
class SpriteListener : public cocos2d::EventListenerTouchOneByOne{
private:
    cocos2d::Sprite* protagonist;
    cocos2d::Point points[10000];//手指画出来的点集
    int index = 0;//计数器
    bool isMoved=false;
    bool moveLock=true;
    int index_target = 1;
    cocos2d::Node* target[10000];
    cocos2d::Sequence* allAction;
    cocos2d::MoveTo* action[10000];
public:
    virtual EventListenerTouchOneByOne* create(cocos2d::Sprite* getSprite);
    cocos2d::Rect getRect();
    
    bool onTouchBegan(cocos2d::Touch* touch,cocos2d::Event* event);
    
    void onTouchMoved(cocos2d::Touch* touch,cocos2d::Event* event);
    
    void onTouchEnded(cocos2d::Touch* touch,cocos2d::Event* event);
    
    //bool isMoveValid();
};
#endif /* SpriteListener_hpp */
