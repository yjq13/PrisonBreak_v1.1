//
//  GameCommonScene.cpp
//  PrisonBreak
//
//  Created by yjq131250077 on 15/9/11.
//
//

#include "GameCommonScene.h"
#include "Sprite_protagonist.h"
#include "MoveListener.h"
#include "Move_action.h"
#include "cocostudio/CocoStudio.h"
#include "Constant_Use.h"
#include "ui/CocosGUI.h"
#include "Section.h"
USING_NS_CC;

Scene* Game :: createScene(){
    auto scene=Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto layer=Game::create();
    layer->setPhyWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    return scene;
}
bool Game::init(){
    if(!Layer::init()){
        return false;
    }

    moveAction moveaction;
    
    EventListenerPhysicsContact* contactListener = moveaction.createPro_Jailer();
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    //rootNodeS = CSLoader::createNode("res/Game/Scene_Game.csb");
    
    rootNodeL = CSLoader::createNode("res/Game/Layer_Game.csb");
    
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
    Size size_start = startPosition->getContentSize();
    Vec2 position_start = startPosition->getPosition();
    startSection=Section(&size_start, &position_start);
    
    Size size_stop = stopPosition->getContentSize();
    Vec2 position_stop = stopPosition->getPosition();
    stopSection=Section(&size_stop, &position_stop);
    
    Size size_destination = destinationPosition->getContentSize();
    Vec2 position_destination = destinationPosition->getPosition();
    destinationSection=Section(&size_destination, &position_destination);
    
    moveListener movelistener;
    
    EventListenerTouchOneByOne* listener = movelistener.create(this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
}
