//
//  ballGamescene.h
//  changeableball
//
//  Created by mac on 14-9-6.
//
// 游戏开始的界面，主要有some buttons ,for example start ,pause exc

#ifndef __changeableball__ballGamescene__
#define __changeableball__ballGamescene__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "extensions/cocos-ext.h"

using namespace cocos2d::extension;

class BallGameScene : public cocos2d::CCLayer
{
    cocos2d::CCMenuItemImage * m_playnow;
    cocos2d::CCMenuItemImage * m_countdown;
    cocos2d::CCMenuItemImage * m_highscore;
    cocos2d::CCMenuItemImage * m_settings;
    cocos2d::CCMenuItemImage * m_aboutus;
    cocos2d::CCMenuItemImage * m_share;
    cocos2d::CCMenuItemImage * m_ranking;
    

public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    virtual void onEnter();
    
    void startGame();
    void playingNow(void* sender);
    void countDownModel(void* sender);
    void ranking(void* sender);
    void share(void* sender);

    void multiplePlayer(void* sender);
    void highScore(void* sender);
    void aboutus(void* sender);
    void onEnterTransitionDidFinish();
    void settings(void* sender);
    
//    void playingNow(Ref *senderz, cocos2d::extension::Control::EventType controlEvent);

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(cocos2d::CCObject* pSender);
    void musicControl(Ref* pSender);
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(BallGameScene);

    ControlButton* standardButtonWithTitle(const char * title);
    bool ControlButtoninit(Node* obj,std::vector<std::string> vec);
    void touchDownAction(Ref *senderz, Control::EventType controlEvent);
    void valueChanged(Ref* sender, Control::EventType controlEvent);
    
};

#endif /* defined(__changeableball__ballGamescene__) */
