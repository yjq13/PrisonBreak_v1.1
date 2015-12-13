//
//  setScene.cpp
//  PrisonBreak
//
//  Created by yjq131250077 on 15/9/17.
//
//

#include "aboutScene.h"
#include "OC_callFigureInfo.h"
#include "OC_callSystemInfo.h"
#include "FigureVo.h"
#include "Constant.h"
#include "Constant_Use.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;

Scene* About::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = About::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
bool About::init(){
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    setUI();
    return true;
}
void About::setUI(){
    
}