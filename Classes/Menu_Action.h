//
//  Menu_Action.hpp
//  PrisonBreak_v1.1
//
//  Created by 马长松 on 16/1/24.
//
//

#ifndef Menu_Action_hpp
#define Menu_Action_hpp

#include <stdio.h>
#include "cocos2d.h"
class MenuAction{
public:
    static void move_in(cocos2d::Node* menu);
    static void move_out(cocos2d::Node* menu);
};
#endif /* Menu_Action_hpp */
