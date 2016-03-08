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
    cocostudio::timeline::ActionTimeline* timeline;
    
    Sprite* sprite;
    
    JailerListener* Listener;
    
public:    
    JailerListener* getlistener();
    
    Sprite_jailer(){
        CCLOG("我是精灵警察！我被创造啦！！！");
    }
    
    ~Sprite_jailer(){
        CCLOG("我是精灵警察！我被删掉啦！！！");
    }

    
    cocostudio::timeline::ActionTimeline* getTimeLine();
    
    void setJailer(int number,cocos2d::Sprite* getSprite);
    
    void setTimeline(TIMELINE timeline);
    
    void setListener(JailerListener* listener);
};


#endif /* Sprite_jailer_hpp */
