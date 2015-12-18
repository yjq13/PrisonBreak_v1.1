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
#include "LockofSelect.h"
#include "CoverView.h"
#include "ShopScene.h"

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
    
    //rootNodeS = CSLoader::createNode("res/Selection_2/Scene_Selection_2.csb");
    
    rootNodeL_Basis = CSLoader::createNode("res/Selection_2/Layer_Selection_2.csb");
    
    rootNodeL_Diamond = CSLoader::createNode("res/Selection_2/Layer_Selection_3.csb");
    
    rootNodeL_GameStep = CSLoader::createNode("res/Selection_2/Layer_Selection_3.csb");
    
    setUI();
    setCoverflow();
    return true;
}


void Select_Detail::setCoverflow(){
    //初始化coverflow
    float winWidth = CCDirector::sharedDirector()->getWinSize().width;
    float winHeight = CCDirector::sharedDirector()->getWinSize().height;
    
    CCRect swRect_level = CCRectMake(0.01f*winWidth,0.4f*winHeight,0.98f*winWidth,0.33f*winHeight);
    CCSize slSize_level = CCSizeMake(2.3f*winWidth,0.33f*winHeight);
    float disDistance = 0.2f*winWidth;
    float disScale = 0.25f;
    levelView = CoverView::create(swRect_level,slSize_level,disDistance,disScale);
    
    for(int i = 0 ; i< 9 ; i++)
    {
        char* url;
        url="res/Picture/Button_Part_1.png";
        Button* level=Button::create(url);
        level->addClickEventListener(CC_CALLBACK_1(Select_Detail::show_GameReady,this,i));
        levelView->addCard(level,i);
    }
    //下面这句话是调整图片位置
    //levelView->setOffsetPosition(ccp(0.1f*winWidth,swRect.size.height/2));
    levelView->setPosition(swRect_level.origin);
   this->addChild(levelView);
    
    //下面是道具的coverflow，感觉没有必要
    //    CCRect swRect_prop = CCRectMake(0.1f*winWidth,0.4f*winHeight,0.8f*winWidth,0.33f*winHeight);
    //    CCSize slSize_prop = CCSizeMake(2.3f*winWidth,0.33f*winHeight);
    //    propView = CoverView::create(swRect_prop,slSize_prop,disDistance,disScale);
    //
    //    for(int i = 0 ; i< 3 ; i++)
    //    {
    //        char* url;
    //        url="res/Picture/Button_Part_1.png";
    //        Button* prop=Button::create(url);
    //        prop->addClickEventListener(CC_CALLBACK_1(Select_Detail::chooseProp,this,i));
    //        propView->addCard(prop,i);
    //    }
    //    //下面这句话是调整图片位置
    //    //propView->setOffsetPosition(ccp(0.1f*winWidth,swRect.size.height/2));
    //    propView->setPosition(swRect_prop.origin);
    //    rootNodeL_GameStep->addChild(propView);
    
}

void Select_Detail::setUI(){
    
    auto Button_Close   =  rootNodeL_GameStep->getChildByName<ui::Button*>("Button_Close");
    auto Button_StartGame = rootNodeL_GameStep->getChildByName<ui::Button*>("Button_StartGame");
    
    Button_Close->addTouchEventListener(this, toucheventselector(Select_Detail::closeLayer));
    
    
    Button_StartGame->addTouchEventListener(CC_CALLBACK_1(Select_Detail::turnToGame,this));
    
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
    addChild(rootNodeL_GameStep,3);
    
    
    auto Button_Back = rootNodeL_Basis->getChildByName<ui::Button*>("Button_Back");
    
    // auto Button_GameStep = rootNodeL_Basis->getChildByName<ui::Button*>("Button_Level_1");
    
    
    Button_Back->addTouchEventListener(this, toucheventselector(Select_Detail::menuCloseCallback));
    
    //Button_GameStep->addTouchEventListener(CC_CALLBACK_1(Select_Detail::show_GameReady,this));
    
    auto Button_AddDiamond=rootNodeL_Basis->getChildByName<ui::Button*>("Button_AddDiamond");
    
    Button_AddDiamond->addTouchEventListener(this, toucheventselector(Select::turnToShop));
    
}



void Select_Detail::menuCloseCallback(Ref* pSender)
{
    auto Scene = Select::createScene();
    
    Director::getInstance()->replaceScene(Scene);
    
}

void Select_Detail::shieldButton(){
    auto Button_Back = rootNodeL_Basis->getChildByName<ui::Button*>("Button_Back");
    Button_Back->setEnabled(false);
}

void Select_Detail::resumeButton(){
    auto Button_Back = rootNodeL_Basis->getChildByName<ui::Button*>("Button_Back");
    Button_Back->setEnabled(true);
}


void Select_Detail::turnToGame(Ref* pSender)
{
    if(BUTTON_LOCK){
        BUTTON_LOCK=false;
        CCLOG("%d",BUTTON_LOCK);
        Game gameScene;
        
        auto sceneNew = Game::createScene();
        
        Director::getInstance()->pushScene(sceneNew);
        
    }
    
}





void Select_Detail::show_GameReady(Ref* pSender,int level)
{
    LockofSelect lock;
    bool result = lock.checkLock_outside(level);
    
    if(level!=0){
        printf("%d",level);
    }
    

    char data[25];
    memset(data,0,sizeof(data));
    sprintf(data,"%d",level+1);
    string stepSu=data;
    
    PATH_LEVEL = stepSu;

    if (result&&level==levelView->getCurCardIndex()) {
        rootNodeL_GameStep->setVisible(true);
        levelView->removeListener();
        shieldButton();
    }else{
        CCLOG("choice is wrong");
    }
}

//void Select_Detail::chooseProp(Ref* pSender,int prop_id)
//{
//    CCLOG("choose prop %d",prop_id);
//}

void Select_Detail::turnToShop(Ref* pSender){
    auto sceneNew=Shop::createScene();
    //下面搞个翻页效果
    //this->removeAllChildren();
    //auto transition=createTransition_Page(sceneNew);
    auto curScene= Director::getInstance()->getRunningScene();
    Director::getInstance()->pushScene(curScene);
    Director::getInstance()->pushScene(sceneNew);
   
}


void Select_Detail::closeLayer(Ref* pSender){
    rootNodeL_GameStep->setVisible(false);
    levelView->addListener();
    resumeButton();
}
