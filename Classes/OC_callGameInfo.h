//
//  OC-callGameInfo.h
//  PrisonBreak
//
//  Created by yjq131250077 on 15/9/11.
//
//>


#ifndef PrisonBreak_OC_callGameInfo_h
#define PrisonBreak_OC_callGameInfo_h
#include <stdio.h>
class GameVo;
class TimeLineVo;

GameVo getGameInfo(int);

void setGameInfo(GameVo,int);

std::vector<TimeLineVo> getTimeLine(std::string);

#endif




