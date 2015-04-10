//
//  GameCenterScene.cpp
//  changeableball
//
//  Created by huge on 3/9/14.
//
//

#include "GameCenterScene.h"
#include "ControllerLayer.h"
#include "GameOverLayer.h"
#include "DataHome.h"
#include "BuyLifeLayer.h"
#include "DataBase64.h"

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


        CCSize s = Director::getInstance()->getWinSize();
               
        m_controllerLayer = ControllerLayer::create();
        m_controllerLayer->setPosition(ccp(0, 0));
        m_controllerLayer->setAnchorPoint(ccp(0, 0));

        addChild(m_controllerLayer,2);
        
        setAnchorPoint(CCPoint(0,0));
        m_data = DataManager::create();
        this->addChild(m_data,1);

        //        bool isFirst = !UserDefault::getInstance()->getBoolForKey("isFirstOpen");
        bool isFirst = !getIntegerForKey("isFirstOpen");
        if (isFirst)
        {
            setIntegerForKey("LIFE_LIQUID", 60);
            m_data->m_helpLayer->setVisible(true);
            setIntegerForKey("isFirstOpen", 1);
            UserDefault::getInstance()->flush();
            //            UserDefault::getInstance()->setIntegerForKey("LIFE_LIQUID", 3);
            //            UserDefault::getInstance()->setBoolForKey("isFirstOpen", true);
            
        }
        
        m_score = strtoul((getStringForKey("TOTALSCORE")).c_str(), nullptr, 10);

        m_current_score = 0;
        
        buyLayer = BuyLifeLayer::create();
        this->addChild(buyLayer,10);
        buyLayer->setVisible(false);
        
        //buy life
        auto buy_life_listener = EventListenerCustom::create(BUY_LIFE_LIQUID, [=](EventCustom* event){
            int lifeLiquid = getIntegerForKey("LIFE_LIQUID");

//            int lifeLiquid = UserDefault::getInstance()->getIntegerForKey("LIFE_LIQUID");
            lifeLiquid += 10;
            setIntegerForKey("LIFE_LIQUID", lifeLiquid);

//            UserDefault::getInstance()->setIntegerForKey("LIFE_LIQUID",lifeLiquid);
            
        });

        //use life
        auto Use_life_listener = EventListenerCustom::create(USE_LIFE_LIQUID, [=](EventCustom* event){
            int lifeLiquid = getIntegerForKey("LIFE_LIQUID");

//            int lifeLiquid = UserDefault::getInstance()->getIntegerForKey("LIFE_LIQUID");
            
            if (lifeLiquid >= RIVIVE_COSUMED_DIAMOND)
            {
                m_data->m_canPlaying = true;
                buyLayer->setVisible(false);
                m_data->initElements();
                lifeLiquid -= RIVIVE_COSUMED_DIAMOND;
                
                if (lifeLiquid<0)
                {
                    lifeLiquid = 0;
                }
                setIntegerForKey("LIFE_LIQUID", lifeLiquid);

//                UserDefault::getInstance()->setIntegerForKey("LIFE_LIQUID",lifeLiquid);
                UserDefault::getInstance()->flush();
                NotificationCenter::getInstance()->postNotification(REFESH_BUYLIFE_UI);

                startGame();
            }
            else
            {
                "生命药水不够，请购买";
            }

        });
        _eventDispatcher->addEventListenerWithFixedPriority(Use_life_listener, 1);

        
        bRet = true;
    }
    while(0);
    
    return bRet;
}
void GameCenterScene::startGame()
{
    m_data->startAnimtionDisplay();
    m_data->startPlaying();
    if (DataHome::getInstance()->isCountDownModel)
    {
        startTimerCounter();
    }
}

void GameCenterScene::addScore(int nScore)
{
    m_score += nScore;
    m_current_score += nScore;
    int bestSingleScore = getIntegerForKey("SINGLE_BEST_SCORE");

//    int bestSingleScore = UserDefault::getInstance()->getIntegerForKey("SINGLE_BEST_SCORE");
    if (bestSingleScore < m_current_score)
    {
        setIntegerForKey("SINGLE_BEST_SCORE",m_current_score);

//        UserDefault::getInstance()->setIntegerForKey("SINGLE_BEST_SCORE",m_current_score);
    }

    auto num = m_score;
    char str[100];
    sprintf(str, " %lu" , num);
    setStringForKey("TOTALSCORE", str);
    
//    UserDefault::getInstance()->setStringForKey("TOTALSCORE", str);
//    CCString* scores = CCString::createWithFormat("%d",m_score);
//    m_controllerLayer->resetScoreString(StringMake(str));
    m_controllerLayer->resetScoreWithIntValue(m_score);
    m_controllerLayer->resetCurrentScoreWithIntValue(m_current_score);
}


void GameCenterScene::startTimerCounter()
{
    m_pause = false;
    m_timeCounter = DEFAULT_COUNT_TIME;
    schedule(schedule_selector(GameCenterScene::tick),1);
}

void GameCenterScene:: tick(float dt)
{
    m_controllerLayer->resetCunntDownWithIntValue(m_timeCounter);

    m_timeCounter -= 1;
    if (m_timeCounter <= 0)
    {
        unschedule(schedule_selector(GameCenterScene::tick));
//        
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sounds/xiaoxinjiayou.mp3");

        buyLayer->setVisible(true);
        m_data->m_canPlaying = false;
        log("gameover");
    }
    
    
//
//    if (!m_pause) {
//        m_delta +=dt;
//    }
//    
//    if (m_delta>=0.9999) {
//        m_delta = 0.0;
//        m_timeCounter -=1;
//        m_timeCounter = 1;
//        
////        if (m_timeCounter<=0)//zhao
////        {
////            [m_hudController resetTimeString:[NSString stringWithFormat:@"%d",m_timeCounter]];
////            [m_data moveOut];
////            //            [m_hudController gamePause];
////            [m_hudController currentGameOver:m_score];
////            [self unscheduleAllSelectors];
////        }else{
////            [m_hudController resetTimeString:[NSString stringWithFormat:@"%d",m_timeCounter]];
////        }
//    }
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
