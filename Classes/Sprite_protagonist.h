//
//  Sprite_Component.hpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 10/22/15.
//
//

#ifndef Sprite_Component_protagonist_h
#define Sprite_Component_protagonist_h

#include <cocos2d.h>
class Sprite_protagonist : public cocos2d::Sprite{
public:
    //Sprite_protagonist();
    
    static cocos2d::Sprite* create(int number);
};

#endif /* Sprite_Component_hpp */
