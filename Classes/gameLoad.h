//
//  gameLoad.hpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 12/11/15.
//
//

#ifndef gameLoad_hpp
#define gameLoad_hpp

#include <stdio.h>
#include "cocostudio/CocoStudio.h"
#include "Constant_Use.h"
#include "Sprite_jailer.h"
#include "Sprite_wall.h"
#include "Sprite_mouse.h"
#include "Sprite_coin.h"
#include "Special_Section.h"
class gameLoad{
public:
    Sprite_jailer jailer[10];
    
    JailerListener jailerlistener[10];
    
    std::vector<Sprite_mouse*> MouseList;
    
    std::vector<Sprite_wall*> WallList;
    
    std::vector<Sprite_coin*> CoinList;
    
    std::vector<Sprite_SpecialSection*> SpecialSectionList;
    
    std::vector<cocos2d::EventListenerTouchOneByOne*> JailerlistenerList;
    
    std::vector<cocos2d::EventListenerTouchOneByOne*> WalllistenerList;

    void loadGame(cocos2d::Node* rootNodeL);
    
    gameLoad(){
        CCLOG("hello gameload");
    }
    ~gameLoad(){
        CCLOG("goodbye gameload");
    }
};

#endif /* gameLoad_hpp */
