//
//  SpriteManager.cpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 16/4/20.
//
//

#include "SpriteManager.h"
#include "GameManager.h"
#include "Constant_Use.h"
void SpriteManager::setStopJailer(int Tag){

    for(int i=0;i<10;i++){
        if(GameManager::jailer[i].getTag()==Tag){
            GameManager::jailer[i].setIsStop(true);
            break;
        }
    }
    
}


Sprite_jailer* SpriteManager::getJailerByTag(int aTag){
    for(int i=0;i<10;i++){
        if(GameManager::jailer[i].getTag()==aTag){
            return &GameManager::jailer[i];
        }
    }
    return NULL;
}