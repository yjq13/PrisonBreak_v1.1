//
//  Constant_Use.cpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 10/20/15.
//
//

#include "Constant_Use.h"

cocos2d::TransitionPageTurn* Constant_Use::createTransition_Page(cocos2d::Scene* sceneNew){
    cocos2d::TransitionPageTurn* transition=cocos2d::TransitionPageTurn::create(1.5f, sceneNew, false);
    return transition;
}

bool Constant_Use::init(){
    CCLog("OKK!!@!!");
    VISIBLE_SIZE = cocos2d::Director::getInstance()->getVisibleSize();
    
    ORIGIN = cocos2d::Director::getInstance()->getVisibleOrigin();
    
    DESIGN_SIZE=Size(1334.0,750.0);
    
    return true;
}