//
//  CoverView.hpp
//  CocosProject
//
//  Created by 马长松 on 15/12/6.
//
//

#ifndef __CoverView_H__
#define __CoverView_H__
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class CoverView : public Node{
private:
    //书的左右边
    std::stack<Node* > card_left;
    std::stack<Node* > card_right;
    //上一关与下一关
    Node* lastLevel;
    Node* thisLevel;
    //已旋转的角度
    float angle;
    //是左滑还是右滑
    bool isRight;
    //是否松手
    bool isHandOff;
    //是否结束动画
    bool isShiftDone;
    //到哪一关了
    int whichLevel;
    
    //用于排序
    ValueVector order_left;
    ValueVector order_right;
    int levelNum;
public:
    CoverView();
    ~CoverView();
    /**
     *
     * @param scrollView的rect
     * @param scrollView滚动size
     * @param card之间的距离
     * @param card之间的缩放
     */
    static CoverView* create(Rect swBox, Size slSize ,float disDistance , float disScale );
    virtual bool init(Rect swBox , Size slSize , float disDistance , float disScale);
    virtual bool onTouchBegin(Touch* pTouch, Event* pEvent);
    virtual void onTouchMoved(Touch* pTouch, Event* pEvent);
    virtual void onTouchEnded(Touch* pTouch, Event* pEvent);
    void update(float dt);
    void initData();
    void initCard(int cardNum,cocos2d::ui::Widget* card,cocos2d::ui::Widget* start_0,cocos2d::ui::Widget* start_1,cocos2d::ui::Widget* start_2,cocos2d::ui::Widget* start_3);
    void initLevel(int currentLevel,cocos2d::ui::Widget* lock);
    void adjustCardScale(Point adjustPoint);
    int getCurLevel();
    void addCard(Node * card);
    void addCard(Node * card, int zOrder);
    void addCard(Node* card, int zOrder, int tag);
    void addLevel(Node * level);
    void addLevel(Node * level, int zOrder);
    void addLevel(Node* level, int zOrder, int tag);
    void turnToLevel(int whichLevel);
    CC_SYNTHESIZE(Point , swPosition , SwPosition);//scrollView 位置
    CC_SYNTHESIZE(Size , swSize , SwSize);//scrollView大小
    CC_SYNTHESIZE(Size , slSize , SlSize);//scrollLayer 大小
    CC_SYNTHESIZE(float , disDistance , DisDistance);//card距离间隔
    CC_SYNTHESIZE(float , disScale , DisScale);//card缩放间隔
    CC_SYNTHESIZE(Rect , swBox , SwBox);//scrollview 边框
    CC_SYNTHESIZE(Layer* , scrollLayer , scrollLayer);//scrollView的containLayer
    CC_SYNTHESIZE(int , cardNum , CardNum);//card索引
    CC_PROPERTY(Point , offsetPosition , OffsetPosition);//card起始位置
    CC_SYNTHESIZE(Point, slayerPosition, SlayerPosition);//sontainLayer的位置
    EventListenerTouchOneByOne* Listener;
private:
    Size wSize;
    Array* levelArray;
    ScrollView* scrollView;
    int totalCard;
    cocos2d::ui::Widget* start_0;
    cocos2d::ui::Widget* start_1;
    cocos2d::ui::Widget* start_2;
    cocos2d::ui::Widget* start_3;
};
#endif