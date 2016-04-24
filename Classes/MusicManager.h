//
//  MusicManager.hpp
//  PrisonBreak_v1.1
//
//  Created by 马长松 on 16/4/24.
//
//

#ifndef MusicManager_hpp
#define MusicManager_hpp

//声音头文件及命名空间
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include <stdio.h>
#include "ui/CocosGUI.h"
class MusicManager{
public:
    void turnMusicOn(cocos2d::Ref* pSender,cocos2d::ui::Widget* buttonOn,cocos2d::ui::Widget* buttonOff);
    void turnMusicOff(cocos2d::Ref* pSender,cocos2d::ui::Widget* buttonOn,cocos2d::ui::Widget* buttonOff);
    void init(cocos2d::ui::Widget* buttonOn,cocos2d::ui::Widget* buttonOff);
};

#endif /* MusicManager_hpp */
