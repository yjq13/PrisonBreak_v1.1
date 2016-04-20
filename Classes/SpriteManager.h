//
//  SpriteManager.hpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 16/4/20.
//
//

#ifndef SpriteManager_h
#define SpriteManager_h

#include <stdio.h>
#include "cocos2d.h"
#include "Sprite_jailer.h"
class SpriteManager{
public:
    static void setStopJailer(int Tag);
    
    static Sprite_jailer* getJailerByTag(int Tag);
};
#endif /* SpriteManager_hpp */
