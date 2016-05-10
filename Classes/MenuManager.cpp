//
//  Menu_Action.cpp
//  PrisonBreak_v1.1
//
//  Created by 马长松 on 16/1/24.
//
//
#include "cocos2d.h"
#include "Constant_Use.h"
#include "SchedulerManager.h"
#include "MenuManager.h"
#include "ListenerManager.h"
#include "GameCommonScene.h"
#include "SelectScene_Detail.h"
#include "ButtonManager.h"
USING_NS_CC;

Node* MenuManager::create_Menu(int MenuNumber){
    Node* Menu;
    switch(MenuNumber){
        case FAIL_LAYER:{
            Menu = CSLoader::createNode("res/Game/Other/Layer_Fail.csb");
            isPause = true;
            setFailConfig(Menu);
            break;
        }
        case SUCCESS_LAYER:{
            Menu = CSLoader::createNode("res/Game/Other/Layer_Success.csb");
            isPause = true;
            setSuccessConfig(Menu);
            break;
        }
        case STOP_LAYER:{
            Menu = CSLoader::createNode("res/Game/Other/Layer_Stop.csb");
            isPause = true;
            setPauseConfig(Menu);
            break;
        }
    }
        return Menu;
}


void MenuManager::move_in(cocos2d::Node *menu){
  //Movein
    MoveTo* Movein_1=MoveTo::create(0.3f,Point(0,0));
    EaseExponentialIn* moveIn_1 = EaseExponentialIn::create(Movein_1);
    MoveTo* Movein_2=MoveTo::create(0.3f,Point(0,70));
    EaseExponentialOut* moveIn_2 = EaseExponentialOut::create(Movein_2);
    MoveTo* Movein_3=MoveTo::create(0.2f,Point(0,0));
    EaseExponentialIn* moveIn_3 = EaseExponentialIn::create(Movein_3);
    auto ac=Sequence::create(moveIn_1,moveIn_2,moveIn_3, NULL);
    menu->runAction(ac);
}

void MenuManager::move_out(cocos2d::Node *menu){
    MoveTo* Moveout=MoveTo::create(0.3f,Point(0,VISIBLE_SIZE.height));
    EaseExponentialOut* moveOut = EaseExponentialOut::create(Moveout);
    
    auto ac = Sequence::create(moveOut, NULL);
    menu->runAction(ac);
}

void MenuManager::setPauseConfig(Node* menu){
    
    auto Button_Resume_pause = menu->getChildByName<ui::Button*>("Button_Resume");
    
    Button_Resume_pause->addClickEventListener(CC_CALLBACK_1(MenuManager::pauseCallresume,this,menu));
    
    auto Button_Retry_pause = menu->getChildByName<ui::Button*>("Button_Retry");
    
    Button_Retry_pause->addClickEventListener(CC_CALLBACK_1(MenuManager::Callrestart,this,menu));
    
    auto Button_Back_pause = menu->getChildByName<ui::Button*>("Button_Back");
    
    Button_Back_pause->addClickEventListener(CC_CALLBACK_1(MenuManager::menuCloseCallback,this,menu));
    
    menu->setContentSize(VISIBLE_SIZE);
    
    ui::Helper::doLayout(menu);
    
    menu->setPositionY(VISIBLE_SIZE.height);
    
}


void MenuManager::setFailConfig(Node* menu){
    
    auto Button_Back_Fail = menu->getChildByName<ui::Button*>("Button_Back");
    
    Button_Back_Fail->addClickEventListener(CC_CALLBACK_1(MenuManager::menuCloseCallback,this,menu));

    auto Button_Retry_Fail = menu->getChildByName<ui::Button*>("Button_Retry");
    
    Button_Retry_Fail->addClickEventListener(CC_CALLBACK_1(MenuManager::Callrestart,this,menu));

    menu->setContentSize(VISIBLE_SIZE);
    
    ui::Helper::doLayout(menu);
    
    menu->setPositionY(VISIBLE_SIZE.height);
    
}

void MenuManager::setSuccessConfig(Node* menu){
    
    auto Button_Back_Success = menu->getChildByName<ui::Button*>("Button_Back");
    
    Button_Back_Success->addClickEventListener(CC_CALLBACK_1(MenuManager::menuCloseCallback,this,menu));
    
    auto Button_Retry_Success = menu->getChildByName<ui::Button*>("Button_Retry");
    
    Button_Retry_Success->addClickEventListener(CC_CALLBACK_1(MenuManager::Callrestart,this,menu));
    
    auto Button_Next_Success = menu->getChildByName<ui::Button*>("Button_Next");
    
    Button_Next_Success->addClickEventListener(CC_CALLBACK_1(MenuManager::Callrestart,this,menu));//下一关还没实现，之后搞定
        
    menu->setContentSize(VISIBLE_SIZE);
    
    ui::Helper::doLayout(menu);
    
    menu->setPositionY(VISIBLE_SIZE.height);
    
}


void MenuManager::pauseCallresume(Ref* pSender,Node* layer){
    TIMEEND = getTime();
    
    SchedulerManager::resumePro();
    SchedulerManager::resumeTimeLine();
    ListenerManager::resumeListenerPro();
    ButtonManager::resumeButton();
    
    MenuManager::move_out(layer);
    
}

void MenuManager::Callrestart(Ref *pSender,Node* layer){
    if(BUTTON_LOCK==false){
        BUTTON_LOCK= true;
        //menuCloseCallback(pSender);
        MenuManager::move_out(layer);
        if(isPause)
            SchedulerManager::resumePro();
        
        auto sceneNew = Game::createScene();
        
        Director::getInstance()->replaceScene(sceneNew);
        BUTTON_LOCK = false;
    }
}

void MenuManager::menuCloseCallback(Ref* pSender,Node* layer)
{
    if(BUTTON_LOCK==false){
        BUTTON_LOCK= true;
        if(isPause)
            SchedulerManager::resumePro();

        //auto Scene =  Select_Detail::createScene();
        //auto transition=TransitionPageTurn::create(0.1f, Scene, false);
        MenuManager::move_out(layer);
        // moveaction->target
        Director::getInstance()->popScene();
        
        auto sceneNew = Select_Detail::createScene();
        
        Director::getInstance()->replaceScene(sceneNew);
    }
    //#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
    //#endif
}