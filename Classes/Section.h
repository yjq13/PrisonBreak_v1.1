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
class End_Section : public cocos2d::Sprite{
public:
    static void setEnd_Section(int number,cocos2d::Sprite* getSprite);
};

#endif /* Section_hpp */
