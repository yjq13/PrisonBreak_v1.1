//
//  SelectScene.cpp
//  PrisonBreak
//
//  Created by yjq131250077 on 15/9/11.
//
//

#include "SelectScene.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

//Scene* Select::createScene()
//{
//    auto rootNode = CSLoader::createNode("MainScene.csb");
//    
//    scene->addChild(layer);
//    
//    auto button = rootNode->getChildByName<ui::Button*>("Button_1");
//    // 'scene' is an autorelease object
//    auto scene = Scene::create();
//    
//    // 'layer' is an autorelease object
//    auto layer = Start::create();
//    
//    // add layer as a child to scene
//    scene->addChild(layer);
//    
//    // return the scene
//    return scene;
//}

bool Select::init(){
        auto rootNode = CSLoader::createNode("MainScene.csb");
    
        addChild(rootNode);
    
        auto button = rootNode->getChildByName<ui::Button*>("Button_1");

}

