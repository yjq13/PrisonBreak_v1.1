//
//  gameLoad.hpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 12/11/15.
//
//

#ifndef gameLoad_hpp
#define gameLoad_hpp

#include <stdio.h>
#include "cocostudio/CocoStudio.h"
class gameLoad{
public:    
    static void loadGame(cocos2d::Node* rootNodeL,cocostudio::timeline::ActionTimeline* rootTimeLine);
    
};

#endif /* gameLoad_hpp */
