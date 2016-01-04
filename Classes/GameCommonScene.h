//
//  GameCommonScene.h
//  PrisonBreak
//
//  Created by yjq131250077 on 15/9/11.
//
//

#ifndef __PrisonBreak__GameCommonScene__
#define __PrisonBreak__GameCommonScene__
#include "Move_action.h"
#include "cocos2d.h"
#include "MyScene.h"
#include "Section.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "layerHandle.h"
#include <string>
using namespace std;

USING_NS_CC;
class Game : public MyScene{
    moveListener movelistener;
    moveAction moveaction;
    cocos2d::Node* rootNodeL;
    cocos2d::Node* failNodeL;
    cocos2d::Node* successNodeL;
    cocostudio::timeline::ActionTimeline* rootTimeLine;
    cocostudio::timeline::ActionTimeline* rootTimeLine2;
public:
    static Scene* createScene();
    PhysicsWorld* m_world;
    virtual bool init();
    void setPhyWorld(PhysicsWorld* world){
    m_world=world;
    };
    ~Game();
    void menuCloseCallback(Ref* pSender);
    
    void failCloseCallback(Ref* pSender);
    
    void successCloseCallback(Ref* pSender);
    
    void Callrestart(Ref* pSender);
    // a selector callback
    void setUI();

    int index;//计数器
    
    bool isMoved;//用于判断是否画完线路
    
    virtual void onExit();
    virtual void update(float dt);
    // implement the "static create()" method manually
    CREATE_FUNC(Game);
};
#endif /* defined(__PrisonBreak__GameCommonScene__) */

