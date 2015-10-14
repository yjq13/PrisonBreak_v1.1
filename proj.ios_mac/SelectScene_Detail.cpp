//
//  SelectScene_2.cpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 10/14/15.
//
//

#include "SelectScene_Detail.h"
#include "SelectScene_ALL.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SelectScene_2.h"

USING_NS_CC;
using namespace ui;

Scene* Select_Detail::createScene(){
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Select_Detail::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
   
    // return the scene

    return scene;
}

bool Select_Detail::init(){
    if ( !Layer::init() )
    {
        return false;
    }
    auto rootNodeS = CSLoader::createNode("res/Selection_2/Scene_Selection_2.csb");
    
    auto rootNodeL = CSLoader::createNode("res/Selection_2/Layer_Selection_2.csb");
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    rootNodeL->setPosition(visibleSize*1/2);
    rootNodeL->setScale(0.5);
    
    rootNodeS->addChild(rootNodeL);
    
    rootNodeS->setPosition(visibleSize*-1/2);
    
    addChild(rootNodeS);
    return true;
}