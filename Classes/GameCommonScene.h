//
//  GameCommonScene.h
//  PrisonBreak
//
//  Created by yjq131250077 on 15/9/11.
//
//

#ifndef __PrisonBreak__GameCommonScene__
#define __PrisonBreak__GameCommonScene__

#include "cocos2d.h"
#include "MyScene.h"
USING_NS_CC;
class Game : public MyScene{
public:
    virtual Scene* createScene();
    PhysicsWorld* m_world;
    virtual bool init();
    void setPhyWorld(PhysicsWorld* world){
    m_world=world;
    };
    // a selector callback
    void setUI();
    
    //触屏测试
    CCSprite* sprite;
    //重载触控函数
    Point points[10000];//手指画出来的点集
    int index;//计数器
//    bool onTouchBegan(Touch* touch,Event* event);
//    void onTouchMoved(Touch* touch,Event* event);
//    void onTouchEnded(Touch* touch,Event* event);
   // void onTouchCancel(Touch* touch,Event* event);
    
    bool isMoved;//用于判断是否画完线路
    //下面是检测碰撞的方法
   // bool onContactBegin(const PhysicsContact& contact);
    Sprite* protagonist;
    Sprite* ballTwo;
    // implement the "static create()" method manually
    CREATE_FUNC(Game);
};
#endif /* defined(__PrisonBreak__GameCommonScene__) */

