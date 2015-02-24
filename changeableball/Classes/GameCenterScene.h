//
//  GameCenterScene.h
//  changeableball
//
//  Created by huge on 3/9/14.
//
// game's center, ui and data update layer are all add to this scene

#ifndef __changeableball__GameCenterScene__
#define __changeableball__GameCenterScene__

#include <iostream>
#include "cocos2d.h"
#include "DataManager.h"
//#include "ControllerLayer.h"
class ControllerLayer;

class GameCenterScene:public cocos2d::CCLayer
{
    DataManager* m_data;
    ControllerLayer* m_controllerLayer;
    
    float m_delta;
    int m_score;
    int m_current_score;
    int m_timeCounter;
    
    bool m_pause;
    
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GameCenterScene);
    void startGame();
    void addScore(int nScore);
    
    void pauseGame();
    void resumeGame();
    void startTimerCounter();
    void tick(float dt);

//    void registerWithTouchDispatcher();
//    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
};

#endif /* defined(__changeableball__GameCenterScene__) */
