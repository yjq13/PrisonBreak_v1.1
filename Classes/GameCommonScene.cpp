//
//  GameCommonScene.cpp
//  PrisonBreak
//
//  Created by yjq131250077 on 15/9/11.
//
//

#include "GameCommonScene.h"
#include "Sprite_protagonist.h"
#include "JailerListener.h"
#include "WallListener.h"
#include "ContactManager.h"
#include "cocostudio/CocoStudio.h"
#include "Constant_Use.h"
#include "ui/CocosGUI.h"
#include "Sprite_jailer.h"
#include <string>
#include <iostream>
#include "SelectScene_Detail.h"
#include "Sprite_wall.h"
#include "MenuManager.h"
#include "SchedulerManager.h"
#include "TimeLineVo.h"
#include "OC_callGameInfo.h"
#include "CacheData.h"
#include "pauseScene.h"
#include "ListenerManager.h"
USING_NS_CC;
using namespace ui;

int i = 0;
Scene* Game::createScene(){
    auto scene=Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto layer=Game::create();
    
    
    layer->setPhyWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    scene->setTag(131250077);
    return scene;
}

Game::~Game(){
    
    CCLOG("goodbye game");

    }
void Game::draw(Renderer *renderer,const cocos2d::Mat4& transform,uint32_t flags)
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    drawLine();
}
DrawNode* a;
void Game::drawLine()
{
    int tickSubCount = 1;
    int pointListKeepCount = 1000;
    
    for (int i=0; i<tickSubCount ; i++)
    {
        if (pointList.size() >0)
        {
            pointList.pop_front();
        }
        else
        {
            break;
        }
    }
    while (pointList.size() > pointListKeepCount)
    {
        pointList.pop_front();
    }
    
    float max_lineWidth = 5;
    float min_lineWidth = 1;
    int   alpha_min = 10;
    int   alpha_max =  200;
    
    float  R = 20;//arc4random()%255;
    float  G = 255;//arc4random()%255;
    float  B = 255;//arc4random()%255;
    
    int pointListCount = pointList.size();
    std::list <CCPoint>::iterator it =pointList.begin();
    
    a->clear();
    float pointIndex = 0;
    for(;it!=pointList.end();it++)
    {
        int distanceToMiddle = fabs(pointIndex-pointListCount/2);
        float percent = 1.0-(float)distanceToMiddle/(float)(pointListCount/2.0);
        float lintWidth = min_lineWidth + max_lineWidth*percent;
        float alpha = (alpha_min +alpha_max*percent)/200;
        //Color4B(R,G,B,alpha);
//        ccDrawColor4B(R,G,B,alpha);
//        ccPointSize(lintWidth);
//        ccDrawPoint(p);
        
        Point p=*it;
        a->drawPoint(p, lintWidth, Color4F(R, G, B, alpha));
        
        pointIndex++;
    }
}

bool Game::init(){
    a=DrawNode::create();
    
    addChild(a,100);

    scheduleUpdate();

    initCacheData();
    //rootNodeS = CSLoader::createNode("res/Game/Scene_Game.csb");
    
    string hand = "res/Game/";
    string tail = ".csb";
    string follow = "/Layer_Game_Level_";
    string all = hand+PATH_PART+follow+PATH_LEVEL+tail;
    
    failNodeL = CSLoader::createNode("res/Game/Other/Layer_Fail.csb");
    successNodeL = CSLoader::createNode("res/Game/Other/Layer_Success.csb");
    stopNodeL = CSLoader::createNode("res/Game/Other/Layer_Stop.csb");
    rootNodeL = CSLoader::createNode(all);
    //failNodeL->setTag(131250077);
    rootTimeLine = CSLoader::createTimeline(all);
    
    //rootNodeL->setTag(131250081);
    
    
    GameManager::_TIMELINE = SchedulerManager::loadTimeLine(rootNodeL);
    gameload.loadGame(rootNodeL);
    
    EventListenerPhysicsContact* contactListener = moveaction.createProAction();
    
   // _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener,this);

    auto listener=EventListenerTouchOneByOne::create();
    
    listener->onTouchMoved=CC_CALLBACK_2(Game::onTouchMoved, this);
    listener->onTouchBegan=CC_CALLBACK_2(Game::onTouchBegan, this);
    listener->onTouchEnded=CC_CALLBACK_2(Game::onTouchEnded, this);
    
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
    
    setUI();

    
    return true;
}
void Game::setUI(){
    //测试在界面上放置组件
    //Size visibleSize = Director::getInstance()->getVisibleSize();
//  Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //rootNodeS->addChild(rootNodeL);
    rootNodeL->setContentSize(VISIBLE_SIZE);
    
    addChild(rootNodeL);
    
    
    auto Button_Back = rootNodeL->getChildByName<ui::Button*>("Button_Stop");
    
    Button_Back->addClickEventListener(CC_CALLBACK_1(Game::stopCallback,this));
    
    
    
    auto Button_Tool_1 = rootNodeL->getChildByName<ui::Button*>("Button_Tool_1");
    
    Button_Tool_1->addClickEventListener(CC_CALLBACK_1(Game::toolCallback,this,1));
    
    auto Button_Tool_2 = rootNodeL->getChildByName<ui::Button*>("Button_Tool_2");
    
    Button_Tool_2->addClickEventListener(CC_CALLBACK_1(Game::toolCallback,this,2));
    
    
    
    
    auto Button_Back_Fail = failNodeL->getChildByName<ui::Button*>("Button_Back");
    
    Button_Back_Fail->addTouchEventListener(CC_CALLBACK_1(Game::menuCloseCallback,this));
    
    auto Button_Back_Success = successNodeL->getChildByName<ui::Button*>("Button_Back");
    
    Button_Back_Success->addTouchEventListener(CC_CALLBACK_1(Game::menuCloseCallback,this));
    
    auto Button_Back_Stop = stopNodeL->getChildByName<ui::Button*>("Button_Back");
    
    Button_Back_Stop->addTouchEventListener(CC_CALLBACK_1(Game::menuCloseCallback,this));
    
    
    
    auto Button_Retry_Fail = failNodeL->getChildByName<ui::Button*>("Button_Retry");
    
    Button_Retry_Fail->addTouchEventListener(CC_CALLBACK_1(Game::Callrestart,this));
    
    auto Button_Retry_Success = successNodeL->getChildByName<ui::Button*>("Button_Retry");
    
    Button_Retry_Success->addTouchEventListener(CC_CALLBACK_1(Game::Callrestart,this));
    
    auto Button_Retry_Stop = stopNodeL->getChildByName<ui::Button*>("Button_Retry");
    
    Button_Retry_Stop->addTouchEventListener(CC_CALLBACK_1(Game::Callrestart,this));

    
    
    auto Button_Resume_Stop = stopNodeL->getChildByName<ui::Button*>("Button_Resume");
    
    Button_Resume_Stop->addTouchEventListener(CC_CALLBACK_1(Game::Callresume,this));
    
    //未完成部分
    auto Button_Next_Success = successNodeL->getChildByName<ui::Button*>("Button_Next");
    
    Button_Next_Success->addTouchEventListener(CC_CALLBACK_1(Game::Callrestart,this));
    
   
    
   }


void Game::update(float dt){
    auto scale=VISIBLE_SIZE.width/DESIGN_SIZE.width;
    if(!GameManager::isStop){
    //坐标重绘
    Sprite* Demo_jailer[10];
    int index = 0;
    do{
        index++;
        char number[25];
        memset(number,0,sizeof(number));
        sprintf(number,"%d",index);
        string numberStr=number;
        
        string first = "Sprite_Jailer_";
        string all = first+numberStr;
        
        Demo_jailer[index] = rootNodeL->getChildByName<Sprite*>(all);
        if(Demo_jailer[index]!=NULL){
            auto position_Before=Demo_jailer[index]->getPosition();
            Demo_jailer[index]->setPositionX(position_Before.x*scale);
        }
    }while(Demo_jailer[index]!=NULL);
    
    
    Sprite* Demo_Mouse[10];
    index = 0;
    do{
        index++;
        char number[25];
        memset(number,0,sizeof(number));
        sprintf(number,"%d",index);
        string numberStr=number;
        
        string first = "Sprite_Mouse_";
        string all = first+numberStr;
        
        Demo_Mouse[index] = rootNodeL->getChildByName<Sprite*>(all);
        if(Demo_Mouse[index]!=NULL)
        {
            auto position_Before=Demo_Mouse[index]->getPosition();
            Demo_Mouse[index]->setPositionX(position_Before.x*scale);
        }
    }while(Demo_Mouse[index]!=NULL);
    }
}


void Game::stopCallback(Ref* pSender){
    GameManager::isStop = true;
    SchedulerManager::pauseTimeLine();
    SchedulerManager::pausePro();
    doPasue();
    //addChild(stopNodeL);
    //target = Director::getInstance()->getScheduler()->pauseAllTargets();
    //MenuAction::move_in(stopNodeL);
}


void Game::Callrestart(Ref *pSender){
     CCLOG("pop GAME");
    if(BUTTON_LOCK==false){
        BUTTON_LOCK= true;
    //menuCloseCallback(pSender);
        Director::getInstance()->getScheduler()->resumeTargets(target);
    Director::getInstance()->getScheduler()->resumeTargets(moveaction.target_pro);
    Director::getInstance()->popScene();
    }
}

void Game::menuCloseCallback(Ref* pSender)
{
    if(BUTTON_LOCK==false){
        BUTTON_LOCK= true;
    //auto Scene =  Select_Detail::createScene();
    //auto transition=TransitionPageTurn::create(0.1f, Scene, false);
        Director::getInstance()->getScheduler()->resumeTargets(target);
        Director::getInstance()->getScheduler()->resumeTargets(moveaction.target_pro);
        
        // moveaction->target
        Director::getInstance()->popScene();
    }
    //#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
    //#endif
}

void Game::onExit(){
    
}

void Game::Callresume(Ref* pSender){
    MenuManager::move_out(stopNodeL);
    Director::getInstance()->getScheduler()->resumeTargets(target);
}



void Game::doPasue(){
    
    
//        Size visibleSize = Director::getInstance()->getVisibleSize();
//    
//        RenderTexture *renderTexture = RenderTexture::create(visibleSize.width,visibleSize.height);
//        renderTexture->begin();
//        this->getParent()->visit();
//        renderTexture->end();
    
//        Director::getInstance()->pushScene(pauseScene::createScene());
    MenuManager menuManager;
    Node* stopNode = menuManager.create_Menu(STOP_LAYER);
    rootNodeL->addChild(stopNode);
    MenuManager::move_in(stopNode);
}

void Game::toolCallback(Ref* pSender,int toolMark){
    switch(toolMark){
        case 1:{
            ListenerManager::addListenerJailer();
            break;
        }
        case 2:{
            ListenerManager::addListenerWall();
            CCLOG("!!!!!%d",toolMark);
            break;
        }
    };
}
bool Game::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    
    if(!moveLock){
        return false;
    }
    //CCLOG("begin with (%f,%f)",touch->getLocation().x,touch->getLocation().y);
    //画线特效
    CCPoint beginPoint = touch->getLocationInView();
    beginPoint = CCDirector::sharedDirector()->convertToGL(beginPoint);
    // beginPoint 检测
    pointList.push_back(beginPoint);
    
    index=0;
    for(int i=0;i<10000;i++){
        points[i]=Point(0,0);
    }
    
    return true;
}

void Game::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event){
    isMoved=true;
    points[index]=touch->getLocation();
    CCPoint nextPoint = touch->getLocationInView( );
    nextPoint = CCDirector::sharedDirector()->convertToGL(nextPoint);
    // nextPoint 检测
    CCPoint preMovePoint = touch->getPreviousLocationInView();
    preMovePoint = CCDirector::sharedDirector()->convertToGL(preMovePoint);
    
    float distance = ccpDistance(nextPoint, preMovePoint);
    if (distance > 1)
    {
        int d = (int)distance;
        for (int i =0; i < d; i++ )
        {
            float distanceX = nextPoint.x - preMovePoint.x;
            float distanceY = nextPoint.y - preMovePoint.y;
            
            float percent = i / distance;
            CCPoint newPoint;
            newPoint.x = preMovePoint.x + (distanceX * percent);
            newPoint.y = preMovePoint.y + (distanceY * percent);
            
            pointList.push_back(newPoint);
        }
    }
    index++;
}

void Game::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
    //CCLOG("end with (%f,%f)",touch->getLocation().x,touch->getLocation().y);
    //CCLOG("%f,%f",DESTINATION_SECTION.position->x,DESTINATION_SECTION.position->y);
    if (isMoved)
    {
        //下面是主角跟随路线移动
        //下面是填装动作的容器
        protagonist = rootNodeL->getChildByName<Sprite*>("Sprite_Protagonist");
        //CCLOG("hello moveStart!!!!");
        protagonist->setPosition(points[0]);
        
        moveLock = false;
        
        Vector<FiniteTimeAction*> actionVector;
        
        for (int i=0;i<10000;i++){
            if (i!=0&&points[i].x!=0) {
                action[i] = MoveTo::create((points[i-1]-points[i]).length()/SPEED_PRO, points[i]);
                
                //action->setTag(index);
                
                actionVector.pushBack(action[i]);
                //actionVector.pushBack(callfun);
                // protagonist->runAction(action);
            }
        }
        auto callfun = CallFunc::create([&]{
            MenuManager menuManager;
            auto layer =menuManager.create_Menu(SUCCESS_LAYER);
            protagonist->getParent()->addChild(layer);
            MenuManager::move_in(layer);
        });
        
        actionVector.pushBack(callfun);
        
        allAction=Sequence::create(actionVector);
        allAction->setTag(70000);
        protagonist->runAction(allAction);
        
    }
    
    
    
    isMoved=false;
    pointList.clear();
    
    
}



