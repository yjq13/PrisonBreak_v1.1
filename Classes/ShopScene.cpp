//
//  AnimationScene.cpp
//  PrisonBreak
//
//  Created by yjq131250077 on 15/9/11.
//
//

#include "OC_callFigureInfo.h"
#include "OC_callSystemInfo.h"
#include "FigureVo.h"
#include "Constant.h"
#include "Constant_Use.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;
#include "ShopScene.h"
Scene* Shop::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Shop::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool Shop::init(){
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    rootNodeL = CSLoader::createNode("res/DiamondShop/Layer_DiamondShop.csb");
    setUI();
    return true;
}

void Shop::setUI(){
    rootNodeL->setContentSize(VISIBLE_SIZE);
    ui::Helper::doLayout(rootNodeL);
    addChild(rootNodeL);
    
    auto Button_fewDiamonds=rootNodeL->getChildByName<ui::Button*>("Button_fewDiamonds");
    auto Button_someDiamonds=rootNodeL->getChildByName<ui::Button*>("Button_someDiamonds");
    auto Button_manyDiamonds=rootNodeL->getChildByName<ui::Button*>("Button_manyDiamonds");
    
    Button_fewDiamonds->addClickEventListener(CC_CALLBACK_1(Shop::buyfew, this));
     Button_fewDiamonds->addClickEventListener(CC_CALLBACK_1(Shop::buysome, this));
     Button_fewDiamonds->addClickEventListener(CC_CALLBACK_1(Shop::buymany, this));
    
    
    auto Button_Back=rootNodeL->getChildByName<ui::Button*>("Button_Back");
     Button_Back->addClickEventListener(CC_CALLBACK_1(Shop::menuCloseCallback, this));
    
    
    
}


void Shop::menuCloseCallback(cocos2d::Ref *pSender){
    Director::getInstance()->popScene();
    
}

bool Shop::buyfew(cocos2d::Ref *pSender){
    return true;
}
bool Shop::buysome(cocos2d::Ref *pSender){
    return true;
}
bool Shop::buymany(cocos2d::Ref *pSender){
    return true;
}