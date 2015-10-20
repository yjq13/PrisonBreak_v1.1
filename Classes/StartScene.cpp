#include "StartScene.h"

#include "OC_callFigureInfo.h"
#include "OC_callSystemInfo.h"
#include "SelectScene_ALL.h"
#include "FigureVo.h"
#include "Constant.h"
#include "Constant_Use.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;

Scene* Start::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Start::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool Start::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    initDocuments();
    ALLINFO.setConstant();
    printf("%d\n", ALLINFO.GOLD_COIN);
    rootNodeS = CSLoader::createNode("res/Start/Scene_Start.csb");
    rootNodeL = CSLoader::createNode("res/Start/Layer_Start.csb");
    
    auto button_Start = rootNodeL->getChildByName<ui::Button*>("Button_Start");
    
    button_Start->addTouchEventListener(this, toucheventselector(Start::turnToSelect));
    
    //auto Scene = rootNodeS->getChildByName<cocos2d::Scene*>("Scene");
    
    rootNodeL->setPosition(CONSTANT_USE.VISIBLE_SIZE*1/2);
    rootNodeL->setScale(0.5);
    
    rootNodeS->addChild(rootNodeL);
    rootNodeS->setPosition(CONSTANT_USE.VISIBLE_SIZE*-1/2);
    addChild(rootNodeS);
//
    
    return true;
}


void Start::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}




//点击按钮转到游戏界面
void Start::turnToSelect(Ref* pSender)
{
    Select select;
    auto scene=select.createScene();
    
    //this->removeAllChildren();
    //下面搞个翻页效果
    TransitionPageTurn* transition = CONSTANT_USE.createTransition_Page(scene);
    Director::getInstance()->replaceScene(transition);
}
