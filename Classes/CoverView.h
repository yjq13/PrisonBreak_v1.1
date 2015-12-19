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
class CoverView : public Node , public ScrollViewDelegate{
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
    void initData();
    void addListener();
    void removeListener();
    void scrollViewDidScroll(ScrollView* view);
    void scrollViewDidZoom(ScrollView* view);
    void adjustCardScale(Point adjustPoint);
    void adjustScrollView(Point adjustPoint);
    void adjusetEndScrollView();
    void cardViewEnd_callBack(Node* pSender);
    int getCurCardIndex();//当前中间card索引 从0开始
    void addCard(Node * card);
    void addCard(Node * card, int zOrder);
    void addCard(Node* card, int zOrder, int tag);
    CC_SYNTHESIZE(Point , swPosition , SwPosition);//scrollView 位置
    CC_SYNTHESIZE(Size , swSize , SwSize);//scrollView大小
    CC_SYNTHESIZE(Size , slSize , SlSize);//scrollLayer 大小
    CC_SYNTHESIZE(float , disDistance , DisDistance);//card距离间隔
    CC_SYNTHESIZE(float , disScale , DisScale);//crad缩放间隔
    CC_SYNTHESIZE(Rect , swBox , SwBox);//scrollview 边框
    CC_SYNTHESIZE(Layer* , scrollLayer , scrollLayer);//scrollView的containLayer
    CC_SYNTHESIZE(int , cardNum , CardNum);//card索引
    CC_PROPERTY(Point , offsetPosition , OffsetPosition);//card起始位置
    CC_SYNTHESIZE(Point, slayerPosition, SlayerPosition);//sontainLayer的位置
    CC_SYNTHESIZE(bool, isMove, IsMove);//是否发生了移动用于加入菜单的时候能滑动并正确响应事件
    EventListenerTouchOneByOne* Listener;
private:
    Size wSize;
    Array* cardArray;
    ScrollView* scrollView;
};
#endif