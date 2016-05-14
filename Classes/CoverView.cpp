//
//  CoverView.cpp
//  CocosProject
//
//  Created by 马长松 on 15/12/6.
//
//
#include "CoverView.h"
#define PI 3.14159
using namespace std;
#include "Constant_Use.h"
#include "strstream"
#include "string.h"
#include "GameVo.h"
#include "OC_callGameInfo.h"
//声音头文件及命名空间
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
CoverView::CoverView()
{
    
}

CoverView::~CoverView()
{
    CC_SAFE_RELEASE_NULL(levelArray);
}

CoverView* CoverView::create(Rect swBox, Size slSize , float disDistance , float disScale)
{
    CoverView* cover = new CoverView();
    if(cover && cover->init(swBox,slSize,disDistance,disScale))
    {
        cover->autorelease();
        return cover;
    }
    CC_SAFE_DELETE(cover);
    return NULL;
}
bool CoverView::init(Rect swBox , Size slSize , float disDistance , float disScale)
{
    if(!Node::init()) return false;
    this->swBox = swBox;
    this->swPosition = swBox.origin;
    this->swSize = swBox.size;
    this->slSize = slSize;
    this->disDistance = disDistance;
    this->disScale = disScale;
    
    Listener=EventListenerTouchOneByOne::create();
    Listener->onTouchBegan=CC_CALLBACK_2(CoverView::onTouchBegin, this);
    Listener->onTouchMoved=CC_CALLBACK_2(CoverView::onTouchMoved, this);
    Listener->onTouchEnded=CC_CALLBACK_2(CoverView::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(Listener, this);
    
    initData();
    
    scheduleUpdate();
    return true;
}
void CoverView::update(float dt){
    //调整angle数值
    if(angle>360){
        angle-=360;
    }
    if(angle<-360){
        angle+=360;
    }
    if (isHandOff&&!isShiftDone) {
        Node* card;
        bool hasValue=true;
        if(isRight&&!card_right.empty()){
            card=card_right.top();
        }else if(!isRight&&!card_left.empty()){
            card=card_left.top();
        }else{
            CCLOG("未初始化");
            hasValue=false;
        }
        if(hasValue){
            thisLevel=(Node*)levelArray->getObjectAtIndex(whichLevel+isRight);
            lastLevel=(Node*)levelArray->getObjectAtIndex(whichLevel-1+isRight);
            if(angle>=-90&&angle<=-30){
                //合于右侧
                //合并动画
                angle+=dt*100;
                card->setRotationSkewY(angle);
                thisLevel->setScaleX(-sin((-angle-30)/2*PI/180)/sin(PI/3));
                thisLevel->setRotationSkewY(-(90+(-angle-30)/2+30));
                lastLevel->setScaleX((sin((angle+150)/2*PI/180)/sin(PI/3)));
                lastLevel->setRotationSkewY(-(90-(150+angle)/2-30));
            }else if(angle>=-150&&angle<90){
                //合于左侧
                //合并动画
                angle-=dt*100;
                card->setRotationSkewY(angle);
                thisLevel->setScaleX(-sin((-angle-30)/2*PI/180)/sin(PI/3));
                thisLevel->setRotationSkewY(-(90+(-angle-30)/2+30));
                lastLevel->setScaleX((sin((angle+150)/2*PI/180)/sin(PI/3)));
                lastLevel->setRotationSkewY(-(90-(150+angle)/2-30));
            }
            if (angle>=-30) {
                isShiftDone=true;
                card->setRotationSkewY(-30);
                thisLevel->setScaleX(-0/sin(PI/3));
                thisLevel->setRotationSkewY(-(90+0/2+30));
                lastLevel->setScaleX((sin((120)/2*PI/180)/sin(PI/3)));
                lastLevel->setRotationSkewY(-(90-(120)/2-30));
                if(!isRight&&!card_left.empty()){
                    whichLevel--;
                    //左侧的书出栈一页进入右侧栈
                    CCLOG("左侧的书出栈一页进入右侧栈");
                    card_left.pop();
                    card_right.push(card);
                }
            }
            if (angle<=-150) {
                isShiftDone=true;
                card->setRotationSkewY(-150);
                thisLevel->setScaleX(-sin((150-30)/2*PI/180)/sin(PI/3));
                thisLevel->setRotationSkewY(-(90+(150-30)/2+30));
                lastLevel->setScaleX((sin((-150+150)/2*PI/180)/sin(PI/3)));
                lastLevel->setRotationSkewY(-(90-(150-150)/2-30));
                if(isRight&&!card_right.empty()){
                    whichLevel++;
                    //右侧的书出栈一页进入左侧栈
                    CCLOG("右侧的书出栈一页进入左侧栈");
                    card_right.pop();
                    card_left.push(card);
                }
            }
        }
    }
    
    
}
void CoverView::initCard(int cardNum,cocos2d::ui::Widget* card ,cocos2d::ui::Widget* start_0,cocos2d::ui::Widget* start_1,cocos2d::ui::Widget* start_2,cocos2d::ui::Widget* start_3){
    totalCard=cardNum;
    this->start_0=start_0;
    this->start_1=start_1;
    this->start_2=start_2;
    this->start_3=start_3;
    //第一关的字
    ui::TextBMFont* text_level=ui::TextBMFont::create();
    text_level->setAnchorPoint(Point(0,0));
    text_level->setString("Level_1");
    text_level->setColor(Color3B(0, 0, 0));
    text_level->setRotationSkewY(30);
    text_level->setScale(5, 5);
    text_level->setPosition(Vec2(-card->getContentSize().width*sin(PI/3), 0)+Point(offsetPosition.x,offsetPosition.y));
    addChild(text_level);
    
    //最后一关的星级
    GameVo gVO=getGameInfo(cardNum+1);
    start_0->setAnchorPoint(Vec2(1, 0));
    start_0->setPosition(Vec2(card->getContentSize().width*sin(PI/3), 0)+Point(offsetPosition.x,offsetPosition.y));
    start_0->setRotationSkewY(-30);
    start_1->setAnchorPoint(Vec2(1, 0));
    start_1->setPosition(Vec2(card->getContentSize().width*sin(PI/3), 0)+Point(offsetPosition.x,offsetPosition.y));
    start_1->setRotationSkewY(-30);
    start_2->setAnchorPoint(Vec2(1, 0));
    start_2->setPosition(Vec2(card->getContentSize().width*sin(PI/3), 0)+Point(offsetPosition.x,offsetPosition.y));
    start_2->setRotationSkewY(-30);
    start_3->setAnchorPoint(Vec2(1, 0));
    start_3->setPosition(Vec2(card->getContentSize().width*sin(PI/3), 0)+Point(offsetPosition.x,offsetPosition.y));
    start_3->setRotationSkewY(-30);
    switch (gVO._state) {
        case 0:
            CCLOG("a wodongl:%f,%f",offsetPosition.x,offsetPosition.y);
            
            addChild(start_0->clone());
            break;
        case 1:
            addChild(start_1->clone());
            break;
        case 2:
            addChild(start_2->clone());
            break;
        case 3:
            addChild(start_3->clone());
            break;
        default:
            break;
    }

    
    for(int i = 0 ; i< cardNum ; i++)
    {
        cocos2d::ui::Widget* player = card->clone();
        this->addCard(player,1000+i*10);
        
        order_left.push_back(Value(i*10));
        order_right.push_back(Value(1000+(cardNum-i-1)*10));
    }
    
}
void CoverView::initLevel(int currentLevel,cocos2d::ui::Widget* lock ){
     this->whichLevel=currentLevel-1;
    for(int i=currentLevel;i<levelNum;i++){
        cocos2d::ui::Widget* level_lock = lock->clone();
        Node* level=scrollLayer->getChildByTag(i);
        level_lock->setPosition(Vec2(level->getContentSize().width/2, level->getContentSize().height/2));
        level->addChild(level_lock);
        level->setScaleX(-0/sin(PI/3));
        level->setRotationSkewY(-(90+0/2+30));
    }
    for(int i=0;i<currentLevel-1;i++){
        Node* level=scrollLayer->getChildByTag(i);
        level->setScaleX((sin((-150+150)/2*PI/180)/sin(PI/3)));
        level->setRotationSkewY(-(90-(150-150)/2-30));
        
        Node* card=card_right.top();
        card->setRotationSkewY(-150);
        card->setZOrder(order_left.at(card_left.empty()?0:card_left.size()).asInt());
        card->getChildByTag(10)->setVisible(true);
        card->getChildByTag(20)->setVisible(false);
        card_right.pop();
        card_left.push(card);
    }
    
    scrollLayer->getChildByTag(currentLevel-1)->setLocalZOrder(10000);
    
}
void CoverView::initData()
{
    wSize = Director::getInstance()->getWinSize();
    levelArray = Array::create();
    levelArray->retain();
    cardNum = 0;
    isRight=true;
    isHandOff=true;
    isShiftDone=true;
    whichLevel=0;
    levelNum=0;
    
    SimpleAudioEngine::getInstance()->preloadEffect(M_TURNSTEP.data());
    
    
    offsetPosition = Point(swSize.width/2,swSize.height/2);
    
    scrollLayer = Layer::create();
    scrollLayer->setAnchorPoint(Point::ZERO);
    scrollLayer->setPosition(Point::ZERO);
    scrollLayer->setContentSize(slSize);
    slayerPosition = Point::ZERO;
    scrollView = ScrollView::create(swSize,scrollLayer);
    scrollView->setAnchorPoint(Point::ZERO);
    scrollView->setContentOffset(Point(0,0));
    scrollView->setTouchEnabled(false);
    addChild(scrollView,1);
}

bool CoverView::onTouchBegin(Touch* pTouch, Event* pEvent)
{
    if(isShiftDone){
        isHandOff=false;
        Point curPoint = pTouch->getLocation();
        if(curPoint.x<wSize.width/2){
            isRight=false;
            angle=-150;
        }else{
            isRight=true;
            angle=-30;
        }
        if(whichLevel+isRight>0&&whichLevel+isRight<cardNum+1){
            thisLevel=(Node*)levelArray->getObjectAtIndex(whichLevel+isRight);
            lastLevel=(Node*)levelArray->getObjectAtIndex(whichLevel-1+isRight);
            thisLevel->setPositionX(offsetPosition.x+lastLevel->getContentSize().width/2);
            thisLevel->setAnchorPoint(Point(1,0));
            thisLevel->setScaleX(!isRight);
            thisLevel->setRotationSkewY(0);
            
            lastLevel->setPositionX(offsetPosition.x-lastLevel->getContentSize().width/2);
            lastLevel->setAnchorPoint(Point(0,0));
            lastLevel->setScaleX(isRight);
            lastLevel->setRotationSkewY(0);
            return true;
        }
    }
    return false;
}

void CoverView::onTouchMoved(Touch* pTouch, Event* pEvent)
{
    Point scroll_prepoint = pTouch->getPreviousLocation();
    Point scroll_movepoint = pTouch->getLocation();
    if(swBox.containsPoint(scroll_movepoint))
    {
        Point adjustPoint = scroll_movepoint-scroll_prepoint;
        adjustCardScale(adjustPoint);
    }
}

void CoverView::onTouchEnded(Touch* pTouch, Event* pEvent)
{
    isShiftDone=false;
    isHandOff=true;
}

void CoverView::adjustCardScale(Point adjustPoint)
{
    float scale = adjustPoint.x/swSize.width*360;
    thisLevel=(Node*)levelArray->getObjectAtIndex(whichLevel+isRight);
    lastLevel=(Node*)levelArray->getObjectAtIndex(whichLevel-1+isRight);
    
    CCLOG("angle=%f",angle);
    if(isRight&&!card_right.empty()){
        Node* card = card_right.top();
        if(angle>-90&&angle+scale<=-90){
            SimpleAudioEngine::getInstance()->playEffect(M_TURNSTEP.data());
        }
        angle+=scale;
        if(angle>-90){
            card->setZOrder(order_right.at(card_right.empty()?order_right.size()-1:order_right.size()-card_right.size()).asInt());
            thisLevel->setZOrder(card->getZOrder()-1);
            lastLevel->setZOrder(card->getZOrder()+10000);
            card->getChildByTag(10)->setVisible(false);
            card->getChildByTag(20)->setVisible(true);
        }else{
            card->setZOrder(order_left.at(card_left.empty()?0:card_left.size()).asInt());
            thisLevel->setZOrder(card->getZOrder()+10000);
            lastLevel->setZOrder(card->getZOrder()-1);
            card->getChildByTag(10)->setVisible(true);
            card->getChildByTag(20)->setVisible(false);
            
        }
        //固定角度内才可以旋转
        if(angle<=-30&&angle>=-150){
            card->setRotationSkewY(angle);
            thisLevel->setScaleX(-sin((-angle-30)/2*PI/180)/sin(PI/3));
            thisLevel->setRotationSkewY(-(90+(-angle-30)/2+30));
            lastLevel->setScaleX((sin((angle+150)/2*PI/180)/sin(PI/3)));
            lastLevel->setRotationSkewY(-(90-(150+angle)/2-30));
        }
    }else if(!isRight&&!card_left.empty()){
        Node* card = card_left.top();
        if(angle<=-90&&angle+scale>-90){
            SimpleAudioEngine::getInstance()->playEffect(M_TURNSTEP.data());
        }
        angle+=scale;
        if(angle>-90){
            card->setZOrder(order_right.at(card_right.empty()?order_right.size()-1:order_right.size()-card_right.size()-1).asInt());
            
            thisLevel->setZOrder(card->getZOrder()-1);
            lastLevel->setZOrder(card->getZOrder()+10000);
            card->getChildByTag(10)->setVisible(false);
            card->getChildByTag(20)->setVisible(true);
        }else{
            card->setZOrder(order_left.at(card_left.empty()?0:card_left.size()-1).asInt());
            thisLevel->setZOrder(card->getZOrder()+10000);
            lastLevel->setZOrder(card->getZOrder()-1);
            card->getChildByTag(10)->setVisible(true);
            card->getChildByTag(20)->setVisible(false);
            
        }
        //固定角度内才可以旋转
        if(angle<=-30&&angle>=-150){
            card->setRotationSkewY(angle);
            thisLevel->setScaleX(-sin((-angle-30)/2*PI/180)/sin(PI/3));
            thisLevel->setRotationSkewY(-(90+(-angle-30)/2+30));
            lastLevel->setScaleX((sin((angle+150)/2*PI/180)/sin(PI/3)));
            lastLevel->setRotationSkewY(-(90-(150+angle)/2-30));
        }
        
    }
}
//
//
void CoverView::turnToLevel(int whichLevel)
{
    this->whichLevel=whichLevel-1;
    for (int i=0; i<whichLevel-1; i++) {
        Node* card=card_right.top();
        card_right.pop();
        card_left.push(card);
    }
    scrollLayer->getChildByTag(whichLevel-1)->setLocalZOrder(10000);
}




void CoverView::addCard(Node * card)
{
    int zOrder =0;
    this->addCard(card, zOrder, -10);
}

void CoverView::addCard(Node * card, int zOrder)
{
    this->addCard(card, zOrder,-10);
}

void CoverView::addCard(Node* card, int zOrder, int tag)
{
    float positionX = offsetPosition.x;
    //float scale = 1 - disScale*cardNum;
    card->setAnchorPoint(Point(0,0));
    card->setPosition(Point(positionX,offsetPosition.y-card->getContentSize().height));
    card->setRotationSkewY(-30);
    
    char level[20]="Level_";
    strstream ss;
    char* l;
//    ss<<10;
//    ss>>l;
    sprintf(l, "%d",totalCard-cardNum+1);
    
    strcat(level, l);
    
    ui::TextBMFont* text_level=ui::TextBMFont::create();
    text_level->setString(level);
    text_level->setColor(Color3B(0, 0, 0));
    text_level->setRotationSkewY(-180);
    text_level->setAnchorPoint(Point(0,0));
    text_level->setScale(5, 5);
    text_level->setPosition(Vec2(card->getContentSize().width, card->getContentSize().height/3));
    
    text_level->setVisible(false);
    card->addChild(text_level,0,10);
    
    //加入星级
    GameVo gVO=getGameInfo(cardNum+1);
    start_0->setAnchorPoint(Vec2(1, 0));
    start_0->setPosition(Vec2(card->getContentSize().width, card->getContentSize().height/4));
    start_0->setRotationSkewY(0);
    start_1->setAnchorPoint(Vec2(1, 0));
    start_1->setPosition(Vec2(card->getContentSize().width, card->getContentSize().height/4));
    start_1->setRotationSkewY(0);
    start_2->setAnchorPoint(Vec2(1, 0));
    start_2->setPosition(Vec2(card->getContentSize().width, card->getContentSize().height/4));
    start_2->setRotationSkewY(0);
    start_3->setAnchorPoint(Vec2(1, 0));
    start_3->setPosition(Vec2(card->getContentSize().width, card->getContentSize().height/4));
    start_3->setRotationSkewY(0);
    switch (gVO._state) {
        case 0:
            card->addChild(start_0->clone(),0,20);
            break;
        case 1:
            card->addChild(start_1->clone(),0,20);
            break;
        case 2:
            card->addChild(start_2->clone(),0,20);
            break;
        case 3:
            card->addChild(start_3->clone(),0,20);
            break;
        default:
            break;
    }
    
    //card->setScale(scale);
    scrollLayer->addChild(card , zOrder,tag);
    cardNum++;
    card_right.push(card);
    //CCLog("crad%d:[%f , %f]",cardNum,card->getPositionX(),card->getPositionY());
}

void CoverView::addLevel(Node * level)
{
    int zOrder = -1000-levelNum;
    this->addLevel(level, zOrder, levelNum++);
}

void CoverView::addLevel(Node * level, int zOrder)
{
    this->addLevel(level, zOrder,levelNum++);
}
void CoverView::addLevel(Node* level, int zOrder, int tag)
{
    float positionX = offsetPosition.x;
    //float scale = 1 - disScale*cardNum;
    
    level->setPosition(offsetPosition.x-level->getContentSize().width/2, offsetPosition.y-card_right.top()->getContentSize().width/2);
    level->setAnchorPoint(Point(0,0));
    level->setScaleX(1);
    levelArray->addObject(level);
    scrollLayer->addChild(level , zOrder,tag);
    //CCLog("crad%d:[%f , %f]",cardNum,card->getPositionX(),card->getPositionY());
}


int CoverView::getCurLevel()
{
    return whichLevel;
}

void CoverView::setOffsetPosition(Point var)
{
    //    offsetPosition = var;
    //    Ref* obj = NULL;
    //    cardNum = 0;
    //    CCARRAY_FOREACH(cardArray,obj)
    //    {
    //        Node* card = (Node*) obj;
    //        float positionX = offsetPosition.x + disDistance*cardNum;
    //        card->setPosition(Point(positionX,offsetPosition.y));
    //        cardNum++;
    //    }
    //    adjustCardScale(Point::ZERO);
}

Point CoverView::getOffsetPosition()
{
    return offsetPosition;
}