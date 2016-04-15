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
class GameManager{
    
public:

static bool isStop;
    
static TIMELINE _TIMELINE;

static Scheduler* PRO_SCHEDULER;

static set<void *> target_else;

static set<void *> target_pro;

static vector<cocos2d::EventListenerTouchOneByOne*> JailerlistenerList;

static vector<cocos2d::EventListenerTouchOneByOne*> WalllistenerList;
};


#endif /* Constant_Game_hpp */
