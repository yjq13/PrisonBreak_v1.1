#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class Start : public cocos2d::Layer
{
public:
    cocos2d::Scene* createScene();

    bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void turnToSelect(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(Start);
};

#endif // __HELLOWORLD_SCENE_H__
