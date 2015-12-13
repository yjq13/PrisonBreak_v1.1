//
//  setScene.h
//  PrisonBreak
//
//  Created by yjq131250077 on 15/9/17.
//
//

#ifndef __PrisonBreak__setScene__
#define __PrisonBreak__setScene__

#include <stdio.h>
#include "MyScene.h"
class About : public MyScene
{
    //cocos2d::Node* rootNodeS;
    cocos2d::Node* rootNodeL;
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    virtual void setUI();
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(About);
};



#endif /* defined(__PrisonBreak__setScene__) */
