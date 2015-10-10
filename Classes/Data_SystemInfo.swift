//
//  Data_SystemInfo.swift
//  PrisonBreak
//
//  Created by yjq131250077 on 15/9/12.
//
//

import Foundation

class SystemInfo_deal: NSObject {
    func getSystemInfoData()->SystemPo{
            let paths = NSSearchPathForDirectoriesInDomains(.DocumentDirectory, .UserDomainMask, true) as NSArray
            let documentsDirectory = paths.objectAtIndex(0) as! NSString
            let path = documentsDirectory.stringByAppendingPathComponent("SystemInfo.plist")
            let dict = NSDictionary(contentsOfFile: path)

            let _voice: Bool = dict?.objectForKey("voice") as! Bool
            let _sound: Bool = dict?.objectForKey("sound") as! Bool
            let Gpo : SystemPo =  SystemPo(voice:_voice,sound:_sound)
            return Gpo
            }
    
    func writeSystemInfoData(po:SystemPo){
        let paths = NSSearchPathForDirectoriesInDomains(.DocumentDirectory, .UserDomainMask, true) as NSArray
        let documentsDirectory = paths.objectAtIndex(0) as! NSString
        let path = documentsDirectory.stringByAppendingPathComponent("SystemInfo.plist")
        let dict = NSMutableDictionary(contentsOfFile: path)

        dict?.setObject(po.voice, forKey: "voice")
        dict?.setObject(po.sound, forKey: "sound")
        
        dict?.writeToFile(path, atomically: false)

    }
}