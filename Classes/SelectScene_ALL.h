//
//  SelectScene.h
//  PrisonBreak
//
//  Created by yjq131250077 on 15/9/11.
//
//

#ifndef __PrisonBreak__SelectScene_ALL__
#define __PrisonBreak__SelectScene_ALL__

#include "cocos2d.h"
class Select : public cocos2d::Layer
{
    cocos2d::Node* rootNodeS;
    cocos2d::Node* rootNodeL;
public:
    cocos2d::Scene* createScene();
    
    bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void turnToSelect_2(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(Select);
};

#endif /* defined(__PrisonBreak__SelectScene__) */
