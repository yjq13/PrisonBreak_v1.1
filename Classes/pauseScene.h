//
//  pauseScene.hpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 2/5/16.
//
//

#ifndef pauseScene_hpp
#define pauseScene_hpp

#include "cocos2d.h"
#include "MyScene.h"
#endif /* pauseScene_hpp */
class pauseScene : public MyScene{
    cocos2d::Node* stopNodeL;
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    virtual void setUI();
    
    void Callresume(Ref* pSender);
    CREATE_FUNC(pauseScene);
};