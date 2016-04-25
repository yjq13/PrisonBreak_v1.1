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
#import "TimeLineVo.h"
GameVo getGameInfo(int step){
    GameVo vo;
    GamePo *po;
    GameInfo_deal *Gget = [[GameInfo_deal alloc]init];
    po = [Gget getGameInfoData:step];
    vo.setData((NSInteger)po.score,(NSInteger)po.state,(NSInteger)po.time);
    return vo;
}

void setGameInfo(GameVo vo){
    GamePo *po = [GamePo alloc];
    [po initWithScore:vo._score state:vo._state time:vo._time];
    GameInfo_deal *Gwrite = [[GameInfo_deal alloc]init];
    [Gwrite writeGameInfoData:po];
}


std::vector<TimeLineVo> getTimeLine(std::string path){
    NSString *needpath = [NSString stringWithCString:path.c_str()
                                                encoding:[NSString defaultCStringEncoding]];
    TimeLineVo vo;
    NSArray<TimeLinePo *> *polist;
    std::vector<TimeLineVo> volist;
    GameInfo_deal *Gget = [[GameInfo_deal alloc]init];
    polist = [Gget getGameTmieLine:needpath];
    int index= 0;
    for(TimeLinePo *po:polist){
        
        vo.setData((NSInteger)po.tag,(NSInteger)po.startTime,(NSInteger)po.endTime);
        volist.insert(volist.begin(), vo);
        index++;
    }
    return volist;
}