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
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
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
    CCSize visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto sprite1=Sprite::create("00.jpg");
    sprite1->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    auto wallBody1=PhysicsBody::createBox(sprite1->getContentSize());
    CCLOG("%f,%f",sprite1->getContentSize().width,sprite1->getContentSize().height);
    wallBody1->setGravityEnable(false);
    //    wallBody1->getShape(0)->setRestitution(1.0f);
    //    wallBody1->getShape(0)->setFriction(0.0);
    //    wallBody1->getShape(0)->setDensity(1.0);
    //    Vect force = Vect(500000.0f, 500000.0f);
    //    wallBody1->applyImpulse(force);
    wallBody1->setContactTestBitmask(0xFFFFFFFF);
    sprite1->setPhysicsBody(wallBody1);
    sprite1->setTag(1);
    this->addChild(sprite1,10);
    
    auto sprite2=Sprite::create("01.jpg");
    sprite2->setPosition(Vec2(300 , 250));
    auto wallBody2=PhysicsBody::createBox(sprite2->getContentSize());
    wallBody2->setGravityEnable(false);
    wallBody2->setContactTestBitmask(0xFFFFFFFF);
    sprite2->setPhysicsBody(wallBody2);
    sprite2->setTag(2);
    addChild(sprite2,10);
    sprite2->runAction(MoveTo::create(2, Vec2(400, 400)));
    
    Sprite* edgeSpace=Sprite::create();
    PhysicsBody* boundBody=PhysicsBody::createEdgeBox(visibleSize,PHYSICSBODY_MATERIAL_DEFAULT,3);
    boundBody->getShape(0)->setFriction(0.0f);
    boundBody->getShape(0)->setRestitution(1.0f);
    
    edgeSpace->setPhysicsBody(boundBody);
    edgeSpace->setPosition(CCPoint(visibleSize.width/2,visibleSize.height/2));
    addChild(edgeSpace);
    edgeSpace->setTag(0);
    auto button_Start = rootNodeL->getChildByName<ui::Button*>("Button_Start");
    
    button_Start->addTouchEventListener(this, toucheventselector(Start::turnToSelect));
    rootNodeL->setContentSize(VISIBLE_SIZE);
    ui::Helper::doLayout(rootNodeL);
    addChild(rootNodeL);
    

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
