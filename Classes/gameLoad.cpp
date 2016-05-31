//
//  gameLoad.cpp
//  PrisonBreak_v1.1
//
//  Created by yjq131250077 on 12/11/15.
//
//

#include "gameLoad.h"
#include <cocos2d.h>
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "Sprite_protagonist.h"
#include "Sprite_jailer.h"
#include "Sprite_wall.h"
#include "Special_Section.h"
#include "Constant_Use.h"
#include "GameManager.h"
#include <iostream>
#include "Sprite_mouse.h"
#include "JailerListener.h"
#include "WallListener.h"
#include "SchedulerManager.h"
#include "protagonistListener.h"
#include "Section.h"
USING_NS_CC;

using namespace ui;




void gameLoad::loadGame(cocos2d::Node* rootNodeL){
    
       
    //警卫加载

    Sprite* Demo_jailer[10];

    int index = 0;
    do{
    index++;
        char number[25];
        memset(number,0,sizeof(number));
        sprintf(number,"%d",index);
        string numberStr=number;
        
        string first = "Sprite_Jailer_";
        string all = first+numberStr;
        
    Demo_jailer[index] = rootNodeL->getChildByName<Sprite*>(all);
        if(Demo_jailer[index]!=NULL){
            GameManager::jailer[index].setJailer(index,Demo_jailer[index]);
            EventListenerTouchOneByOne* listener = GameManager::jailerlistener[index].create(Demo_jailer[index]);
            listener->setEnabled(false);
            GameManager::JailerlistenerList.push_back(listener);
            
            Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, Demo_jailer[index]);
            
        }
    }while(Demo_jailer[index]!=NULL);
    
    
    //墙体加载
    Sprite* Demo_wall[10];
    index = 0;
    do{
        index++;
        char number[25];
        memset(number,0,sizeof(number));
        sprintf(number,"%d",index);
        string numberStr=number;
        
        string first = "Sprite_Wall_";
        string all = first+numberStr;
        
        
        Demo_wall[index] = rootNodeL->getChildByName<Sprite*>(all);
        if(Demo_wall[index]!=NULL){
            Sprite_wall::setWall(index,Demo_wall[index]);
            auto height=Director::getInstance()->getOpenGLView()->getFrameSize().height;
            Demo_wall[index]->setScale(DESIGN_SIZE.height/height);

            EventListenerTouchOneByOne* listener = GameManager::walllistener[index].create(Demo_wall[index]);
            
            listener->setEnabled(false);
            GameManager::WalllistenerList.push_back(listener);
            //_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, getSprite);
            //添加一个触摸委托给dispatcher的列表,委托对象this,
            Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, Demo_wall[index]);
        }
    }while(Demo_wall[index]!=NULL);
    
    
    
    //老鼠加载
    Sprite* Demo_Mouse[10];
    index = 0;
    do{
        index++;
        char number[25];
        memset(number,0,sizeof(number));
        sprintf(number,"%d",index);
        string numberStr=number;
        
        string first = "Sprite_Mouse_";
        string all = first+numberStr;
        
        Demo_Mouse[index] = rootNodeL->getChildByName<Sprite*>(all);
        if(Demo_Mouse[index]!=NULL){
            Sprite_mouse::setMouse(index,Demo_Mouse[index]);
        }
    }while(Demo_Mouse[index]!=NULL);

    
    //主角加载
    auto Demo_protagonist = rootNodeL->getChildByName<Sprite*>("Sprite_Protagonist");
    Sprite_protagonist::setPro(0,Demo_protagonist);
    
    Scheduler* sched1;
    
    ActionManager* actionManager1;
    
    Scheduler* defaultScheduler = Director::getInstance()->getScheduler();
    
    sched1 = new Scheduler();
    
    defaultScheduler->scheduleUpdate(sched1, 0, false);
    
    actionManager1 = new ActionManager();
    
    sched1->scheduleUpdate(actionManager1, 0, false);
    
    Demo_protagonist->setActionManager(actionManager1);
    
    Demo_protagonist->setScheduler(sched1);
    
    SchedulerManager::setProScheduler(sched1);
    
    
    
    EventListenerTouchOneByOne* listener = GameManager::proListener.create(Demo_protagonist);
    
    listener->setEnabled(true);
    
    GameManager::Prolistener = listener;
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, Demo_protagonist);
    
    //特殊区域加载
    Sprite* Demo_Section_Slow[10];
    index = 0;
    do{
        index++;
        char number[25];
        memset(number,0,sizeof(number));
        sprintf(number,"%d",index);
        string numberStr=number;
        
        string first = "Sprite_Slow_Section_";
        string all = first+numberStr;
        Demo_Section_Slow[index] = rootNodeL->getChildByName<Sprite*>(all);
        if(Demo_Section_Slow[index]!=NULL)
            Sprite_SpecialSection::setSpecialSection(index,Demo_Section_Slow[index]);
    }while(Demo_Section_Slow[index]!=NULL);
    
    //特殊区域加载
    Sprite* Demo_Section_Quick[10];
    index = 0;
    do{
        index++;
        char number[25];
        memset(number,0,sizeof(number));
        sprintf(number,"%d",index);
        string numberStr=number;
        
        string first = "Sprite_Quick_Section_";
        string all = first+numberStr;
        Demo_Section_Quick[index] = rootNodeL->getChildByName<Sprite*>(all);
        if(Demo_Section_Quick[index]!=NULL)
            Sprite_SpecialSection::setSpecialSection(500+index,Demo_Section_Quick[index]);
    }while(Demo_Section_Quick[index]!=NULL);
    
   
    
    //终点加载
    Sprite* End_Section;

    string all = "Sprite_Destination";
    End_Section = rootNodeL->getChildByName<Sprite*>(all);

    End_Section::setEnd_Section(index,End_Section);
    
}