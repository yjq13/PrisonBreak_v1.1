//
//  Sprite_coin.hpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 10/22/15.
//
//

#ifndef Sprite_coin_h
#define Sprite_coin_h

#include <cocos2d.h>
class Sprite_coin : public cocos2d::Sprite{
public:    
    static cocos2d::Sprite* create(int number,cocos2d::Sprite* getSprite);
    
};

#endif /* Sprite_coin_hpp */
