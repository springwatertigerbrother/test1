//
//  ControllerLayer.h
//  changeableball
//
//  Created by huge on 3/9/14.
//
//

#ifndef __changeableball__ControllerLayer__
#define __changeableball__ControllerLayer__

#include <iostream>
#import "cocos2d.h"
#import "config.h"
USING_NS_CC;

class UpStateLayer;
//class DownStateLayer;
//class PauseLayer;
//class TopScoreLayer;

class ControllerLayer:public cocos2d::CCNode
{
    
    UpStateLayer * m_upstateLayer;
//    DownStateLayer * m_downStateLayer;
//    PauseLayer * m_pauseLayer;
//    
//    TopScoreLayer * m_topScoreLayer;
    
    bool m_pause;
public:
    virtual bool init();
    CREATE_FUNC(ControllerLayer);
    virtual void onEnter();
void gamePause();

void currentGameOver(int score);

void resetTimeString(CCString* string);
void resetScoreString(CCString* string);

void startGame();

void playerUseSkill(PLAYERTOOLTYPE skillTpye);
    void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
};

#endif /* defined(__changeableball__ControllerLayer__) */
