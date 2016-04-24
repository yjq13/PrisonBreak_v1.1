//
//  CacheData.cpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 10/12/15.
//
//

#include "CacheData.h"
#include "GameManager.h"
int GOLD_COIN_GET = 0;

int DIAMOND_GET = 0;

int POINT_GET = 0;

int SCORE_GET = 0;

void initCacheData(){
    GOLD_COIN_GET = 0;
    DIAMOND_GET = 0;
    POINT_GET = 0;
    SCORE_GET = 0;
}

int getScore(){
    SCORE_GET = 10000*GameManager::stepOfGame+1000*GOLD_COIN_GET+11*(2000-POINT_GET);
    return SCORE_GET;
}