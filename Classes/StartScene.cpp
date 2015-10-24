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
    ALLINFO.setConstant();
    printf("%d\n", ALLINFO.GOLD_COIN);
    rootNodeS = CSLoader::createNode("res/Start/Scene_Start.csb");
    rootNodeL = CSLoader::createNode("res/Start/Layer_Start.csb");
    
    setUI();
    return true;
}

void Start::setUI(){
    //直接添加图片
    auto background=Sprite::create("res/P2.jpg");
    background->setScale(DESIGN_SIZE.width/background->getContentSize().width,DESIGN_SIZE.height/background->getContentSize().height);
    background->setPositionX(VISIBLE_SIZE.width/2+ORIGIN.x);
    background->setPositionY(VISIBLE_SIZE.height/2+ORIGIN.y);
    addChild(background,1);
    
    
    auto button_Start = rootNodeL->getChildByName<ui::Button*>("Button_Start");
    
    button_Start->addTouchEventListener(this, toucheventselector(Start::turnToSelect));
    
    //auto Scene = rootNodeS->getChildByName<cocos2d::Scene*>("Scene");
    
    rootNodeL->setPositionX(rootNodeL->getPositionX()+ORIGIN.x);
    rootNodeL->setScaleX(VISIBLE_SIZE.width/DESIGN_SIZE.width);
    //CCLOG("%f",VISIBLE_SIZE.width);
    rootNodeS->addChild(rootNodeL);
    addChild(rootNodeS,2);
    

}



//点击按钮转到游戏界面
void Start::turnToSelect(Ref* pSender)
{
    Select select;
    auto scene=select.createScene();
    
    //this->removeAllChildren();
    //下面搞个翻页效果
    TransitionPageTurn* transition = createTransition_Page(scene);
    Director::getInstance()->replaceScene(transition);
}
