//
//  ListenerManager.cpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 16/4/9.
//
//

#include "ListenerManager.h"
#include "GameManager.h"

void ListenerManager::addListenerJailer(){
    for(int i = 0;i<GameManager::JailerlistenerList.size();i++){
        EventListenerTouchOneByOne* listener = GameManager::JailerlistenerList[i];
        listener->setEnabled(true);
    }

}

void ListenerManager::removeListenerJailer(){
    for(int i = 0;i<GameManager::JailerlistenerList.size();i++){
        EventListenerTouchOneByOne* listener = GameManager::JailerlistenerList[i];
        listener->setEnabled(false);
    }
    
}

void ListenerManager::removeListenerWall(){
    for(int i = 0;i<GameManager::JailerlistenerList.size();i++){
        EventListenerTouchOneByOne* listener = GameManager::WalllistenerList[i];
        listener->setEnabled(false);
    }
    
}

void ListenerManager::addListenerWall(){
    for(int i = 0;i<GameManager::WalllistenerList.size();i++){
        EventListenerTouchOneByOne* listener = GameManager::WalllistenerList[i];
        listener->setEnabled(true);
    }
}