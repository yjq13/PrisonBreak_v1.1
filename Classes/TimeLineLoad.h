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
class TimeLineLoad{
public:
    static TIMELINE loadTimeLine(cocos2d::Node* rootNodeL);
        
    static void pauseTimeLine();
    
    static void resumeTimeLine();
    TimeLineLoad(){
        CCLOG("hello TimeLineLoad");
    }
    ~TimeLineLoad(){
        CCLOG("goodbye TimeLineLoad");
    }
};
#endif /* TimeLineLoad_hpp */
