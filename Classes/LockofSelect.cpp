//
//  LockofSelect.cpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 11/30/15.
//
//

#include "LockofSelect.h"
bool LockofSelect::checkLock_inside(int number){
    if(number<=STEP){
        return true;
    }else{
        return false;
    }
}

bool LockofSelect::checkLock_outside(int number){
    if((number-1)<=STEP/15){
        return true;
    }else{
        return false;
    }
}