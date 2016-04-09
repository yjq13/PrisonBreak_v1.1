//
//  Constant_Game.hpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 16/4/7.
//
//

#ifndef Constant_Game_hpp
#define Constant_Game_hpp

#include "Constant_Use.h"
#include "Section.h"
class GameManager{
    
public:
    
static TIMELINE _TIMELINE;

static Section START_SECTION;

static Section DESTINATION_SECTION;

static Section STOP_SECTION;

static Scheduler* PRO_SCHEDULER;

static set<void *> target_else;

static set<void *> target_pro;

static vector<cocos2d::EventListenerTouchOneByOne*> JailerlistenerList;

static vector<cocos2d::EventListenerTouchOneByOne*> WalllistenerList;
};


#endif /* Constant_Game_hpp */
