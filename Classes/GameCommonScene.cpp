//
//  GameCommonScene.cpp
//  PrisonBreak
//
//  Created by yjq131250077 on 15/9/11.
//
//

#include "GameCommonScene.h"
#include "Sprite_protagonist.h"
#include "JailerListener.h"
#include "WallListener.h"
#include "ContactManager.h"
#include "cocostudio/CocoStudio.h"
#include "Constant_Use.h"
#include "ui/CocosGUI.h"
#include "Section.h"
#include "Sprite_jailer.h"
#include <string>
#include <iostream>
#include "SelectScene_Detail.h"
#include "Sprite_wall.h"
#include "Menu_Action.h"
#include "TimeLineLoad.h"
#include "TimeLineVo.h"
#include "OC_callGameInfo.h"
#include "CacheData.h"
#include "pauseScene.h"
USING_NS_CC;
using namespace ui;

int i = 0;
Scene* Game::createScene(){
    auto scene=Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto layer=Game::create();
    
    layer->setPhyWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    scene->setTag(131250077);
    return scene;
}

Game::~Game(){
    
    CCLOG("goodbye game");

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
    stopNodeL = CSLoader::createNode("res/Game/Other/Layer_Stop.csb");
    rootNodeL = CSLoader::createNode(all);
    //failNodeL->setTag(131250077);
    rootTimeLine = CSLoader::createTimeline(all);
    
    //rootNodeL->setTag(131250081);
    
    _TIMELINE = TimeLineLoad::loadTimeLine(rootNodeL);
    
    EventListenerPhysicsContact* contactListener = moveaction.createProAction();
    
   // _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener,this);

    EventListenerTouchOneByOne* listener = movelistener.create(rootNodeL);
    
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
    
    setUI();

    
    return true;
}
void Game::setUI(){
    //测试在界面上放置组件
    //Size visibleSize = Director::getInstance()->getVisibleSize();
//  Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //rootNodeS->addChild(rootNodeL);
    rootNodeL->setContentSize(VISIBLE_SIZE);
    ui::Helper::doLayout(this);
    failNodeL->setTag(131250077);
    successNodeL->setTag(131250057);
    
    
    
    ////addChild(failNodeL);
    successNodeL->setPositionY(VISIBLE_SIZE.height);
    failNodeL->setPositionY(VISIBLE_SIZE.height);
    
    
    
    addChild(rootNodeL);
    
    
    
    
    
    
    auto Button_Back = rootNodeL->getChildByName<ui::Button*>("Button_Stop");
    
    Button_Back->addClickEventListener(CC_CALLBACK_1(Game::stopCallback,this));
    
    
    
    
    auto Button_Tool_1 = rootNodeL->getChildByName<ui::Button*>("Button_Tool_1");
    
    Button_Tool_1->addClickEventListener(CC_CALLBACK_1(Game::toolCallback,this,1));
    
    auto Button_Tool_2 = rootNodeL->getChildByName<ui::Button*>("Button_Tool_2");
    
    Button_Tool_2->addClickEventListener(CC_CALLBACK_1(Game::toolCallback,this,2));
    
    
    
    
    auto Button_Back_Fail = failNodeL->getChildByName<ui::Button*>("Button_Back");
    
    Button_Back_Fail->addTouchEventListener(CC_CALLBACK_1(Game::menuCloseCallback,this));
    
    auto Button_Back_Success = successNodeL->getChildByName<ui::Button*>("Button_Back");
    
    Button_Back_Success->addTouchEventListener(CC_CALLBACK_1(Game::menuCloseCallback,this));
    
    auto Button_Back_Stop = stopNodeL->getChildByName<ui::Button*>("Button_Back");
    
    Button_Back_Stop->addTouchEventListener(CC_CALLBACK_1(Game::menuCloseCallback,this));
    
    
    
    auto Button_Retry_Fail = failNodeL->getChildByName<ui::Button*>("Button_Retry");
    
    Button_Retry_Fail->addTouchEventListener(CC_CALLBACK_1(Game::Callrestart,this));
    
    auto Button_Retry_Success = successNodeL->getChildByName<ui::Button*>("Button_Retry");
    
    Button_Retry_Success->addTouchEventListener(CC_CALLBACK_1(Game::Callrestart,this));
    
    auto Button_Retry_Stop = stopNodeL->getChildByName<ui::Button*>("Button_Retry");
    
    Button_Retry_Stop->addTouchEventListener(CC_CALLBACK_1(Game::Callrestart,this));

    
    
    auto Button_Resume_Stop = stopNodeL->getChildByName<ui::Button*>("Button_Resume");
    
    Button_Resume_Stop->addTouchEventListener(CC_CALLBACK_1(Game::Callresume,this));
    
    //未完成部分
    auto Button_Next_Success = successNodeL->getChildByName<ui::Button*>("Button_Next");
    
    Button_Next_Success->addTouchEventListener(CC_CALLBACK_1(Game::Callrestart,this));
        
    gameload.loadGame(rootNodeL);
   }


void Game::update(float dt){
    auto scale=VISIBLE_SIZE.width/DESIGN_SIZE.width;
    if(!isStop){
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
}


void Game::stopCallback(Ref* pSender){
    isStop = true;
    TimeLineLoad::pauseTimeLine();
    auto pro = rootNodeL->getChildByName<Sprite*>("Sprite_Protagonist");
    pro->getScheduler()->setTimeScale(0.0f);
    doPasue();
    //addChild(stopNodeL);
    //target = Director::getInstance()->getScheduler()->pauseAllTargets();
    //MenuAction::move_in(stopNodeL);
}


void Game::Callrestart(Ref *pSender){
     CCLOG("pop GAME");
    if(BUTTON_LOCK==false){
        BUTTON_LOCK= true;
    //menuCloseCallback(pSender);
        Director::getInstance()->getScheduler()->resumeTargets(target);
    Director::getInstance()->getScheduler()->resumeTargets(moveaction.target_pro);
    Director::getInstance()->popScene();
    }
}

void Game::menuCloseCallback(Ref* pSender)
{
    if(BUTTON_LOCK==false){
        BUTTON_LOCK= true;
    //auto Scene =  Select_Detail::createScene();
    //auto transition=TransitionPageTurn::create(0.1f, Scene, false);
        Director::getInstance()->getScheduler()->resumeTargets(target);
        Director::getInstance()->getScheduler()->resumeTargets(moveaction.target_pro);
        
        // moveaction->target
        Director::getInstance()->popScene();
    }
    //#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
    //#endif
}

void Game::onExit(){
    
}

void Game::Callresume(Ref* pSender){
    MenuAction::move_out(stopNodeL);
    Director::getInstance()->getScheduler()->resumeTargets(target);
}



void Game::doPasue(){
    
    
//        Size visibleSize = Director::getInstance()->getVisibleSize();
//    
//        RenderTexture *renderTexture = RenderTexture::create(visibleSize.width,visibleSize.height);
//        renderTexture->begin();
//        this->getParent()->visit();
//        renderTexture->end();
    
//        Director::getInstance()->pushScene(pauseScene::createScene());
    MenuAction menuManager;
    Node* stopNode = menuManager.create_Menu(STOP_LAYER);
    rootNodeL->addChild(stopNode);
    MenuAction::move_in(stopNode);
}

void Game::toolCallback(Ref* pSender,int toolMark){
        switch(toolMark){
        case 1:{
            CCLOG("警卫数量%lu",gameload.JailerlistenerList.size());
            for(int i = 0;i<gameload.JailerlistenerList.size();i++){
                CCLOG("我设置好一个警卫啦");
                EventListenerTouchOneByOne* listener = gameload.JailerlistenerList[i];
                listener->setEnabled(true);
            }
           CCLOG("!!!!!%d",toolMark);
            break;
        }
        case 2:{
            for(int i = 0;i<gameload.WalllistenerList.size();i++){
                CCLOG("我设置好一个墙啦");
                EventListenerTouchOneByOne* listener = gameload.WalllistenerList[i];
                listener->setEnabled(true);
            }

            CCLOG("!!!!!%d",toolMark);
            break;
        }
    };
}


