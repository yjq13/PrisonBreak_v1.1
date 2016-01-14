//
//  GameCommonScene.cpp
//  PrisonBreak
//
//  Created by yjq131250077 on 15/9/11.
//
//

#include "GameCommonScene.h"
#include "Sprite_protagonist.h"

#include "Move_action.h"
#include "cocostudio/CocoStudio.h"
#include "Constant_Use.h"
#include "ui/CocosGUI.h"
#include "Section.h"
#include "Sprite_jailer.h"
#include <string>
#include <iostream>
#include "SelectScene_Detail.h"
#include "Sprite_wall.h"
#include "gameLoad.h"
#include "TimeLineLoad.h"
#include "TimeLineVo.h"
#include "OC_callGameInfo.h"
#include "CacheData.h"
USING_NS_CC;
using namespace ui;

int i = 0;
Scene* Game::createScene(){
    auto scene=Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto layer=Game::create();
    CCLOG("HELLO GAME");
    layer->setPhyWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    return scene;
}

Game::~Game(){
    
    CCLOG("GOODBYE GAME");

    }
bool Game::init(){
    
    scheduleUpdate();
    
    initCacheData();
    //rootNodeS = CSLoader::createNode("res/Game/Scene_Game.csb");
    
    string hand = "res/Game/";
    string tail = ".csb";
    string follow = "/Layer_Game_Level_";
    string all = hand+PATH_PART+follow+PATH_LEVEL+tail;
    
    failNodeL = CSLoader::createNode("res/Game/Other/Layer_Fail.csb");
    successNodeL = CSLoader::createNode("res/Game/Other/Layer_Success.csb");
    rootNodeL = CSLoader::createNode(all);
    //failNodeL->setTag(131250077);
    rootTimeLine = CSLoader::createTimeline(all);
    
    
    TIMELINE timeline = TimeLineLoad::loadTimeLine(rootNodeL);

    
    EventListenerPhysicsContact* contactListener = moveaction.createProAction(timeline);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    EventListenerTouchOneByOne* listener = movelistener.create(rootNodeL);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    setUI();
    
    return true;
}
void Game::setUI(){
    //测试在界面上放置组件
//    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //rootNodeS->addChild(rootNodeL);
    rootNodeL->setContentSize(VISIBLE_SIZE);
    ui::Helper::doLayout(rootNodeL);
    failNodeL->setTag(131250077);
    successNodeL->setTag(131250057);
    rootNodeL->addChild(successNodeL);
    rootNodeL->addChild(failNodeL);
    successNodeL->setVisible(false);
    failNodeL->setVisible(false);
    addChild(rootNodeL);
    
    auto Button_Close_Fail = failNodeL->getChildByName<ui::Button*>("Button_Close");
    
    Button_Close_Fail->addTouchEventListener(this, toucheventselector(Game::failCloseCallback));
    
    auto Button_Close_Success = successNodeL->getChildByName<ui::Button*>("Button_Close");
    
    Button_Close_Success->addTouchEventListener(this, toucheventselector(Game::successCloseCallback));
    
    
    
    
    
    auto Button_Back = rootNodeL->getChildByName<ui::Button*>("Button_Back");
    
    Button_Back->addTouchEventListener(this,toucheventselector(Game::menuCloseCallback));
    
    auto Button_Back_Fail = failNodeL->getChildByName<ui::Button*>("Button_Back");
    
    Button_Back_Fail->addTouchEventListener(this, toucheventselector(Game::menuCloseCallback));
    
    auto Button_Back_Success = successNodeL->getChildByName<ui::Button*>("Button_Back");
    
    Button_Back_Success->addTouchEventListener(this, toucheventselector(Game::menuCloseCallback));
    
    
    
    auto Button_Retry_Fail = failNodeL->getChildByName<ui::Button*>("Button_Retry");
    
    Button_Retry_Fail->addTouchEventListener(this,toucheventselector(Game::Callrestart));
    
    auto Button_Retry_Success = successNodeL->getChildByName<ui::Button*>("Button_Retry");
    
    Button_Retry_Success->addTouchEventListener(this,toucheventselector(Game::Callrestart));

    
    //未完成部分
    auto Button_Next_Success = successNodeL->getChildByName<ui::Button*>("Button_Next");
    
    Button_Next_Success->addTouchEventListener(this,toucheventselector(Game::Callrestart));
    
    gameLoad::loadGame(rootNodeL);
    
    
    
   }
void Game::update(float dt){
    auto scale=VISIBLE_SIZE.width/DESIGN_SIZE.width;
    
    //坐标重绘
    Sprite* Demo_jailer[10];
    int index = 0;
    do{
        index++;
        char number[25];
        memset(number,0,sizeof(number));
        sprintf(number,"%d",index);
        string numberStr=number;
        
        string first = "Sprite_Jailer_";
        string all = first+numberStr;
        
        Demo_jailer[index] = rootNodeL->getChildByName<Sprite*>(all);
        if(Demo_jailer[index]!=NULL){
            auto position_Before=Demo_jailer[index]->getPosition();
            Demo_jailer[index]->setPositionX(position_Before.x*scale);
        }
    }while(Demo_jailer[index]!=NULL);
    
    Sprite* Demo_wall[10];
    index = 0;
    do{
        index++;
        char number[25];
        memset(number,0,sizeof(number));
        sprintf(number,"%d",index);
        string numberStr=number;
        
        string first = "Sprite_Wall_";
        string all = first+numberStr;
        
        Demo_wall[index] = rootNodeL->getChildByName<Sprite*>(all);
        if(Demo_wall[index]!=NULL){
            auto position_Before=Demo_wall[index]->getPosition();
            Demo_wall[index]->setPositionX(position_Before.x*scale);
        }
    }while(Demo_wall[index]!=NULL);
    
    
    Sprite* Demo_Mouse[10];
    index = 0;
    do{
        index++;
        char number[25];
        memset(number,0,sizeof(number));
        sprintf(number,"%d",index);
        string numberStr=number;
        
        string first = "Sprite_Mouse_";
        string all = first+numberStr;
        
        Demo_Mouse[index] = rootNodeL->getChildByName<Sprite*>(all);
        if(Demo_Mouse[index]!=NULL)
        {
            auto position_Before=Demo_Mouse[index]->getPosition();
            Demo_Mouse[index]->setPositionX(position_Before.x*scale);
        }
    }while(Demo_Mouse[index]!=NULL);
}

void Game::failCloseCallback(Ref* pSender){
    failNodeL->setVisible(false);
}


void Game::successCloseCallback(Ref* pSender){
    successNodeL->setVisible(false);
}


void Game::Callrestart(Ref *pSender){
    if(BUTTON_LOCK==false){
        BUTTON_LOCK= true;
    //menuCloseCallback(pSender);
    Director::getInstance()->popScene();
    
    CCLOG("pop GAME");
    }
}

void Game::menuCloseCallback(Ref* pSender)
{
    if(BUTTON_LOCK==false){
        BUTTON_LOCK= true;
        
    auto Scene =  Select_Detail::createScene();
    //auto transition=TransitionPageTurn::create(0.1f, Scene, false);
    
    Director::getInstance()->popScene();
    }
    //#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
    //#endif
}
void Game::onExit(){
    
}

