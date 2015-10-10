//
//  Constant.h
//  PrisonBreak
//
//  Created by yjq131250077 on 15/9/17.
//
//

#ifndef __PrisonBreak__Constant__
#define __PrisonBreak__Constant__

#include <stdio.h>
class Constant{
public:
    bool VOICE;
    bool SOUND;
    int GOLD_COIN;
    int DIAMOND;
    int SPEED;
    int LV;
    int STEP;
    void setConstant();
};

static Constant ALLINFO;
#endif /* defined(__PrisonBreak__Constant__) */
