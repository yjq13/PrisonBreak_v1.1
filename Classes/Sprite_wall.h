//
//  Sprite_wall.hpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 10/22/15.
//
//

#ifndef Sprite_wall_h
#define Sprite_wall_h

#include <cocos2d.h>
class Sprite_wall : public cocos2d::Sprite{
public:    
    static cocos2d::Sprite* create();
    static void setWall(int number,cocos2d::Sprite* getSprite);
};

#endif /* Sprite_wall_hpp */
