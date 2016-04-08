//
//  Constant_Game.cpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 16/4/7.
//
//

#include "Constant_Game.h"

Section START_SECTION = Section();

Section DESTINATION_SECTION = Section();

Section STOP_SECTION = Section();

TIMELINE _TIMELINE = *new TIMELINE();

Scheduler* PRO_SCHEDULER = new Scheduler();

set<void *> target_else = *new set<void *>();

set<void *> target_pro = *new set<void *>(); 