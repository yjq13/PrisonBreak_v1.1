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
void CoverView::initCard(int cardNum,cocos2d::ui::Widget* card ){
    for(int i = 0 ; i< cardNum ; i++)
    {cocos2d::ui::Widget* player = card->clone();
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
        level->setScaleX((sin((120)/2*PI/180)/sin(PI/3)));
        level->setRotationSkewY(-(90-(120)/2-30));
        
        Node* card=card_right.top();
        card->setRotationSkewY(-150);
        card->setZOrder(order_left.at(card_left.empty()?0:card_left.size()).asInt());
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
    if(isRight&&!card_right.empty()){
        Node* card = card_right.top();
        angle+=scale;
        //固定角度内才可以旋转
        if(angle<=-30&&angle>=-150){
            card->setRotationSkewY(angle);
            if(angle>-90){
                card->setZOrder(order_right.at(card_right.empty()?order_right.size()-1:order_right.size()-card_right.size()).asInt());
                thisLevel->setZOrder(card->getZOrder()-1);
                lastLevel->setZOrder(card->getZOrder()+10000);
            }else{
                SimpleAudioEngine::getInstance()->playEffect(M_TURNSTEP.data());
                card->setZOrder(order_left.at(card_left.empty()?0:card_left.size()).asInt());
                thisLevel->setZOrder(card->getZOrder()+10000);
                lastLevel->setZOrder(card->getZOrder()-1);
                
            }
            thisLevel->setScaleX(-sin((-angle-30)/2*PI/180)/sin(PI/3));
            thisLevel->setRotationSkewY(-(90+(-angle-30)/2+30));
            lastLevel->setScaleX((sin((angle+150)/2*PI/180)/sin(PI/3)));
            lastLevel->setRotationSkewY(-(90-(150+angle)/2-30));
        }
    }else if(!isRight&&!card_left.empty()){
        Node* card = card_left.top();
        angle+=scale;
        //固定角度内才可以旋转
        if(angle<=-30&&angle>=-150){
            card->setRotationSkewY(angle);
            if(angle>-90){
                SimpleAudioEngine::getInstance()->playEffect(M_TURNSTEP.data());
                card->setZOrder(order_right.at(card_right.empty()?order_right.size()-1:order_right.size()-card_right.size()-1).asInt());
                
                thisLevel->setZOrder(card->getZOrder()-1);
                lastLevel->setZOrder(card->getZOrder()+10000);
            }else{
                card->setZOrder(order_left.at(card_left.empty()?0:card_left.size()-1).asInt());
                thisLevel->setZOrder(card->getZOrder()+10000);
                lastLevel->setZOrder(card->getZOrder()-1);
                
            }
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