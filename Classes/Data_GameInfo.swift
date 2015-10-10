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
}