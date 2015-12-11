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
class CoverView : public CCNode , public ScrollViewDelegate{
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
    static CoverView* create(CCRect swBox, CCSize slSize ,float disDistance , float disScale );
    virtual bool init(CCRect swBox , CCSize slSize , float disDistance , float disScale);
    virtual void onEnter();
    virtual void onExit();
    virtual bool onTouchBegin(CCTouch* pTouch, CCEvent* pEvent);
    virtual void onTouchMoved(CCTouch* pTouch, CCEvent* pEvent);
    virtual void onTouchEnded(CCTouch* pTouch, CCEvent* pEvent);
    void initData();
    void scrollViewDidScroll(ScrollView* view);
    void scrollViewDidZoom(ScrollView* view);
    void adjustCardScale(CCPoint adjustPoint);
    void adjustScrollView(CCPoint adjustPoint);
    void adjusetEndScrollView();
    void cardViewEnd_callBack(CCNode* pSender);
    int getCurCardIndex();//当前中间card索引 从0开始
    void addCard(CCNode * card);
    void addCard(CCNode * card, int zOrder);
    void addCard(CCNode* card, int zOrder, int tag);
    CC_SYNTHESIZE(CCPoint , swPosition , SwPosition);//scrollView 位置
    CC_SYNTHESIZE(CCSize , swSize , SwSize);//scrollView大小
    CC_SYNTHESIZE(CCSize , slSize , SlSize);//scrollLayer 大小
    CC_SYNTHESIZE(float , disDistance , DisDistance);//card距离间隔
    CC_SYNTHESIZE(float , disScale , DisScale);//crad缩放间隔
    CC_SYNTHESIZE(CCRect , swBox , SwBox);//scrollview 边框
    CC_SYNTHESIZE(CCLayer* , scrollLayer , scrollLayer);//scrollView的containLayer
    CC_SYNTHESIZE(int , cardNum , CardNum);//card索引
    CC_PROPERTY(CCPoint , offsetPosition , OffsetPosition);//card起始位置
    CC_SYNTHESIZE(CCPoint, slayerPosition, SlayerPosition);//sontainLayer的位置
    CC_SYNTHESIZE(bool, isMove, IsMove);//是否发生了移动用于加入菜单的时候能滑动并正确响应事件
private:
    CCSize wSize;
    CCArray* cardArray;
    ScrollView* scrollView;
};
#endif