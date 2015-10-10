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



void Constant::setConstant(){
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

