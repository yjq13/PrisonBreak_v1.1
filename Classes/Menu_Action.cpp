//
//  Menu_Action.cpp
//  PrisonBreak_v1.1
//
//  Created by 马长松 on 16/1/24.
//
//
#include "cocos2d.h"
#include "Constant_Use.h"
#include "Menu_Action.h"
USING_NS_CC;
void MenuAction::move_in(cocos2d::Node *menu){
  //Movein
    MoveTo* Movein_1=MoveTo::create(0.3f,Point(0,0));
    EaseExponentialIn* moveIn_1 = EaseExponentialIn::create(Movein_1);
    MoveTo* Movein_2=MoveTo::create(0.3f,Point(0,70));
    EaseExponentialOut* moveIn_2 = EaseExponentialOut::create(Movein_2);
    MoveTo* Movein_3=MoveTo::create(0.2f,Point(0,0));
    EaseExponentialIn* moveIn_3 = EaseExponentialIn::create(Movein_3);
    auto ac=Sequence::create(moveIn_1,moveIn_2,moveIn_3, NULL);
    menu->runAction(ac);
}
void MenuAction::move_out(cocos2d::Node *menu){
    MoveTo* Moveout=MoveTo::create(0.3f,Point(0,VISIBLE_SIZE.height));
    EaseExponentialOut* moveOut = EaseExponentialOut::create(Moveout);
    menu->runAction(moveOut);
}