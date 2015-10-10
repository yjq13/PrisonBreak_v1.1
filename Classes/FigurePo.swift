//
//  FigurePo.swift
//  PrisonBreak
//
//  Created by yjq131250077 on 15/9/15.
//
//

import Foundation
class FigurePo: NSObject {
    
    var LV:Int
    
    var speed:Int
    
    var gold_coin:Int
    
    var diamond:Int
    
    var step:Int
    init(LV:Int,step:Int,speed:Int,gold_coin:Int,diamond:Int){
        self.step=step
        self.LV=LV
        self.speed=speed
        self.diamond=diamond
        self.gold_coin=gold_coin
    }
}