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
    bool init();
    
    cocos2d::Size VISIBLE_SIZE;
    
    cocos2d::Vec2 ORIGIN;
    
    
    
    cocos2d::TransitionPageTurn* createTransition_Page(cocos2d::Scene* sceneNew);
    
    cocos2d::Size DESIGN_SIZE;
    
};
static Constant_Use CONSTANT_USE;

#endif /* Constant_Use_h*/
