#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "cocos2d.h"
#include "MyScene.h"
class Start : public MyScene
{
    //cocos2d::Node* rootNodeS;
    cocos2d::Node* rootNodeL;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    virtual void setUI();
    
    void turnToSelect(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(Start);
};

#endif // __HELLOWORLD_SCENE_H__
