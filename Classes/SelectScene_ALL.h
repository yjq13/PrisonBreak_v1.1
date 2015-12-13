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
#include "MyScene.h"
class Select : public MyScene
{
    //cocos2d::Node* rootNodeS;
    cocos2d::Node* rootNodeL;
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    virtual void setUI();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void turnToSelect_Detail(cocos2d::Ref* pSender,int number);
    
    void turnToShop(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(Select);
};

#endif /* defined(__PrisonBreak__SelectScene__) */
