//
//  Data_GameInfo.swift
//  PrisonBreak
//
//  Created by yjq131250077 on 15/9/11.
//
//

import Foundation
class GameInfo_deal: NSObject {
    func getGameInfoData(step:Int)->GamePo{
        let paths = NSSearchPathForDirectoriesInDomains(.DocumentDirectory, .UserDomainMask, true) as NSArray
        let documentsDirectory = paths.objectAtIndex(0) as! NSString
        let path = documentsDirectory.stringByAppendingPathComponent("GameInfo.plist")
        let dict = NSDictionary(contentsOfFile: path)
        
        let valueArr:AnyObject? = dict?.objectForKey("Game_\(step)")!
        let _score: Int = valueArr?.objectForKey("score") as! Int
        let _state: Int = valueArr?.objectForKey("state") as! Int
        let _time: Int = valueArr?.objectForKey("time") as! Int
        
        let Gpo : GamePo =  GamePo(score:_score,state:_state,time:_time)
        return Gpo
    }
    
    func writeGameInfoData(po:GamePo,step:Int){
        let paths = NSSearchPathForDirectoriesInDomains(.DocumentDirectory, .UserDomainMask, true) as NSArray
        let documentsDirectory = paths.objectAtIndex(0) as! NSString
        let path = documentsDirectory.stringByAppendingPathComponent("GameInfo.plist")
        let dict = NSMutableDictionary(contentsOfFile: path)
        
        let valueArr:AnyObject? = dict?.objectForKey("Game_\(step)")!
        valueArr?.setObject(po.score, forKey: "score")
        valueArr?.setObject(po.state, forKey: "state")
        //dict?.setObject(po.time, forKey: "time")
        
        dict?.writeToFile(path, atomically: false)
    }
    
    func getGameTmieLine(path:String)->[TimeLinePo]{
        let dict = NSDictionary(contentsOfFile: NSBundle.mainBundle().pathForResource("TimeLine", ofType: "plist")!)
        
        let dict_LEVEL:AnyObject? = dict?.objectForKey(path)!
        let counter = dict_LEVEL?.count
        var valueArr = dict_LEVEL?.allValues
        var polist:[TimeLinePo] = []
        var count = 0
        for(;count<counter;count++){
            let tag: Int = valueArr![count].objectForKey("tag") as! Int
            let startTime: Int = valueArr![count].objectForKey("startTime") as! Int
            let endTime: Int = valueArr![count].objectForKey("endTime") as! Int
            
            let po:TimeLinePo = TimeLinePo(tag: tag, startTime: startTime, endTime: endTime);
            polist.append(po)
            
        }
        return polist
    }
 
}

