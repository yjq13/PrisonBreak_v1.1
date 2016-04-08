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

extern TIMELINE _TIMELINE;

extern Section START_SECTION;

extern Section DESTINATION_SECTION;

extern Section STOP_SECTION;

extern Scheduler* PRO_SCHEDULER;

extern set<void *> target_else;

extern set<void *> target_pro;
#endif /* Constant_Game_hpp */
