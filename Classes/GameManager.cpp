//
//  Constant_Game.cpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 16/4/7.
//
//

#include "GameManager.h"

TIMELINE GameManager::_TIMELINE = *new TIMELINE();

Scheduler* GameManager::PRO_SCHEDULER = new Scheduler();

cocos2d::ui::Button* GameManager::Button_Back;

cocos2d::ui::Button* GameManager::Button_Tool_1;

cocos2d::ui::Button* GameManager::Button_Tool_2;


set<void *> GameManager::target_pro = *new set<void *>();

std::vector<cocos2d::EventListenerTouchOneByOne*> GameManager::JailerlistenerList = *new std::vector<cocos2d::EventListenerTouchOneByOne*>();

cocos2d::EventListenerTouchOneByOne* GameManager::Prolistener = new cocos2d::EventListenerTouchOneByOne();

std::vector<cocos2d::EventListenerTouchOneByOne*> GameManager::WalllistenerList = *new std::vector<cocos2d::EventListenerTouchOneByOne*>();

bool GameManager::isStop = false;

bool GameManager::isTouchPro = false;

int GameManager::stepOfGame = 3;

int GameManager::stepNow = 0;

protagonistListener GameManager::proListener = *new protagonistListener();

Sprite_jailer GameManager::jailer[10];

JailerListener GameManager::jailerlistener[10];

wallListener GameManager::walllistener[10];


