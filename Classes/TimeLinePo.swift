//
//  TimeLinePo.swift
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 12/12/15.
//
//

import Foundation
class TimeLinePo: NSObject {
    
    var tag:Int
    
    var startTime:Int
    
    var endTime:Int
    
    init(tag:Int,startTime:Int,endTime:Int){
        
        self.tag=tag
        self.startTime=startTime
        self.endTime=endTime
    }
}