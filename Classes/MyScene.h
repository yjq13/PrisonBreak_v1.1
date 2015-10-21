//
//  MyScene.hpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 10/22/15.
//
//

#ifndef MyScene_h
#define MyScene_h

#include "cocos2d.h"

class MyScene : public cocos2d::Layer
{
public:
    virtual cocos2d::Scene* createScene();
    
    virtual bool init();
    
    
    CREATE_FUNC(MyScene);
};


#endif /* MyScene_hpp */
