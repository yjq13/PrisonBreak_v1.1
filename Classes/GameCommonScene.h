//
//  GameCommonScene.h
//  PrisonBreak
//
//  Created by yjq131250077 on 15/9/11.
//
//

#ifndef __PrisonBreak__GameCommonScene__
#define __PrisonBreak__GameCommonScene__
#include "ContactManager.h"
#include "cocos2d.h"
#include "MyScene.h"
#include "Section.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "moveListener.h"
#include "gameLoad.h"
#include <string>
using namespace std;

USING_NS_CC;
class Game : public MyScene{
    gameLoad gameload;
    moveListener movelistener;
    ContactManager moveaction;
    cocos2d::Node* rootNodeL;
    cocos2d::Node* failNodeL;
    cocos2d::Node* successNodeL;
    cocos2d::Node* stopNodeL;
    cocostudio::timeline::ActionTimeline* rootTimeLine;
    cocostudio::timeline::ActionTimeline* rootTimeLine2;
public:
    set<void *> target;
    bool toolLock = false;
    static Scene* createScene();
    PhysicsWorld* m_world;
    virtual bool init();
    void setPhyWorld(PhysicsWorld* world){
    m_world=world;
    };
    ~Game();
    void menuCloseCallback(Ref* pSender);
    
    void stopCallback(Ref* pSender);
    
    void Callrestart(Ref* pSender);
    
    void Callresume(Ref* pSender);
    
    void toolCallback(Ref* pSender,int toolMark);
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

