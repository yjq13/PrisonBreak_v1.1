//
//  Constant_Use.cpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 10/20/15.
//
//

#include "Constant_Use.h"

cocos2d::TransitionPageTurn* createTransition_Page(cocos2d::Scene* sceneNew){
    cocos2d::TransitionPageTurn* transition=cocos2d::TransitionPageTurn::create(0.1f, sceneNew, false);
    return transition;
}

cocos2d::Size VISIBLE_SIZE = cocos2d::Director::getInstance()->getWinSize();

cocos2d::Vec2 ORIGIN = cocos2d::Director::getInstance()->getVisibleOrigin();

cocos2d::Size DESIGN_SIZE = Size(2208.0,1242.0);

/*Section START_SECTION = Section();

Section DESTINATION_SECTION = Section();

Section STOP_SECTION = Section();

TIMELINE _TIMELINE = *new TIMELINE();*/

int SPEED_PRO = 500;

int ACTION_TAG = 0;

int TIMELINE_NUM = 0;

long TIMESTART = 0;

long TIMEEND = 0;

string PATH_PART = "";

string PATH_LEVEL = "";

bool BUTTON_LOCK = true;

int debugInt = 0;

MusicManager* MUSICMANAGER=new MusicManager();

long getTime(){
    struct timeval nowTimeval;
    gettimeofday(&nowTimeval, NULL);
    return (nowTimeval.tv_sec*1000 + nowTimeval.tv_usec / 1000);
}


