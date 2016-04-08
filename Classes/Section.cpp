//
//  Section.cpp
//  PrisonBreak_v1.1
//
//  Created by 马长松 on 15/10/24.
//
//

#include "Section.h"
bool Section::isInside(cocos2d::Touch* touch){
    auto p=touch->getLocation();
    //CCLOG("(%f,%f)",startPosition->getPositionX(),p.y);
    if (p.x>=position->x&&p.x<=(position->x+size->width)&&p.y>=position->y&&p.y<=(position->y+size->height)) {
        

        //CCLOG("inside");
        return true;
    } else {
       CCLOG("position:%f,%f————size::%f,%f",position->x,position->y,size->width,size->height);
       CCLOG("outside");
        return false;
    }
}
Section::Section(cocos2d::Size* size,cocos2d::Vec2* position)
    {
        this->size=size;
        this->position=position;
    }
Section::Section(){
    
}