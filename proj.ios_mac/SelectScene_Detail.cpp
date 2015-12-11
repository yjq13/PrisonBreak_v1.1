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
    
    return true;
}




void Select_Detail::setUI(){
    
    auto Button_Close   =  rootNodeL_GameStep->getChildByName<ui::Button*>("Button_Close");
    auto Button_StartGame = rootNodeL_GameStep->getChildByName<ui::Button*>("Button_StartGame");
    
    Button_Close->addTouchEventListener(this, toucheventselector(Select_Detail::closeLayer));
    
    
    Button_StartGame->addTouchEventListener(CC_CALLBACK_1(Select_Detail::turnToGame,this,1));
    
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
    
    Button_GameStep->addTouchEventListener(CC_CALLBACK_1(Select_Detail::show_GameReady,this));
    
    
    //coverflow
    float winWidth = CCDirector::sharedDirector()->getWinSize().width;
    float winHeight = CCDirector::sharedDirector()->getWinSize().height;
    
    CCRect swRect = CCRectMake(0.01f*winWidth,0.4f*winHeight,0.98f*winWidth,0.33f*winHeight);
    CCSize slSize = CCSizeMake(2.3f*winWidth,0.33f*winHeight);
    float disDistance = 0.2f*winWidth;
    float disScale = 0.25f;
    CoverView* coverView = CoverView::create(swRect,slSize,disDistance,disScale);
    for(int i = 0 ; i< 6 ; i++)
    {
        char* url;
        switch (i) {
            case 0:
                url="00.jpg";
                break;
            case 1:
                url="01.jpg";
                break;
            case 2:
                url="02.jpg";
                break;
            case 3:
                url="03.jpg";
                break;
            case 4:
                url="04.jpg";
                break;
            case 5:
                url="05.jpg";
                break;
                
                
            default:
                url="";
                break;
        }
        Sprite* player = Sprite::create(url);
        coverView->addCard(player);
    }
    //coverflow1.png默认第一张在coverView的正中间  coverflow2.png改变第一张的位置有卡片初始不一定在最中间 需要手动调整
    //coverView->setOffsetPosition(ccp(0.1f*winWidth,swRect.size.height/2));
    coverView->setPosition(swRect.origin);
    addChild(coverView);
}



void Select_Detail::menuCloseCallback(Ref* pSender)
{
    auto Scene = Select::createScene();
    
    Director::getInstance()->replaceScene(Scene);

}




void Select_Detail::turnToGame(Ref* pSender,int step)
{
    if(BUTTON_LOCK){
        BUTTON_LOCK=false;
        CCLOG("%d",BUTTON_LOCK);
    Game gameScene;
    LockofSelect lock;
    bool result = lock.checkLock_outside(step);

    if(step==1){
        printf("hahah,sadiao\n");
    }
    
    
    char data[25];
    memset(data,0,sizeof(data));
    sprintf(data,"%d",step);
    string stepSu=data;
    
        PATH_LEVEL = stepSu;
    
        auto sceneNew = Game::createScene();

    Director::getInstance()->pushScene(sceneNew);
        
        }
    
}




void Select_Detail::show_GameReady(Ref* pSender)
{
    rootNodeL_GameStep->setVisible(true);
}

void Select_Detail::closeLayer(Ref* pSender){
    rootNodeL_GameStep->setVisible(false);
}
