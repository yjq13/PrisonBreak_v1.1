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
        let dict = NSDictionary(contentsOfFile: NSBundle.mainBundle().pathForResource("GameInfo", ofType: "plist")!)
        
        let valueArr:AnyObject? = dict?.objectForKey("Game_\(step)")!
        let _step: Int = valueArr?.objectForKey("step") as! Int
        let _state: Int = valueArr?.objectForKey("state") as! Int
        let _time: Int = valueArr?.objectForKey("time") as! Int

        
        let Gpo : GamePo =  GamePo(step:_step,state:_state,time:_time)
        return Gpo
    }
    
    
    func getGameTmieLine(path:String)->[TimeLinePo]{
        let dict = NSDictionary(contentsOfFile: NSBundle.mainBundle().pathForResource("TimeLine", ofType: "plist")!)
        
        let dict_LEVEL:AnyObject? = dict?.objectForKey(path)!
        let counter = dict_LEVEL?.count
        var valueArr = dict_LEVEL?.allValues
        var polist:[TimeLinePo] = []
        var count = 0
        for(count;count<counter;count++){
            let tag: Int = valueArr![count].objectForKey("tag") as! Int
            let startTime: Int = valueArr![count].objectForKey("startTime") as! Int
            let endTime: Int = valueArr![count].objectForKey("endTime") as! Int
            
            let po:TimeLinePo = TimeLinePo(tag: tag, startTime: startTime, endTime: endTime);
            polist.append(po)
            
        }
        print(polist)
        return polist
    }
 
}

