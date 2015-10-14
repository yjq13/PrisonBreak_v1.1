#include "StartScene.h"

#include "OC_callFigureInfo.h"
#include "OC_callSystemInfo.h"
#include "SelectScene_ALL.h"
#include "FigureVo.h"
#include "Constant.h"
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
    auto rootNodeS = CSLoader::createNode("res/Start/Scene_Start.csb");
    auto rootNodeL = CSLoader::createNode("res/Start/Layer_Start.csb");
    
    
    //auto Scene = rootNodeS->getChildByName<cocos2d::Scene*>("Scene");
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    rootNodeL->setPosition(visibleSize*1/2);
    rootNodeL->setScale(0.5);
    
    rootNodeS->addChild(rootNodeL);
    rootNodeS->setPosition(visibleSize*-1/2);
    addChild(rootNodeS);
//
    auto button_Start = rootNodeL->getChildByName<ui::Button*>("Button_Start");
    
    button_Start->addTouchEventListener(this, toucheventselector(Start::turnToSelect));
    
    
//    /////////////////////////////
//    // 2. add a menu item with "X" image, which is clicked to quit the program
//    //    you may modify it.
//    
//    // add a "close" icon to exit the progress. it's an autorelease object
//    auto closeItem = MenuItemImage::create(
//                                           "CloseNormal.png",
//                                           "CloseSelected.png",
//                                           CC_CALLBACK_1(Start::menuCloseCallback, this));
//    
//    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
//                                origin.y + closeItem->getContentSize().height/2));
//    
//    // create menu, it's an autorelease object
//    auto menu = Menu::create(closeItem, NULL);
//    menu->setPosition(Vec2::ZERO);
//    this->addChild(menu, 1);
//    
//    /////////////////////////////
//    // 3. add your codes below...
//    
//    // add a label shows "Hello World"
//    // create and initialize a label
//    
//    auto label = Label::createWithTTF("Prison Break", "fonts/Marker Felt.ttf", 24);
//    
//    // position the label on the center of the screen
//    label->setPosition(Vec2(origin.x + visibleSize.width/2,
//                            origin.y + visibleSize.height - label->getContentSize().height));
//    
//    // add the label as a child to this layer
//    this->addChild(label, 1);
//    
//    // add "HelloWorld" splash screen"
//    auto sprite = Sprite::create();
//    
//    // position the sprite on the center of the screen
//    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//    
//    // add the sprite as a child to this layer
//    this->addChild(sprite, 0);
//    
    //没错下面这个就是按钮
//    auto startItem=MenuItemImage::create("01.jpg", "02.jpg", CC_CALLBACK_1(Start::turnToGame, this));
//    startItem->setPosition(Point(160, 220));
//    auto startMenu = Menu::create(startItem, NULL);
//    startMenu->setPosition(Point::ZERO);
//    this->addChild(startMenu);

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
    
    this->removeAllChildren();
    //下面搞个翻页效果
    auto transition=TransitionPageTurn::create(1.5f, scene, false);
    Director::getInstance()->replaceScene(transition);
}
