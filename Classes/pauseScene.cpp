//
//  pauseScene.cpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 2/5/16.
//
//
#include "Constant_Use.h"
#include "pauseScene.h"
#include "MenuManager.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"


USING_NS_CC;
Scene* pauseScene::createScene() {
    
    Scene* myscene = Scene::create();
    
    auto mylayer = pauseScene::create();
    
    myscene->addChild(mylayer);
    //Node* stopNodeL = CSLoader::createNode("res/Game/Other/Layer_Stop.csb");
//    //增加部分：使用Game界面中截图的sqr纹理图片创建Sprite
//    //并将Sprite添加到GamePause场景层中
//    Sprite *_spr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
//    Size visibleSize = Director::getInstance()->getVisibleSize();
//    _spr->setPosition(Point(visibleSize.width/2,visibleSize.height/2)); //窗口大小(480,320)，这个相对于中心位置。
//    _spr->setFlipY(true);            //翻转，因为UI坐标和OpenGL坐标不同
//    //_spr->setColor(cocos2d::Color3B::GRAY); //图片颜色变灰色
//    myscene->addChild(_spr);
    //myscene->addChild(stopNodeL);
    //MenuAction::move_in(stopnode);
    //auto Button_Resume_Stop = stopNodeL->getChildByName<ui::Button*>("Button_Resume");
    
    //Button_Resume_Stop->addTouchEventListener(CC_CALLBACK_1(pauseScene::Callresume,Button_Resume_Stop));
    return myscene;
}


bool pauseScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    stopNodeL = CSLoader::createNode("res/Game/Other/Layer_Stop.csb");
    
    setUI();
    return true;
}

void pauseScene::setUI(){
    
    auto Button_Resume_Stop = stopNodeL->getChildByName<ui::Button*>("Button_Resume");
    
    Button_Resume_Stop->addTouchEventListener(CC_CALLBACK_1(pauseScene::Callresume,this));
    
    stopNodeL->setContentSize(VISIBLE_SIZE);
    
    ui::Helper::doLayout(stopNodeL);
    stopNodeL->setPositionY(VISIBLE_SIZE.height);
    
    addChild(stopNodeL);
    
    MenuManager::move_in(stopNodeL);
}



void pauseScene::Callresume(Ref* pSender){
    MenuManager::move_out(stopNodeL);
}
