//
//  Constant_Use.hpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 10/20/15.
//
//

#ifndef Constant_Use_h
#define Constant_Use_h
#include <string>
#include <stdio.h>
#include "Section.h"
using namespace std;
USING_NS_CC;
    extern Section START_SECTION;

    extern Section DESTINATION_SECTION;

    extern Section STOP_SECTION;

    extern cocos2d::Size VISIBLE_SIZE;
    
    extern cocos2d::Vec2 ORIGIN;

    extern cocos2d::TransitionPageTurn* createTransition_Page(cocos2d::Scene* sceneNew);
    
    extern cocos2d::Size DESIGN_SIZE;

    extern string PATH_PART;

    extern string PATH_LEVEL;

    extern bool BUTTON_LOCK;

    const int PROTAGONIST_TAG = 1000;

    const int MOUSE_TAG = 2000;

    const int JAILER_TAG = 3000;

    const int COIN_TAG = 4000;

    const int WALL_TAG = 5000;
#endif /* Constant_Use_h*/
