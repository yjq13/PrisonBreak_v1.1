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
USING_NS_CC;
using namespace ui;

int i = 0;
Scene* Game::createScene(){
    auto scene=Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto layer=Game::create();
    
    layer->setPhyWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    return scene;
}

Game::~Game(){
    
    CCLOG("HELLOGAME");

    }
bool Game::init(){

    
    
    //rootNodeS = CSLoader::createNode("res/Game/Scene_Game.csb");
    
    string hand = "res/Game/";
    string tail = ".csb";
    string follow = "/Layer_Game_Level_";
    string all = hand+PATH_PART+follow+PATH_LEVEL+tail;
    
    rootNodeL = CSLoader::createNode(all);
    
    rootTimeLine = CSLoader::createTimeline(all);
    
    
    TIMELINE timeline = TimeLineLoad::loadTimeLine(rootNodeL);

    
    EventListenerPhysicsContact* contactListener = moveaction.createProAction(timeline);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    EventListenerTouchOneByOne* listener = movelistener.create(rootNodeL);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, rootNodeL);
    
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
    addChild(rootNodeL);
    auto Button_Back = rootNodeL->getChildByName<ui::Button*>("Button_Back");
    
    
    Button_Back->addTouchEventListener(this,toucheventselector(Game::menuCloseCallback));
    
    
    
    gameLoad::loadGame(rootNodeL);
    
    
    
   }


void Game::menuCloseCallback(Ref* pSender)
{
    BUTTON_LOCK = true;
    auto Scene =  Select_Detail::createScene();
    //auto transition=TransitionPageTurn::create(0.1f, Scene, false);
    
    Director::getInstance()->replaceScene(Scene);
    
    //#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
    //#endif
}

