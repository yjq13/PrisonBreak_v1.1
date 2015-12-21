#include "TimeLineLoad.h"
#include "OC_callGameInfo.h"
#include "Constant_Use.h"
#include "TimeLineVo.h"
using namespace std;
TIMELINE TimeLineLoad::loadTimeLine(cocos2d::Node* rootNodeL){
    string hand = "res/Game/";
    string tail = ".csb";
    string follow = "/Layer_Game_Level_";
    string allPath = hand+PATH_PART+follow+PATH_LEVEL+tail;
    
    
    //rootTimeLine = CSLoader::createTimeline(all);
    string path = PATH_PART+"_Level_"+PATH_LEVEL;
    
    TIMELINE _timeline;
   
    vector<TimeLineVo> volist = getTimeLine(path);
    for(int i=0;i<volist.size();i++){
        TimeLineVo vo = volist[volist.size()-i-1];
        _timeline.TimeLine[i] = CSLoader::createTimeline(allPath);
        _timeline.TimeLine[i]->setFlags(vo.tag);
        _timeline.TimeLine[i]->gotoFrameAndPlay(vo.startTime,vo.endTime, true);
        rootNodeL->runAction(_timeline.TimeLine[i]);
        //CCLOG("timelineTag:%d",_timeline.TimeLine[i]->getTag());
    }
    
    CCLOG("TIMELINE is OK!!!!!");
    return _timeline;
}