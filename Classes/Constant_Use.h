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
#include "cocostudio/CocoStudio.h"

using namespace std;
USING_NS_CC;

    typedef struct TIMELINE{
        cocostudio::timeline::ActionTimeline* TimeLine[20];
    }TIMELINE;


    //extern TIMELINE _TIMELINE;
    
    extern int SPEED_PRO;

    extern int ACTION_TAG;

    /*extern Section START_SECTION;

    extern Section DESTINATION_SECTION;

    extern Section STOP_SECTION;*/

    extern cocos2d::Size VISIBLE_SIZE;
    
    extern cocos2d::Vec2 ORIGIN;

    extern cocos2d::TransitionPageTurn* createTransition_Page(cocos2d::Scene* sceneNew);
    
    extern cocos2d::Size DESIGN_SIZE;

    extern string PATH_PART;

    extern string PATH_LEVEL;

    extern bool BUTTON_LOCK;

    extern int TIMELINE_NUM;

    const int PROTAGONIST_TAG = 1000;

    const int MOUSE_TAG = 2000;

    const int JAILER_TAG = 3000;

    const int COIN_TAG = 4000;

    const int WALL_TAG = 5000;

    const int SECTION_TAG = 6000;

    const int STOP_LAYER = 1;

    const int FAIL_LAYER = 2;

    const int SUCCESS_LAYER = 3;

#endif /* Constant_Use_h*/
