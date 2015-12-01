//
//  GameCommonScene.cpp
//  PrisonBreak
//
//  Created by yjq131250077 on 15/9/11.
//
//

#include "GameCommonScene.h"
#include "Sprite_protagonist.h"
#include "layerHandle.h"
#include "Move_action.h"
#include "cocostudio/CocoStudio.h"
#include "Constant_Use.h"
#include "ui/CocosGUI.h"
#include "Section.h"
#include "Sprite_jailer.h"
#include <string>
#include <iostream>


using namespace std;
USING_NS_CC;

int i = 0;
Scene* Game::createScene(){
    auto scene=Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto layer=Game::create();
    
    layer->setPhyWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    return scene;
}
bool Game::init(){

    moveAction moveaction;
    
    EventListenerPhysicsContact* contactListener = moveaction.createProAction();
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    //rootNodeS = CSLoader::createNode("res/Game/Scene_Game.csb");
    
    string hand = "res/Game/";
    string tail = ".csb";
    string all = hand+PATH_NOW+tail;
    cout<<all;
    
    rootNodeL = CSLoader::createNode(all);
    
    rootTimeLine = CSLoader::createTimeline(all);
    
    
    
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
    
    
    auto startPosition=rootNodeL->getChildByName<ui::ImageView*>("Image_Start");
    //这里应该加个异常检测，日后再说
    auto stopPosition=rootNodeL->getChildByName<ui::ImageView*>("Image_Stop");
    
    auto destinationPosition=rootNodeL->getChildByName<ui::ImageView*>("Image_Destination");
    
    auto Demo_jailer_1 = rootNodeL->getChildByName<Sprite*>("Sprite_Jailer_1");
    
    Sprite* jailer_1_get = Sprite_jailer::create(1,Demo_jailer_1);
    
    rootNodeL->addChild(jailer_1_get);
    
    rootNodeL->runAction(rootTimeLine);
    
    rootTimeLine->gotoFrameAndPlay(0, true);
    
    
    
    CCSize size_start = startPosition->getContentSize();
    Vec2 position_start = startPosition->getPosition();
    START_SECTION=Section(&size_start, &position_start);
    
    CCSize size_stop = stopPosition->getContentSize();
    Vec2 position_stop = stopPosition->getPosition();
    STOP_SECTION=Section(&size_stop, &position_stop);
    
    CCSize size_destination = destinationPosition->getContentSize();
    Vec2 position_destination = destinationPosition->getPosition();
    DESTINATION_SECTION=Section(&size_destination, &position_destination);
    
    moveListener movelistener;
    
    EventListenerTouchOneByOne* listener = movelistener.create(this,rootTimeLine);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
}

