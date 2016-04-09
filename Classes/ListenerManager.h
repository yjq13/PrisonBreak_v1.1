//
//  ListenerManager.hpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 16/4/9.
//
//

#ifndef ListenerManager_h
#define ListenerManager_h

#include <stdio.h>
#include "cocos2d.h"

class ListenerManager{
public:
    static void addListenerJailer();
    
    static void addListenerWall();
    
    static void removeListenerJailer();
    
    static void removeListenerWall();
};

#endif /* ListenerManager_hpp */
