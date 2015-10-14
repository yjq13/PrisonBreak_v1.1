//
//  SelectScene.cpp
//  PrisonBreak
//
//  Created by yjq131250077 on 15/9/11.
//
//

#include "SelectScene_ALL.h"
#include "StartScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SelectScene_Detail.h"

USING_NS_CC;
using namespace ui;

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
    if ( !Layer::init() )
    {
        return false;
    }
    printf("@@@@@@@\n");
    auto rootNodeS = CSLoader::createNode("res/Selection_1/Scene_Selection_1.csb");
    
    auto rootNodeL = CSLoader::createNode("res/Selection_1/Layer_Selection_1.csb");
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    rootNodeL->setPosition(visibleSize*1/2);
    rootNodeL->setScale(0.5);
    
    rootNodeS->addChild(rootNodeL);
    
    rootNodeS->setPosition(visibleSize*-1/2);
    
    addChild(rootNodeS);
    
    
    auto Button_Part_1 = rootNodeL->getChildByName<ui::Button*>("Button_Part_1");
    
    auto Button_Part_2 = rootNodeL->getChildByName<ui::Button*>("Button_Part_2");
    
    auto Button_Part_3 = rootNodeL->getChildByName<ui::Button*>("Button_Part_3");
    
    auto Button_Part_4 = rootNodeL->getChildByName<ui::Button*>("Button_Part_4");
    
    auto Button_Back = rootNodeL->getChildByName<ui::Button*>("Button_Back");
    
    
    Button_Part_1->addTouchEventListener(this, toucheventselector(Select::turnToSelect_2));
    
    Button_Part_2->addTouchEventListener(this, toucheventselector(Select::turnToSelect_2));
    
    Button_Part_3->addTouchEventListener(this, toucheventselector(Select::turnToSelect_2));
    
    Button_Part_4->addTouchEventListener(this, toucheventselector(Select::turnToSelect_2));
    
    Button_Back->addTouchEventListener(this, toucheventselector(Select::menuCloseCallback));
    
    
    return true;

}

void Select::menuCloseCallback(Ref* pSender)
{
    Start start;
    auto Scene=start.createScene();
    auto transition=TransitionPageTurn::create(1.5f, Scene, false);
    Director::getInstance()->replaceScene(transition);

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
//#endif
}



void Select::turnToSelect_2(Ref* pSender)
{
    Select_Detail select_detail;
    auto sceneNew= select_detail.createScene();
    //下面搞个翻页效果
    this->removeAllChildren();
    auto transition=TransitionPageTurn::create(1.5f, sceneNew, false);
    Director::getInstance()->replaceScene(transition);
}

