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
#include "ShopScene.h"
#include "Constant_Use.h"
#include "LockofSelect.h"
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
    
    //rootNodeS = CSLoader::createNode("res/Selection_1/Scene_Selection_1.csb");
    
    rootNodeL = CSLoader::createNode("res/Selection_1/Layer_Selection_1.csb");
    
    setUI();
    
    
    return true;

}


void Select::setUI(){
//    rootNodeL->setPositionX(rootNodeL->getPositionX()+ORIGIN.x);
//    rootNodeL->setScaleX(VISIBLE_SIZE.width/DESIGN_SIZE.width);
//    CCLOG("%f",VISIBLE_SIZE.width);
    //rootNodeS->addChild(rootNodeL);
    rootNodeL->setContentSize(VISIBLE_SIZE);
    ui::Helper::doLayout(rootNodeL);
    addChild(rootNodeL);
    
    
    auto Button_Part_1 = rootNodeL->getChildByName<ui::Button*>("Button_Part_1");
    
    auto Button_Part_2 = rootNodeL->getChildByName<ui::Button*>("Button_Part_2");
    
    auto Button_Part_3 = rootNodeL->getChildByName<ui::Button*>("Button_Part_3");
    
    auto Button_Part_4 = rootNodeL->getChildByName<ui::Button*>("Button_Part_4");
    
    auto Button_Back = rootNodeL->getChildByName<ui::Button*>("Button_Back");
    
    auto Button_AddDiamond=rootNodeL->getChildByName<ui::Button*>("Button_AddDiamond");
    
    auto Diamond_Num = rootNodeL->getChildByName<ui::Text*>("Text_DiamondNum");
    
    char number[2];
    memset(number,0,sizeof(number));
    sprintf(number,"%d",DIAMOND);
    string numberStr=number;
    Diamond_Num->setString(numberStr);
    
    auto Gold_Num = rootNodeL->getChildByName<ui::Text*>("Text_GoldNum");
    
    memset(number,0,sizeof(number));
    sprintf(number,"%d",GOLD_COIN);
    numberStr=number;
    
    Gold_Num->setString(numberStr);
    
    Button_Part_1->addClickEventListener(CC_CALLBACK_1(Select::turnToSelect_Detail,this,1));
    
    Button_Part_2->addClickEventListener(CC_CALLBACK_1(Select::turnToSelect_Detail,this,2));
    
    Button_Part_3->addClickEventListener(CC_CALLBACK_1(Select::turnToSelect_Detail,this,3));
    
    Button_Part_4->addClickEventListener(CC_CALLBACK_1(Select::turnToSelect_Detail,this,4));
    
    Button_Back->addClickEventListener(CC_CALLBACK_1(Select::menuCloseCallback,this));
    
    Button_AddDiamond->addClickEventListener(CC_CALLBACK_1(Select::turnToShop,this));

}


void Select::menuCloseCallback(Ref* pSender)
{

    //auto transition=createTransition_Page(Scene);
    Director::getInstance()->popScene();
    
}






void Select::turnToSelect_Detail(Ref* pSender,int number)
{
    
    LockofSelect lock;
    bool result = lock.checkLock_outside(number);
    if(result){
        switch(number){
            case 1:{
                PATH_PART = "Part_1";
                break;
            }
            case 2:{
                PATH_PART = "Part_2";
                break;
            }
            case 3:{
                PATH_PART = "Part_3";
                break;
            }
            case 4:{
                PATH_PART = "Part_4";
                break;
            }

                
        }
        
        auto sceneNew= Select_Detail::createScene();
        
        //下面搞个翻页效果
        //this->removeAllChildren();
        //auto transition=createTransition_Page(sceneNew);
        Director::getInstance()->replaceScene(sceneNew);
        
    }else{
        CCLOG("这个大关未开启！！");
    }
}

void Select::turnToShop(Ref* pSender){
    auto sceneNew=Shop::createScene();
    //下面搞个翻页效果
    //this->removeAllChildren();
    //auto transition=createTransition_Page(sceneNew);
    
    Director::getInstance()->pushScene(this->getScene());
    Director::getInstance()->pushScene(sceneNew);
}