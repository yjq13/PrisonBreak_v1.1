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
#include "SpriteManager.h"
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
    debugInt+=1000;
    CCLOG("goodbye game%d",debugInt);

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
    
    float  R = 255;//arc4random()%255;
    float  G = 255;//arc4random()%255;
    float  B = 255;//arc4random()%255;
    
    int pointListCount =(int) pointList.size();
    std::list <Point>::iterator it =pointList.begin();
    
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
    debugInt++;
    CCLOG("init被调用过了%d",debugInt);
    a=DrawNode::create();
    
    addChild(a,100);

    scheduleUpdate();

    initCacheData();
    //rootNodeS = CSLoader::createNode("res/Game/Scene_Game.csb");
    GameManager::stepOfGame=3;
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
    
    ui::Helper::doLayout(rootNodeL);
    
    addChild(rootNodeL);
    
    
    auto Button_Back = rootNodeL->getChildByName<ui::Button*>("Button_Stop");
    
    Button_Back->addClickEventListener(CC_CALLBACK_1(Game::stopCallback,this));
    
    
    
    auto Button_Tool_1 = rootNodeL->getChildByName<ui::Button*>("Button_Tool_1");
    
    Button_Tool_1->addClickEventListener(CC_CALLBACK_1(Game::toolCallback,this,1));
    
    auto Button_Tool_2 = rootNodeL->getChildByName<ui::Button*>("Button_Tool_2");
    
    Button_Tool_2->addClickEventListener(CC_CALLBACK_1(Game::toolCallback,this,2));
    
    
    
    
      }


void Game::update(float dt){
    auto scale=VISIBLE_SIZE.width/DESIGN_SIZE.width;

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
        if((Demo_jailer[index]!=NULL)){
            if(!SpriteManager::getJailerByTag(Demo_jailer[index]->getTag())->getIsStop()){
                auto position_Before=Demo_jailer[index]->getPosition();
                Demo_jailer[index]->setPositionX(position_Before.x*scale);
            }
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
    CCLOG("我退出了");

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
    
    if((!GameManager::isTouchPro)||isMoved){
        return false;
    }
    //CCLOG("begin with (%f,%f)",touch->getLocation().x,touch->getLocation().y);
    //画线特效
    Point beginPoint = touch->getLocationInView();
    beginPoint = Director::getInstance()->convertToGL(beginPoint);
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
    CCLOG("添加point：(%f,%f)",points[index].x,points[index].y);
    Point nextPoint = touch->getLocationInView( );
    nextPoint = Director::getInstance()->convertToGL(nextPoint);
    // nextPoint 检测
    Point preMovePoint = touch->getPreviousLocationInView();
    preMovePoint = Director::getInstance()->convertToGL(preMovePoint);
    
    float distance = nextPoint.getDistance(preMovePoint);
    if (distance > 1)
    {
        int d = (int)distance;
        for (int i =0; i < d; i++ )
        {
            float distanceX = nextPoint.x - preMovePoint.x;
            float distanceY = nextPoint.y - preMovePoint.y;
            
            float percent = i / distance;
            Point newPoint;
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
        
        GameManager::isTouchPro = false;
        
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
            GameManager::stepOfGame--;
            if(GameManager::stepOfGame == 0){
            MenuManager::move_in(layer);
                
            }
        });
        
        actionVector.pushBack(callfun);
        
        allAction=Sequence::create(actionVector);
        allAction->setTag(70000);
        protagonist->runAction(allAction);
        
    }
    
    isMoved=false;
    pointList.clear();
    
    
}




