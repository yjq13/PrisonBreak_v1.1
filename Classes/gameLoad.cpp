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
#include "Section.h"
#include "Sprite_protagonist.h"
#include "Sprite_jailer.h"
#include "Sprite_wall.h"
#include "Constant_Use.h"
#include <iostream>
#include "Sprite_mouse.h"
USING_NS_CC;
using namespace ui;


void gameLoad::loadGame(cocos2d::Node* rootNodeL){
    //起点加载
    auto startPosition=rootNodeL->getChildByName<ui::ImageView*>("Image_Start");
    CCSize size_start = startPosition->getContentSize();
    Vec2 position_start = startPosition->getPosition();
    START_SECTION=Section(&size_start, &position_start);
    
    
    //暂停点加载
    auto stopPosition=rootNodeL->getChildByName<ui::ImageView*>("Image_Stop");
    if(stopPosition!=NULL){
        CCSize size_stop = stopPosition->getContentSize();
        Vec2 position_stop = stopPosition->getPosition();
        STOP_SECTION=Section(&size_stop, &position_stop);
    }
    
    //终点加载
    auto destinationPosition=rootNodeL->getChildByName<ui::ImageView*>("Image_Destination");
    CCSize size_destination = destinationPosition->getContentSize();
    Vec2 position_destination = destinationPosition->getPosition();
    DESTINATION_SECTION=Section(&size_destination, &position_destination);
    
    
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
    if(Demo_jailer[index]!=NULL)
    Sprite_jailer::setJailer(index,Demo_jailer[index]);
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
        if(Demo_wall[index]!=NULL)
            Sprite_wall::setWall(index,Demo_wall[index]);
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
        if(Demo_Mouse[index]!=NULL)
            Sprite_mouse::setMouse(index,Demo_Mouse[index]);
    }while(Demo_Mouse[index]!=NULL);

    
    //主角加载
    auto Demo_protagonist = rootNodeL->getChildByName<Sprite*>("Sprite_Protagonist");
    Sprite_protagonist::setPro(0,Demo_protagonist);
    
    
    
    CCLOG("GAMELOAD is OK!!!!");
   
    
}