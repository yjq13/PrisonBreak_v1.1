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
#include "GameManager.h"
#include "cocos2d.h"
#include "MyScene.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "gameLoad.h"
#include <string>
#include "Constant_Use.h"
using namespace std;

USING_NS_CC;
class Game : public MyScene{
    GameManager manager;
    gameLoad gameload;
    ContactManager moveaction;
    cocos2d::Node* rootNodeL;
    cocos2d::Node* failNodeL;
    cocos2d::Node* successNodeL;
    cocos2d::Node* stopNodeL;
    cocostudio::timeline::ActionTimeline* rootTimeLine;
    
    cocos2d::Sprite* protagonist;
    cocos2d::Point points[10000];//手指画出来的点集
    int index = 0;//计数器
    bool isMoved=false;
    bool moveLock=true;
    int index_target = 1;
    cocos2d::Sequence* allAction;
    cocos2d::MoveTo* action[10000];
    std::list<cocos2d::CCPoint> pointList;
    //cocostudio::timeline::ActionTimeline* rootTimeLine2;
public:
    virtual void draw(cocos2d::Renderer *renderer,const cocos2d::Mat4& transform,uint32_t flags);
    void drawLine();
    set<void *> target;
    bool toolLock = false;
    static Scene* createScene();
    PhysicsWorld* m_world;
    virtual bool init();
    void setPhyWorld(PhysicsWorld* world){
    m_world=world;
    };
    Game(){
        CCLOG("hello game");
    }
    
    ~Game();
    
    
    void doPasue();
    
    void menuCloseCallback(Ref* pSender);
    
    void stopCallback(Ref* pSender);
    
    void Callrestart(Ref* pSender);
    
    void Callresume(Ref* pSender);
    
    void toolCallback(Ref* pSender,int toolMark);
    // a selector callback
    void setUI();
    
    bool onTouchBegan(cocos2d::Touch* touch,cocos2d::Event* event);
    
    void onTouchMoved(cocos2d::Touch* touch,cocos2d::Event* event);
    
    void onTouchEnded(cocos2d::Touch* touch,cocos2d::Event* event);
    

    
    virtual void onExit();
    virtual void update(float dt);
    // implement the "static create()" method manually
    CREATE_FUNC(Game);
};
#endif /* defined(__PrisonBreak__GameCommonScene__) */

