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
#include "protagonistListener.h"
using namespace std;
class gameLoad{
public:
//    Sprite_jailer jailer[10];
//    
//    JailerListener jailerlistener[10];
//    
//    protagonistListener proListener;
    
    void loadGame(cocos2d::Node* rootNodeL);
    
    
    

};
#endif /* gameLoad_hpp */
