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
private:
    cocos2d::Node* node_Pro;
    cocos2d::Node* node_else;
public:
    virtual EventListenerPhysicsContact* createProAction();
    
    bool onContactBeginPro_Jailer();
    
    bool onContactBeginPro_Mouse();

    bool onContactBeginPro_Coin();
    
    bool switchMoveAction(const cocos2d::PhysicsContact &contact);
};

#endif /* Move_action_hpp */
