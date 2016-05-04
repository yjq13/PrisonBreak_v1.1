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
#include "Constant.h"
#include "LockofSelect.h"
#include "CoverView.h"
#include "ShopScene.h"
#include "MenuManager.h"
#include "MusicManager.h"
#include "OC_callGameInfo.h"
#include "GameVo.h"
#include <strstream>

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
    
    rootNodeL_GameStep = CSLoader::createNode("res/Selection_2/Layer_Selection_3.csb");
    
    
    setUI();
    setCoverflow();
    return true;
}


void Select_Detail::setCoverflow(){
    //初始化coverflow
    float winWidth = Director::getInstance()->getWinSize().width;
    float winHeight = Director::getInstance()->getWinSize().height;
    
    Rect swRect_level = Rect::Rect(0.01f*winWidth,0.0f*winHeight,0.98f*winWidth,1.0f*winHeight);
    Size slSize_level = Size::Size(2.3f*winWidth,1.0f*winHeight);
    float disDistance = 0.1f*winWidth;
    float disScale = 0.25f;
    levelView = CoverView::create(swRect_level,slSize_level,disDistance,disScale);
    
    levelView->initCard(9,rootNodeL_Basis->getChildByName<Widget*>("Page"));
    
    
    Widget* step=rootNodeL_Basis->getChildByName<Widget*>("Step");
    
    
    for(int i = 0 ; i< 10 ; i++)
    {
        Widget* a=step->clone();
        a->addClickEventListener(CC_CALLBACK_1(Select_Detail::show_GameReady,this,i));
        levelView->addLevel(a);
    }
    //跳关、加锁
    levelView->initLevel(STEP, rootNodeL_Basis->getChildByName<Widget*>("Lock"));
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
    
    Button_Close->addTouchEventListener(CC_CALLBACK_1(Select_Detail::closeLayer,this));
    
    
    Button_StartGame->addTouchEventListener(CC_CALLBACK_1(Select_Detail::turnToGame,this));
    
    auto button_MusicOn = rootNodeL_Basis->getChildByName<ui::Widget*>("Button_MusicOn");
    auto button_MusicOff = rootNodeL_Basis->getChildByName<ui::Widget*>("Button_MusicOff");
    
    MUSICMANAGER->init(button_MusicOn, button_MusicOff);
    
    button_MusicOn->addClickEventListener(CC_CALLBACK_1(MusicManager::turnMusicOn,MUSICMANAGER));
    button_MusicOff->addClickEventListener(CC_CALLBACK_1(MusicManager::turnMusicOff,MUSICMANAGER));
    

    
    //rootNodeS->addChild(rootNodeL_Diamond);
    
    //rootNodeS->addChild(rootNodeL_GameStep);
    
    //rootNodeL_GameStep->setVisible(false);
    
    
    //rootNodeS->addChild(rootNodeL_Basis);
    rootNodeL_Basis->setContentSize(VISIBLE_SIZE);
    ui::Helper::doLayout(rootNodeL_Basis);
    
    
    rootNodeL_GameStep->setContentSize(VISIBLE_SIZE);
    ui::Helper::doLayout(rootNodeL_GameStep);
    rootNodeL_GameStep->setPositionY(VISIBLE_SIZE.height);
    
    
    addChild(rootNodeL_Basis);
    addChild(rootNodeL_GameStep,3);
    
    
    auto Button_Back = rootNodeL_Basis->getChildByName<ui::Button*>("Button_Back");
    
    // auto Button_GameStep = rootNodeL_Basis->getChildByName<ui::Button*>("Button_Level_1");
    
    
    Button_Back->addTouchEventListener(CC_CALLBACK_1(Select_Detail::menuCloseCallback,this));
    
    //Button_GameStep->addTouchEventListener(CC_CALLBACK_1(Select_Detail::show_GameReady,this));
    
    auto Button_AddDiamond=rootNodeL_Basis->getChildByName<ui::Button*>("Button_AddDiamond");
    
    Button_AddDiamond->addTouchEventListener(CC_CALLBACK_1(Select_Detail::turnToShop,this));
    
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
        //CCLOG("%d",BUTTON_LOCK);
        
        //Game gameScene;
        
        auto sceneNew = Game::createScene();
        
        Director::getInstance()->pushScene(sceneNew);
        //rootNodeL_GameStep->setVisible(false);
        rootNodeL_GameStep->setPositionY(VISIBLE_SIZE.height);
        //levelView->addListener();
        resumeButton();
    }
    
}





void Select_Detail::show_GameReady(Ref* pSender,int level)
{
    LockofSelect lock;
    bool result = lock.checkLock_outside(level+1);
    
    char data[25];
    memset(data,0,sizeof(data));
    sprintf(data,"%d",level+1);
    string stepSu=data;
    
    PATH_LEVEL = stepSu;
    //CCLOG("asasd%d  %d",level,levelView->getCurCardIndex());
    bool iscur=false;//是否未滑动
    if(level+1==STEP){
        //999999表示未滑动，即选择当前关
        iscur=true;
    }
    CCLOG("step:%d,level:%d,view:%d",STEP,level,levelView->getCurLevel());
    if (result&&(level==levelView->getCurLevel()||iscur)) {
        CCLOG("第%d关",level+1);
        GameManager::stepNow = level+1;
        GameVo gVO=getGameInfo(level+1);
        //Menu Movein
        auto text_score=rootNodeL_GameStep->getChildByName<ui::TextBMFont*>("Text_Score");
        strstream ss;
        ss<<gVO._score;
        string score;
        ss>>score;
        text_score->setString(score);
        MenuManager::move_in(rootNodeL_GameStep);
        //rootNodeL_GameStep->setVisible(true);
        //levelView->removeListener();
        shieldButton();
    }else {
        
        CCLOG("choice is wrong");
    }
}

//void Select_Detail::chooseProp(Ref* pSender,int prop_id)
//{
//    CCLOG("choose prop %d",prop_id);
//}

void Select_Detail::turnToShop(Ref* pSender){
    auto sceneNew=Shop::createScene();
    auto curScene= Director::getInstance()->getRunningScene();
    Director::getInstance()->pushScene(curScene);
    Director::getInstance()->pushScene(sceneNew);
    
}


void Select_Detail::closeLayer(Ref* pSender){
    //rootNodeL_GameStep->setVisible(false);
    MenuManager::move_out(rootNodeL_GameStep);
    resumeButton();
}
