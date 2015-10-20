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