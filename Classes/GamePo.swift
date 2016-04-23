//
//  GamePo.swift
//  PrisonBreak
//
//  Created by yjq131250077 on 15/9/15.
//
//

import Foundation
class GamePo: NSObject {
    
    var score :Int
    var state :Int
    var time :Int
    
    init(score:Int,state:Int,time:Int){
        self.time=time
        self.state=state
        self.score=score
    }
}