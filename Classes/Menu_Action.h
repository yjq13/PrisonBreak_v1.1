//
//  Menu_Action.hpp
//  PrisonBreak_v1.1
//
//  Created by 马长松 on 16/1/24.
//
//

#ifndef Menu_Action_hpp
#define Menu_Action_hpp

#include <stdio.h>
#include "cocos2d.h"
class MenuAction{
    
public:
    void setPauseConfig(Node* menu);
    void setFailConfig(Node* menu);
    void setSuccessConfig(Node* menu);
    
    void pauseCallresume(Ref* pSender,Node* layer);
    void Callrestart(Ref *pSender,Node* layer);
    void menuCloseCallback(Ref* pSender,Node* layer);
    
    static void move_in(cocos2d::Node* menu);
    static void move_out(cocos2d::Node* menu);
    Node* create_Menu(int MenuNumber);
    
};
#endif /* Menu_Action_hpp */
