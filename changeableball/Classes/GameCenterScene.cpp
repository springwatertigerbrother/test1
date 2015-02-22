//
//  GameCenterScene.cpp
//  changeableball
//
//  Created by huge on 3/9/14.
//
//

#include "GameCenterScene.h"
#include "ControllerLayer.h"

using namespace cocos2d;

CCScene* GameCenterScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = NULL;
    
    do
    {
        scene = CCScene::create();
        CC_BREAK_IF(! scene);
        
        // 'layer' is an autorelease object
        GameCenterScene *layer = GameCenterScene::create();
        
        CC_BREAK_IF(! layer);

        layer->retain();
        // add layer as a child to scene
        scene->addChild(layer);
        
    }while (0);
    
    
    
    // return the scene
    return scene;
}

bool GameCenterScene::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(! CCLayer::create() );

        m_controllerLayer = ControllerLayer::create();
        m_controllerLayer->setPosition(ccp(0, 0));
        m_controllerLayer->setAnchorPoint(ccp(0, 0));

        addChild(m_controllerLayer);
        
        setAnchorPoint(CCPoint(0,0));
        m_data = DataManager::create();
        this->addChild(m_data);

        bRet = true;
    }
    while(0);
    
    return bRet;
}
void GameCenterScene::startGame()
{
    m_data->startAnimtionDisplay();
    m_data->startPlaying();
    startTimerCounter();
}
void GameCenterScene::addScore(int nScore)
{
    m_score += nScore;
    CCString* scores = CCString::createWithFormat("%d",m_score);
    m_controllerLayer->resetScoreString(scores);
}


void GameCenterScene::startTimerCounter()
{
    m_pause = false;
    m_timeCounter = 60;
    schedule(schedule_selector(GameCenterScene::tick));

}

void GameCenterScene:: tick(float dt)
{
    
    if (!m_pause) {
        m_delta +=dt;
    }
    
    if (m_delta>=0.9999) {
        m_delta = 0.0;
        m_timeCounter -=1;
        m_timeCounter = 1;
        
//        if (m_timeCounter<=0)//zhao
//        {
//            [m_hudController resetTimeString:[NSString stringWithFormat:@"%d",m_timeCounter]];
//            [m_data moveOut];
//            //            [m_hudController gamePause];
//            [m_hudController currentGameOver:m_score];
//            [self unscheduleAllSelectors];
//        }else{
//            [m_hudController resetTimeString:[NSString stringWithFormat:@"%d",m_timeCounter]];
//        }
    }
}



void GameCenterScene::pauseGame()
{
    m_pause = true;
    m_data->moveOut();
}

void GameCenterScene::resumeGame()
{
    m_pause = false;
    m_data->moveIn();
}

//
//void GameCenterScene:: playerUsedToolDisappear(PLAYERTOOLTYPE type)
//{
//    
//    if (type == tooltime) {
//        
//    }else{
//        if (type == toolDisappearAll) {
//            if([m_data allDrawNodeBeSelected:YES]){
//                
//            }
//        }else{
//            
//            if([m_data allDrawNodeBeSelected:NO]){
//                
//            }
//        }
//    }
//}

//virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
