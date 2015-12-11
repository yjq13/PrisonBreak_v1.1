//
//  Sprite_mouse.hpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 10/22/15.
//
//

#ifndef Sprite_mouse_h
#define Sprite_mouse_h

#include <cocos2d.h>
class Sprite_mouse : public cocos2d::Sprite{
public:
    static cocos2d::Sprite* create(int number,cocos2d::Sprite* getSprite);
    static void setMouse(int number,cocos2d::Sprite* getSprite);
};

#endif /* Sprite_mouse_hpp */
