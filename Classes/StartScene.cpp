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

//声音头文件及命名空间
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

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
    
    rootNodeL = CSLoader::createNode("res/Start/Layer_Start.csb");
    initMusic();
    setUI();
    return true;
}

void Start::setUI(){

    auto button_Start = rootNodeL->getChildByName<ui::Button*>("Button_Start");
    
    button_Start->addClickEventListener(CC_CALLBACK_1(Start::turnToSelect,this));
    
    auto button_Music = rootNodeL->getChildByName<ui::Button*>("Button_Music");
    button_Music->addClickEventListener(CC_CALLBACK_1(Start::turnMusic,this));

    
    rootNodeL->setContentSize(VISIBLE_SIZE);
    
    ui::Helper::doLayout(rootNodeL);
    
    addChild(rootNodeL);
    
    SimpleAudioEngine::getInstance()->playBackgroundMusic(M_BACKGROUND_START.data(),true);

}
void Start::initMusic(){
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic(M_BACKGROUND_START.data());
    SimpleAudioEngine::getInstance()->preloadEffect(M_BUTTON_CLICK.data());

}


//点击按钮转到游戏界面
void Start::turnToSelect(Ref* pSender)
{
      SimpleAudioEngine::getInstance()->playEffect(M_BUTTON_CLICK.data());
    auto scene = Select::createScene();
    //this->removeAllChildren();
    ////下面搞个翻页效果
    //TransitionPageTurn* transition = createTransition_Page(scene);
    Director::getInstance()->replaceScene(scene);
}
void Start::turnMusic(Ref* pSender)
{
    SimpleAudioEngine::getInstance()->setEffectsVolume(SimpleAudioEngine::getInstance()->getEffectsVolume()==0?10:0);
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(SimpleAudioEngine::getInstance()->getBackgroundMusicVolume()==0?10:0);

}
