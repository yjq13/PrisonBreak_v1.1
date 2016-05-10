//
//  ButtonManager.cpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 16/4/28.
//
//

#include "ButtonManager.h"
#include "GameManager.h"

void ButtonManager::shieldButton(){
    GameManager::Button_Back->setEnabled(false);
    GameManager::Button_Tool_1->setEnabled(false);
    GameManager::Button_Tool_2->setEnabled(false);
}


void ButtonManager::resumeButton(){
    GameManager::Button_Back->setEnabled(true);
    GameManager::Button_Tool_1->setEnabled(true);
    GameManager::Button_Tool_2->setEnabled(true);
}