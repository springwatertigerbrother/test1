//
//  ControllerLayer.cpp
//  changeableball
//
//  Created by huge on 3/9/14.
//
//

#include "ControllerLayer.h"
#include "DataUpdateLayer.h"
#include "GameCenterScene.h"

bool ControllerLayer::init()
{
    
    if (CCNode::init())
    {
        
//        m_downStateLayer    = [DownStateLayer node];
        m_upstateLayer      = UpStateLayer::create();
//        m_pauseLayer        = [PauseLayer node];
//        m_topScoreLayer     = [TopScoreLayer node];
        
        
//        addChild(m_downStateLayer z:2];
//        CCLayerColor * pLayer = CCLayerColor::create(ccc4(111,111,111,111),111,111);
//        pLayer->setPosition(ccp(0, 0));
        m_upstateLayer->setAnchorPoint(ccp(0, 0));
//        addChild(pLayer);
        m_upstateLayer->setPosition(ccp(0, 0));
         addChild(m_upstateLayer,2);
//        [self addChild:m_pauseLayer z:1];
//        [self addChild:m_topScoreLayer];
        return true;
    }
    return false;
}

void ControllerLayer::onEnter()
{
    CCNode:: onEnter();
    
    m_upstateLayer->startAnimationDisplay();
//    m_downStateLayer startAnimationDisplay];
}

void ControllerLayer::startGame()
{
   
    if (getParent()) {
        GameCenterScene * dps = (GameCenterScene*)getParent();
        dps->startGame();
    }
}

void ControllerLayer::gamePause()
{
    CCScene * playingScene = GameCenterScene::scene();
    CCDirector::sharedDirector()->replaceScene(playingScene);
//
//    if (m_pause) {
//        if (getParent()) {
////            m_pauseLayer->setVisible(false);
//            GameCenterScene * playing = (GameCenterScene*)getParent();
//            playing->resumeGame();
//            m_pause = false;
//        }
//    }else{
//        if (getParent()) {
////            m_pauseLayer->startAnimationDiaplay();
//            GameCenterScene * playing = (GameCenterScene*)getParent();
//            playing->pauseGame();
//            m_pause = true;
//        }
//    }
}

void ControllerLayer:: currentGameOver(int score)
{
//    m_downStateLayer setVisible:false];
    m_upstateLayer->setVisible(false);
//    [m_pauseLayer setVisible:false];
//    [m_topScoreLayer startAnimationDisplay:score];
}


void ControllerLayer::resetTimeString(CCString*string)
{
    m_upstateLayer->resetTimeString(string);
}
void ControllerLayer::resetScoreString(CCString* string)
{
    m_upstateLayer-> resetScoreString(string);
}

void ControllerLayer::resetScoreWithIntValue(unsigned long int nValue)
{
    m_upstateLayer-> resetScoreWithIntValue(nValue);
}
void ControllerLayer::resetCurrentScoreWithIntValue(unsigned long int nValue)
{
    m_upstateLayer-> resetCurrentScoreWithIntValue(nValue);
}

void ControllerLayer::resetCunntDownWithIntValue(unsigned long int nValue)
{
    m_upstateLayer->resetCunntDownWithIntValue(nValue);
}
void ControllerLayer::playerUseSkill(PLAYERTOOLTYPE skillTpye)
{
    if (getParent()) {
        GameCenterScene * playing = (GameCenterScene*)getParent();
        if (playing) {
//            playing playerUsedToolDisappear:skillTpye];
        }
    }
}


void ControllerLayer::registerWithTouchDispatcher()
{
//    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);

}
 bool ControllerLayer:: ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCLOG("fsfsddsdsffsdf");
    return false;
}
