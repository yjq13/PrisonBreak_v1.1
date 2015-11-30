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
#include "SelectScene_Detail.h"
#include "GameCommonScene.h"
#include "Constant_Use.h"
USING_NS_CC;
using namespace ui;

Scene* Select_Detail::createScene(){
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    
    
    auto layer = Select_Detail::create();
    
    init();
    
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
    
    printf("GGsimida");
    //rootNodeS = CSLoader::createNode("res/Selection_2/Scene_Selection_2.csb");
    
    rootNodeL_Basis = CSLoader::createNode("res/Selection_2/Layer_Selection_2.csb");
    
    rootNodeL_Diamond = CSLoader::createNode("res/Selection_2/Layer_Selection_3.csb");
    
    rootNodeL_GameStep = CSLoader::createNode("res/Selection_2/Layer_Selection_3.csb");
    
    setUI();
    
    return true;
}




void Select_Detail::setUI(){
    
    auto Button_Close   =  rootNodeL_GameStep->getChildByName<ui::Button*>("Button_Close");
    auto Button_StartGame = rootNodeL_GameStep->getChildByName<ui::Button*>("Button_StartGame");
    
    Button_Close->addTouchEventListener(this, toucheventselector(Select_Detail::closeLayer));
    
    
    Button_StartGame->addTouchEventListener(CC_CALLBACK_1(Select_Detail::turnToGame,this,"1"));
    
    //rootNodeS->addChild(rootNodeL_Diamond);
    
    rootNodeL_Diamond->setVisible(false);
    
    //rootNodeS->addChild(rootNodeL_GameStep);
    
    rootNodeL_GameStep->setVisible(false);
    
    
    //rootNodeS->addChild(rootNodeL_Basis);
    rootNodeL_Basis->setContentSize(VISIBLE_SIZE);
    ui::Helper::doLayout(rootNodeL_Basis);
    
    rootNodeL_Diamond->setContentSize(VISIBLE_SIZE);
    ui::Helper::doLayout(rootNodeL_Diamond);
    
    rootNodeL_GameStep->setContentSize(VISIBLE_SIZE);
    ui::Helper::doLayout(rootNodeL_GameStep);
    
    
    addChild(rootNodeL_Basis);
    addChild(rootNodeL_Diamond);
    addChild(rootNodeL_GameStep);
    
    
    auto Button_Back = rootNodeL_Basis->getChildByName<ui::Button*>("Button_Back");
    
    auto Button_GameStep = rootNodeL_Basis->getChildByName<ui::Button*>("Button_Level_1");
    
    
    Button_Back->addTouchEventListener(this, toucheventselector(Select_Detail::menuCloseCallback));
    
    Button_GameStep->addTouchEventListener(this, toucheventselector(Select_Detail::show_GameReady));
}



void Select_Detail::menuCloseCallback(Ref* pSender)
{
    Select select_all;
    auto Scene = select_all.createScene();
    auto transition=TransitionPageTurn::create(1.5f, Scene, false);
    Director::getInstance()->replaceScene(transition);
    
    //#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
    //#endif
}




void Select_Detail::turnToGame(Ref* pSender,string step)
{
    Game gameScene;
    if(step=="1"){
        printf("hahah,sadiao");
    }
    string follow = "/Layer_Game_Level_";
    PATH_NOW = PATH_NOW+follow+step;
    auto sceneNew = gameScene.createScene();
    //下面搞个翻页效果
    //this->removeAllChildren();
    TransitionPageTurn* transition=TransitionPageTurn::create(1.5f, sceneNew, false);
    Director::getInstance()->replaceScene(transition);
}




void Select_Detail::show_GameReady(Ref* pSender)
{
    //scene->getChildByName<cocos2d::Layer*>("layer")->getChildByName<cocos2d::Node*>("rootNodeL_GameStep")-
    //layer->getChildByName("rootNodeL_GameStep")->setVisible(true);
    //layer->
    rootNodeL_GameStep->setVisible(true);
}

void Select_Detail::closeLayer(Ref* pSender){
    //printf("hahahaha");
    rootNodeL_GameStep->setVisible(false);
}
