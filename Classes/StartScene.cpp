#include "StartScene.h"

#include "OC_callFigureInfo.h"
#include "OC_callSystemInfo.h"
#include "GameCommonScene.h"
#include "FigureVo.h"
#include "Constant.h"

USING_NS_CC;

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
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(Start::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Prison Break", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create();
    
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    //没错下面这个就是按钮
    auto startItem=MenuItemImage::create("01.jpg", "02.jpg", CC_CALLBACK_1(Start::turnToGame, this));
    startItem->setPosition(Point(160, 220));
    auto starMenu = Menu::create(startItem, NULL);
    starMenu->setPosition(Point::ZERO);
    this->addChild(starMenu, 1);
    
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
void Start::turnToGame(Ref* pSender)
{
    auto scene=Game::createScene();
    //下面搞个翻页效果
    auto transition=TransitionPageTurn::create(1.5f, scene, false);
    Director::getInstance()->replaceScene(transition);
}
