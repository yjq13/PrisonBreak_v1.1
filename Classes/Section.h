//
//  Section.hpp
//  PrisonBreak_v1.1
//
//  Created by 马长松 on 15/10/24.
//
//
#ifndef Section_h
#define Section_h

#include <stdio.h>
#include "ui/CocosGUI.h"
class Section{
    cocos2d::Size* size;
    cocos2d::Vec2* position;
public:
    Section(cocos2d::Size* size,cocos2d::Vec2* position);
    Section();
    bool isInside(cocos2d::Touch* touch);
};
#endif /* Section_hpp */
