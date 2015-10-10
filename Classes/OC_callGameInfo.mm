//
//  OC-callGameInfo.m
//  PrisonBreak
//
//  Created by yjq131250077 on 15/9/11.
//
//


#import <OC_callGameInfo.h>
#import "PrisonBreak_mobile-Swift.h"
#import "GameVo.h"

GameVo getGameInfo(int step){
    GameVo vo;
    GamePo *po;
    GameInfo_deal *Gget = [[GameInfo_deal alloc]init];
    po = [Gget getGameInfoData:step];
    vo.setData((NSInteger)po.step,(NSInteger)po.state,(NSInteger)po.time);
    return vo;
}