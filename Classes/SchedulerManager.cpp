#include "SchedulerManager.h"
#include "OC_callGameInfo.h"
#include "Constant_Use.h"
#include "TimeLineVo.h"
#include "GameManager.h"
using namespace std;
TIMELINE SchedulerManager::loadTimeLine(cocos2d::Node* rootNodeL){
    string hand = "res/Game/";
    string tail = ".csb";
    string follow = "/Layer_Game_Level_";
    string allPath = hand+PATH_PART+follow+PATH_LEVEL+tail;
    
    TIMELINE_NUM = 0;
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
        TIMELINE_NUM++;
    }
    
    CCLOG("TIMELINE is OK!!!!!");
    return _timeline;
}


void SchedulerManager::setProScheduler(Scheduler* sch){
    GameManager::PRO_SCHEDULER = sch;
}

void SchedulerManager::pausePro(){
    GameManager::target_pro = GameManager::PRO_SCHEDULER->pauseAllTargets();
}


void SchedulerManager::resumePro(){
    GameManager::PRO_SCHEDULER->resumeTargets(GameManager::target_pro);
}

void SchedulerManager::pauseTimeLine(){
    for(int i=0;i<TIMELINE_NUM;i++){
            //CCLOG("%d",GameManager::_TIMELINE.TimeLine[i]->getTag());
            GameManager::_TIMELINE.TimeLine[i]->pause();
    }
}


void SchedulerManager::resumeTimeLine(){
    
    for(int i=0;i<TIMELINE_NUM;i++){
        //CCLOG("%d",_TIMELINE.TimeLine[i]->getTag());
        GameManager::_TIMELINE.TimeLine[i]->resume();
    }
}


void SchedulerManager::stopTimeLine(int Tag){
    for(int i = 0;i<20;i++){
        if((signed)GameManager::_TIMELINE.TimeLine[i]->getFlags()==Tag){
            GameManager::_TIMELINE.TimeLine[i]->pause();
            break;
        }
    }
}
