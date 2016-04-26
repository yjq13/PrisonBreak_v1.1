//
//  SpriteListener.hpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 1/15/16.
//
//

#ifndef SpriteListener_hpp
#define SpriteListener_hpp

#include <stdio.h>
#include <cocos2d.h>
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
class protagonistListener : public cocos2d::EventListenerTouchOneByOne{
private:
    cocos2d::Sprite* protagonist;
public:
    virtual EventListenerTouchOneByOne* create(cocos2d::Sprite* getSprite);
    cocos2d::Rect getRect();
    

    
    bool onTouchBegan(cocos2d::Touch* touch,cocos2d::Event* event);
    
    void onTouchMoved(cocos2d::Touch* touch,cocos2d::Event* event);
    
    void onTouchEnded(cocos2d::Touch* touch,cocos2d::Event* event);

};
#endif /* SpriteListener_hpp */
