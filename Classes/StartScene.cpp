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
    VISIBLE_SIZE = cocos2d::Director::getInstance()->getVisibleSize();
    
    ORIGIN = cocos2d::Director::getInstance()->getVisibleOrigin();
    
    initDocuments();
    
    setConstant();
    
    printf("%d\n", GOLD_COIN);
    
    rootNodeL = CSLoader::createNode("res/Start/Layer_Start.csb");
    
    setUI();
    return true;
}

void Start::setUI(){

    auto button_Start = rootNodeL->getChildByName<ui::Button*>("Button_Start");
    
    button_Start->addTouchEventListener(this, toucheventselector(Start::turnToSelect));
    
    rootNodeL->setContentSize(VISIBLE_SIZE);
    
    ui::Helper::doLayout(rootNodeL);
    
    addChild(rootNodeL);
    

}



//点击按钮转到游戏界面
void Start::turnToSelect(Ref* pSender)
{
    
    auto scene = Select::createScene();
    //this->removeAllChildren();
    ////下面搞个翻页效果
    //TransitionPageTurn* transition = createTransition_Page(scene);
    Director::getInstance()->replaceScene(scene);
}
