//
//  Sprite_jailer.hpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 10/22/15.
//
//

#ifndef Sprite_jailer_h
#define Sprite_jailer_h
#include <cocos2d.h>
#include "JailerListener.h"
#include "Constant_Use.h"
class Sprite_jailer{
    
   // Sprite* sprite;
    
    bool isStop;
    
    int Tag;
    
public:
    
    Sprite_jailer(){
        CCLOG("我是精灵警察！我被创造啦！！！");
    }
    
    ~Sprite_jailer(){
        CCLOG("我是精灵警察！我被删掉啦！！！");
    }

    
    void setIsStop(bool stop);
    
    bool getIsStop();
    
    int getTag();
    
    cocostudio::timeline::ActionTimeline* getTimeLine();
    
    void setJailer(int number,cocos2d::Sprite* getSprite);
        
};


#endif /* Sprite_jailer_hpp */
