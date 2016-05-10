//
//  Constant.cpp
//  PrisonBreak
//
//  Created by yjq131250077 on 15/9/17.
//
//

#include "Constant.h"
#include "OC_callFigureInfo.h"
#include "OC_callSystemInfo.h"
#include "SystemVo.h"
#include "FigureVo.h"
#include "CacheData.h"
bool VOICE = true;

bool SOUND = true;

int GOLD_COIN = 0;

int DIAMOND = 0;

int SPEED = 0;

int LV = 0;

int STEP = 0;



extern void setConstant();

void updateConstant(){
    DIAMOND = DIAMOND+DIAMOND_GET;
    
    STEP = STEP;
    GOLD_COIN = GOLD_COIN+GOLD_COIN_GET;
    FigureVo Fvo;
    Fvo._step = STEP;
    Fvo._diamond = DIAMOND;
    Fvo._gold_coin = GOLD_COIN;
    
    setFigureInfo(Fvo);
};

void setConstant(){
    SystemVo Svo;
    FigureVo Fvo;
    Svo = getSystemInfo();
    Fvo = getFigureInfo();
    SPEED = Fvo._speed;
    LV = Fvo._LV;
    DIAMOND = Fvo._diamond;
    STEP = Fvo._step;
    GOLD_COIN = Fvo._gold_coin;
    VOICE = Svo._voice;
    SOUND = Svo._sound;
    printf("constant is OK\n");
};

