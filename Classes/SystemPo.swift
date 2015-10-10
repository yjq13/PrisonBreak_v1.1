//
//  SystemPo.swift
//  PrisonBreak
//
//  Created by yjq131250077 on 15/9/15.
//
//

import Foundation
class SystemPo: NSObject {
    
    var voice:Bool
    
    var sound:Bool

    init(voice:Bool,sound:Bool){
        
        self.voice=voice
        self.sound=sound
    }
}