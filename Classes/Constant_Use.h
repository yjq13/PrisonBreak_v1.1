//
//  Constant_Use.hpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 10/20/15.
//
//

#ifndef Constant_Use_h
#define Constant_Use_h
#include <stdio.h>
USING_NS_CC;
class Constant_Use{
public:
    cocos2d::Size VISIBLE_SIZE = cocos2d::Director::getInstance()->getVisibleSize();
    
    cocos2d::Vec2 ORIGIN = cocos2d::Director::getInstance()->getVisibleOrigin();
    
    cocos2d::TransitionPageTurn* createTransition_Page(cocos2d::Scene* sceneNew);
    
    cocos2d::Size DESIGN_SIZE=Size(1334.0,750.0);
    
};
static Constant_Use CONSTANT_USE;

#endif /* Constant_Use_h*/
