//
//  MusicManager.cpp
//  PrisonBreak_v1.1
//
//  Created by 马长松 on 16/4/24.
//
//

#include "MusicManager.h"
using namespace CocosDenshion;
void MusicManager::init(cocos2d::ui::Widget* buttonOn,cocos2d::ui::Widget* buttonOff){
    if (SimpleAudioEngine::getInstance()->getBackgroundMusicVolume()!=0) {
        buttonOn->setVisible(false);
        buttonOn->setEnabled(false);
        buttonOff->setVisible(true);
        buttonOff->setEnabled(true);
    }else{
        buttonOn->setVisible(true);
        buttonOn->setEnabled(true);
        buttonOff->setVisible(false);
        buttonOff->setEnabled(false);
    }

}
void MusicManager::turnMusicOn(cocos2d::Ref *pSender, cocos2d::ui::Widget* buttonOn,cocos2d::ui::Widget* buttonOff){
    if (SimpleAudioEngine::getInstance()->getBackgroundMusicVolume()==0) {
        buttonOn->setVisible(false);
        buttonOn->setEnabled(false);
        buttonOff->setVisible(true);
        buttonOff->setEnabled(true);
    }
    SimpleAudioEngine::getInstance()->setEffectsVolume(SimpleAudioEngine::getInstance()->getEffectsVolume()==0?10:0);
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(SimpleAudioEngine::getInstance()->getBackgroundMusicVolume()==0?10:0);
}
void MusicManager::turnMusicOff(cocos2d::Ref *pSender, cocos2d::ui::Widget* buttonOn,cocos2d::ui::Widget* buttonOff){
    if (SimpleAudioEngine::getInstance()->getBackgroundMusicVolume()!=0) {
        buttonOn->setVisible(true);
        buttonOn->setEnabled(true);
        buttonOff->setVisible(false);
        buttonOff->setEnabled(false);
    }
    SimpleAudioEngine::getInstance()->setEffectsVolume(SimpleAudioEngine::getInstance()->getEffectsVolume()==0?10:0);
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(SimpleAudioEngine::getInstance()->getBackgroundMusicVolume()==0?10:0);
}