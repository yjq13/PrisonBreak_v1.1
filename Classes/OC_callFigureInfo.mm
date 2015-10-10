//
//  OC-callFigureInfo.m
//  PrisonBreak
//
//  Created by yjq131250077 on 15/9/11.
//
//

//#import <Foundation/Foundation.h>
#import <OC_callFigureInfo.h>
#import "PrisonBreak_mobile-Swift.h"
#import "FigureVo.h"
FigureVo getFigureInfo(){
    FigureVo vo;
    FigurePo *po;
    FigureInfo_deal *Fget = [[FigureInfo_deal alloc]init];
    po = [Fget getFigureInfoData];
    vo.setData(po.LV,po.step,po.speed,po.gold_coin,po.diamond);
    return vo;
}

void setFigureInfo(FigureVo vo){
    FigurePo *po = [FigurePo alloc];
    [po initWithLV:vo._LV step:vo._step speed:vo._speed gold_coin:vo._gold_coin diamond:vo._diamond];
    FigureInfo_deal *Swrite = [[FigureInfo_deal alloc]init];
    [Swrite writeFigureInfoData:po];
}
