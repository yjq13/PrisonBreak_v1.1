//
//  Data_FigureInfo.swift
//  PrisonBreak
//
//  Created by yjq131250077 on 15/9/12.
//
//

import Foundation

class FigureInfo_deal: NSObject {
    func getFigureInfoData()->FigurePo{
        //var dict1 = NSDictionary(contentsOfFile: NSBundle.mainBundle().pathForResource("FigureInfo", ofType: "plist")!)
        
        let paths = NSSearchPathForDirectoriesInDomains(.DocumentDirectory, .UserDomainMask, true) as NSArray
        let documentsDirectory = paths.objectAtIndex(0) as! NSString
        let path = documentsDirectory.stringByAppendingPathComponent("FigureInfo.plist")
        let dict = NSDictionary(contentsOfFile: path)
        
        let _LV:Int = dict?.objectForKey("LV") as! Int
        let _speed:Int = dict?.objectForKey("speed") as! Int
        let _gold_coin:Int = dict?.objectForKey("gold_coin") as! Int
        let _diamond:Int = dict?.objectForKey("diamond") as! Int

        let _step:Int = dict?.objectForKey("step") as! Int
        let Gpo : FigurePo =  FigurePo(LV: _LV, step:_step,speed: _speed, gold_coin: _gold_coin, diamond: _diamond)
        
        return Gpo
    }
    
    func writeFigureInfoData(po:FigurePo){
        let paths = NSSearchPathForDirectoriesInDomains(.DocumentDirectory, .UserDomainMask, true) as NSArray
        let documentsDirectory = paths.objectAtIndex(0) as! NSString
        let path = documentsDirectory.stringByAppendingPathComponent("FigureInfo.plist")
        let dict = NSMutableDictionary(contentsOfFile: path)
        
        dict?.setObject(po.speed, forKey: "speed")
        dict?.setObject(po.LV, forKey: "LV")
        dict?.setObject(po.gold_coin, forKey: "gold_coin")
        dict?.setObject(po.diamond, forKey: "diamond")
        dict?.setObject(po.step, forKey: "step")
        
        dict?.writeToFile(path, atomically: false)
        
    }
}