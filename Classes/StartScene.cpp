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
    CONSTANT_USE.init();
    initDocuments();
    ALLINFO.setConstant();
    printf("%d\n", ALLINFO.GOLD_COIN);
    rootNodeS = CSLoader::createNode("res/Start/Scene_Start.csb");
    rootNodeL = CSLoader::createNode("res/Start/Layer_Start.csb");
    
    setUI();
    return true;
}

void Start::setUI(){
    auto button_Start = rootNodeL->getChildByName<ui::Button*>("Button_Start");
    
    button_Start->addTouchEventListener(this, toucheventselector(Start::turnToSelect));
    
    //auto Scene = rootNodeS->getChildByName<cocos2d::Scene*>("Scene");
    
    rootNodeL->setPositionX(rootNodeL->getPositionX()+CONSTANT_USE.ORIGIN.x);
    rootNodeL->setScaleX(CONSTANT_USE.VISIBLE_SIZE.width/CONSTANT_USE.DESIGN_SIZE.width);
    CCLOG("%f",CONSTANT_USE.VISIBLE_SIZE.width);
    rootNodeS->addChild(rootNodeL);
    addChild(rootNodeS);
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
