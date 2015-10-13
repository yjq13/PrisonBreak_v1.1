//
//  SelectScene.cpp
//  PrisonBreak
//
//  Created by yjq131250077 on 15/9/11.
//
//

#include "SelectScene_ALL.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* Select::createScene(){
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Select::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool Select::init(){
    auto rootNodeS = CSLoader::createNode("res/Selection_1/Scene_Selection_1.csb");
    
    auto rootNodeL = CSLoader::createNode("res/Selection_1/Layer_Selection_1.csb");
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    rootNodeL->setPosition(visibleSize*1/2);
    rootNodeL->setScale(0.5);
    
    rootNodeS->addChild(rootNodeL);
    
    rootNodeS->setPosition(visibleSize*-1/2);
    
    addChild(rootNodeS);
    
    
    auto Button_New = 
    
    return true;

}

