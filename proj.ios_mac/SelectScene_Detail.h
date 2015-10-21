//
//  SelectScene_2.hpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 10/14/15.
//
//

#ifndef __SELECTSCENE_DETAIL_H__
#define __SELECTSCENE_DETAIL_H__

#include "cocos2d.h"
#include "MyScene.h"
class Select_Detail : public MyScene
{
private:
    cocos2d::Node* rootNodeS;
    cocos2d::Node* rootNodeL_Basis;
    cocos2d::Node* rootNodeL_Diamond;
    cocos2d::Node* rootNodeL_GameStep;
public:
    
    virtual cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void turnToGame(cocos2d::Ref* pSender,int step);
    
    void show_GameReady(cocos2d::Ref* pSender);
    
    void closeLayer(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(Select_Detail);
};


#endif /* SelectScene_2_hpp */
