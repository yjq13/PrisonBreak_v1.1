//
//  OC-callSystemInfo.m
//  PrisonBreak
//
//  Created by yjq131250077 on 15/9/11.
//
//

#import <OC_callSystemInfo.h>
#import "PrisonBreak_mobile-Swift.h"
#import "SystemVo.h"
SystemVo getSystemInfo(){
    SystemVo vo;
    SystemPo *po;
    SystemInfo_deal *Sget = [[SystemInfo_deal alloc]init];
    po = [Sget getSystemInfoData];
    vo.setData(po.voice,po.sound);
    return vo;
}

void setSystemInfo(SystemVo vo){
    SystemPo *po = [SystemPo alloc];
    [po initWithVoice:vo._voice sound:vo._sound];
    SystemInfo_deal *Swrite = [[SystemInfo_deal alloc]init];
    [Swrite writeSystemInfoData:po];
}

void initDocuments(){
    initDocument *initD = [[initDocument alloc]init];
    [initD initDoc];
}