//
//  Constant_Game.cpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 16/4/7.
//
//

#include "GameManager.h"
Section GameManager::START_SECTION = Section();

Section GameManager::DESTINATION_SECTION = Section();

Section GameManager::STOP_SECTION = Section();

TIMELINE GameManager::_TIMELINE = *new TIMELINE();

Scheduler* GameManager::PRO_SCHEDULER = new Scheduler();


set<void *> GameManager::target_pro = *new set<void *>();

std::vector<cocos2d::EventListenerTouchOneByOne*> GameManager::JailerlistenerList = *new std::vector<cocos2d::EventListenerTouchOneByOne*>();

std::vector<cocos2d::EventListenerTouchOneByOne*> GameManager::WalllistenerList = *new std::vector<cocos2d::EventListenerTouchOneByOne*>();
