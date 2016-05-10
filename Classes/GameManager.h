//
//  Constant_Game.hpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 16/4/7.
//
//

#ifndef Constant_Game_hpp
#define Constant_Game_hpp

#include "Constant_Use.h"
#include "Sprite_jailer.h"
#include "JailerListener.h"
#include "protagonistListener.h"
#include "WallListener.h"
class GameManager{
    
public:
static int stepNow;

static bool isStop;
    
static bool isTouchPro;
    
static int  stepOfGame;
    
static cocos2d::EventListenerTouchOneByOne* Prolistener;
    
static TIMELINE _TIMELINE;

static Scheduler* PRO_SCHEDULER;

static set<void *> target_else;

static set<void *> target_pro;
    
static cocos2d::ui::Button* Button_Back;
    
static cocos2d::ui::Button* Button_Tool_1;
    
static cocos2d::ui::Button* Button_Tool_2;
    
static Sprite_jailer jailer[10];
    
static JailerListener jailerlistener[10];
    
static wallListener walllistener[10];
    
static protagonistListener proListener;

static vector<cocos2d::EventListenerTouchOneByOne*> JailerlistenerList;

static vector<cocos2d::EventListenerTouchOneByOne*> WalllistenerList;
};


#endif /* Constant_Game_hpp */
