//
//  Move_action.hpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 10/23/15.
//
//

#ifndef Move_action_h
#define Move_action_h

#include <stdio.h>
#include "cocos2d.h"
class moveAction : public cocos2d::EventListenerPhysicsContact{
public:
   virtual EventListenerPhysicsContact* create();
    
   bool onContactBegin(const cocos2d::PhysicsContact& contact);
};

#endif /* Move_action_hpp */
