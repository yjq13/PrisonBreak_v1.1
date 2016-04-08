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
                    thisLevel->setZOrder(-1000);
                    //左侧的书出栈一页进入右侧栈
                    CCLOG("左侧的书出栈一页进入右侧栈");
                    card->setZOrder(0);
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
                    lastLevel->setZOrder(-1000);
                    //右侧的书出栈一页进入左侧栈
                    CCLOG("右侧的书出栈一页进入左侧栈");
                    card->setZOrder(0);
                    card_right.pop();
                    card_left.push(card);
                }
            }
        }
    }
    
    
}
void CoverView::initCard(int cardNum){
    char* url="白色方块.png";
    
    for(int i = 0 ; i< cardNum ; i++)
    {Sprite* player = Sprite::create(url);
        this->addCard(player);
    }
    
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
            thisLevel->setPosition(offsetPosition.x+170, offsetPosition.y-200);
            thisLevel->setAnchorPoint(Point(1,0));
            thisLevel->setScaleX(!isRight);
            thisLevel->setRotationSkewY(0);
            
            lastLevel->setPosition(offsetPosition.x-170, offsetPosition.y-200);
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
        card->setZOrder(1000);
        angle+=scale;
        //固定角度内才可以旋转
        if(angle<=-30&&angle>=-150){
            card->setRotationSkewY(angle);
            if(angle>-90){
                thisLevel->setZOrder(500);
                lastLevel->setZOrder(2000);
            }else{
                thisLevel->setZOrder(2000);
                lastLevel->setZOrder(500);
                
            }
            thisLevel->setScaleX(-sin((-angle-30)/2*PI/180)/sin(PI/3));
            thisLevel->setRotationSkewY(-(90+(-angle-30)/2+30));
            lastLevel->setScaleX((sin((angle+150)/2*PI/180)/sin(PI/3)));
            lastLevel->setRotationSkewY(-(90-(150+angle)/2-30));
        }
    }else if(!isRight&&!card_left.empty()){
        Node* card = card_left.top();
        card->setZOrder(1000);
        angle+=scale;
        //固定角度内才可以旋转
        if(angle<=-30&&angle>=-150){
            card->setRotationSkewY(angle);
            if(angle>-90){
                thisLevel->setZOrder(500);
                lastLevel->setZOrder(2000);
            }else{
                thisLevel->setZOrder(2000);
                lastLevel->setZOrder(500);
            }
            thisLevel->setScaleX(-sin((-angle-30)/2*PI/180)/sin(PI/3));
            thisLevel->setRotationSkewY(-(90+(-angle-30)/2+30));
            lastLevel->setScaleX((sin((angle+150)/2*PI/180)/sin(PI/3)));
            lastLevel->setRotationSkewY(-(90-(150+angle)/2-30));
        }
        
    }
}


void CoverView::turnToLevel(int whichLevel)
{
    this->whichLevel=whichLevel-1;
    for (int i=0; i<whichLevel; i++) {
        Node* card=card_right.top();
        card_right.pop();
        card_left.push(card);
    }
}




void CoverView::addCard(Node * card)
{
    int zOrder = cardNum;
    this->addCard(card, zOrder, 0);
}

void CoverView::addCard(Node * card, int zOrder)
{
    this->addCard(card, zOrder,0);
}

void CoverView::addCard(Node* card, int zOrder, int tag)
{
    float positionX = offsetPosition.x;
    //float scale = 1 - disScale*cardNum;
    card->setAnchorPoint(Point(0,0));
    card->setPosition(Point(positionX,offsetPosition.y-300));
    card->setRotationSkewY(-30);
    //card->setScale(scale);
    scrollLayer->addChild(card , zOrder,tag);
    cardNum++;
    card_right.push(card);
    //CCLog("crad%d:[%f , %f]",cardNum,card->getPositionX(),card->getPositionY());
}

void CoverView::addLevel(Node * level)
{
    int zOrder = -1000;
    this->addLevel(level, zOrder, 0);
}

void CoverView::addLevel(Node * level, int zOrder)
{
    this->addLevel(level, zOrder,0);
}

void CoverView::addLevel(Node* level, int zOrder, int tag)
{
    float positionX = offsetPosition.x;
    //float scale = 1 - disScale*cardNum;
    level->setPosition(offsetPosition.x-170, offsetPosition.y-200);
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