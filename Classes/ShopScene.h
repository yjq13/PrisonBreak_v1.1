//
//  AnimationScene.h
//  PrisonBreak
//
//  Created by yjq131250077 on 15/9/11.
//
//

#ifndef __PrisonBreak__ShopScene__
#define __PrisonBreak__ShopScene__

#include "cocos2d.h"
#include "MyScene.h"
class Shop : public MyScene
{
    //cocos2d::Node* rootNodeS;
    cocos2d::Node* rootNodeL;
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    virtual void setUI();
    
    
    //买道具
    bool buyfew(Ref* pSender);
    bool buysome(Ref* pSender);
    bool buymany(Ref* pSender);
    
    //回退到上一界面
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Shop);
};


#endif /* defined(__PrisonBreak__AnimationScene__) */
