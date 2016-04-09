//
//  TimeLineLoad.hpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 12/12/15.
//
//

#ifndef TimeLineLoad_hpp
#define TimeLineLoad_hpp
#include "Constant_Use.h"
#include <stdio.h>
#include "cocostudio/CocoStudio.h"
using namespace std;
class SchedulerManager{
public:
    
    static void setProScheduler(Scheduler* sch);
    
    static TIMELINE loadTimeLine(cocos2d::Node* rootNodeL);
    
    static void stopTimeLine(int Tag);
        
    static void pauseTimeLine();
    
    static void pausePro();
    
    static void resumePro();
    
    static void resumeTimeLine();
    
    static void resumeTimeLine(int Tag);
    SchedulerManager(){
        CCLOG("hello TimeLineLoad");
    }
    ~SchedulerManager(){
        CCLOG("goodbye TimeLineLoad");
    }
};
#endif /* TimeLineLoad_hpp */
