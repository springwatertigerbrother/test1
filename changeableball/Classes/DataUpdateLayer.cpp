//
//  DataUpdateLayer.cpp
//  changeableball
//
//  Created by huge on 6/9/14.
//
//

#include "DataUpdateLayer.h"
#include "ControllerLayer.h"
#include "DataHome.h"
#include "DataBase64.h"
#include "MUtils.h"
#include "buyDiamond.h"
#include "ballGamescene.h"

bool UpStateLayer::init()
{
    if ( CCLayerColor::initWithColor( ccc4(88,34,241,0) ) )
	{
        
        CCSize s = CCDirector::sharedDirector()->getWinSize();
//         initWithColor(ccc4(198, 203, 206, 255),s.width,s.height);
        {
            
            
            CCSprite* pBg = Sprite::create("Images/updatebg.png");
            pBg->setAnchorPoint(ccp(0.5,0));
            pBg->setOpacity(180);
            pBg->setPosition(ccp(s.width/2,0));
            pBg->setScale(CC_CONTENT_SCALE_FACTOR());
//            addChild(pBg);
            
            m_pAiyinsitan = Sprite::create("Images/aiyinsitanhead.png");
            m_pAiyinsitan->setPosition(ccp(s.width/2  + 200,100));
            m_pAiyinsitan->setScale(CC_CONTENT_SCALE_FACTOR());
            addChild(m_pAiyinsitan);
            
            m_scoreItem = CCMenuItemImage::create("Images/scorebutton.png", "Images/score_unselect.png",CC_CALLBACK_1 (UpStateLayer::menuBePressed,this));
            m_timeItem = CCMenuItemImage::create("Images/timebutton.png","Images/time_unselect.png", CC_CALLBACK_1(UpStateLayer::menuBePressed,this));
            
            m_scoreItem->setAnchorPoint(ccp(0, 0));
            m_timeItem->setAnchorPoint(ccp(1, 0));
            
            m_scoreItem->setPosition(ccp(0, 80));
            m_timeItem->setPosition(ccp(s.width, 80));
            
            
            CCMenu * menu = CCMenu::create(m_scoreItem, m_timeItem,NULL);
            
            menu->setPosition(ccp(0, 2));
            menu->setVisible(false);
            addChild(menu);
            
            Sprite* pFrame = Sprite::create("Images/bg_campaign_mask_blue.png");
            pFrame->setAnchorPoint(ccp(0,0.5));
            pFrame->setPosition(ccp(5,120));
            pFrame->setScale(CC_CONTENT_SCALE_FACTOR());
            addChild(pFrame);
            
            m_labelScore = CCLabelTTF::create("0","ArialRoundedMTBold",30);
            m_labelTime  = CCLabelTTF::create("60","ArialRoundedMTBold",30);
            m_labelNciyuanTitle = CCLabelTTF::create("0","ArialRoundedMTBold",30);
            m_labelTotalScoreTitle = CCLabelTTF::create("0","ArialRoundedMTBold",30);
            m_labelNValue = CCLabelTTF::create("0","ArialRoundedMTBold",30);
            m_labelCurrentNciyuanTitle = CCLabelTTF::create("0","ArialRoundedMTBold",30);
            m_labelCurrentNValue = CCLabelTTF::create("0","ArialRoundedMTBold",30);
            m_labelCurrentScoreTitle = CCLabelTTF::create("当前能量：","ArialRoundedMTBold",30);
            m_labelCurrentScoreValue = CCLabelTTF::create("0","ArialRoundedMTBold",30);
            m_labelCountDown = CCLabelTTF::create("300","ArialRoundedMTBold",50);
           
            m_labelLevel = CCLabelTTF::create("level: 1","ArialRoundedMTBold",50);
            m_labelLevel->setPosition(ccp(s.width/2,-70));
            int currentValue = getIntegerForKey("level");
            String* scoreStr = String::createWithFormat("level: %d",currentValue);
            m_labelLevel->setString(scoreStr->getCString());
            m_labelLevel->setScale(0.01);
            addChild(m_labelLevel);
            
            std::string nicyuantitleStr;
            std::string totalScoreTitleStr;
            std::string currentNciyuanTitleStr;
            std::string currentEnergyStr;
            std::string backStr;
            nicyuantitleStr = "total dimension:";
            totalScoreTitleStr = "total energy:";
            currentNciyuanTitleStr = "current power:";
            currentEnergyStr = "current energy:";
            
            LanguageType currentLanguageType = CCApplication::sharedApplication()->getCurrentLanguage();
            switch (currentLanguageType)
            {
                case cocos2d::LanguageType::CHINESE:
                    nicyuantitleStr = "累计次元：";
                    totalScoreTitleStr = "总能量：";
                    currentNciyuanTitleStr = "当前战斗力：";
                    currentEnergyStr = "当前能量：";
                    backStr = "返回";
                    break;
                case cocos2d::LanguageType::ENGLISH:
                    nicyuantitleStr = "total dimension:";
                    totalScoreTitleStr = "total energy:";
                    currentNciyuanTitleStr = "current power:";
                    currentEnergyStr = "current energy:";
                    backStr = "back";
                    break;
                default:
                    break;
            }
            
//            auto itemback = MenuItemFont::create(backStr.c_str(), CC_CALLBACK_1(UpStateLayer::back, this));
//            itemback->setFontSize(30);
//            itemback->setScale(CC_CONTENT_SCALE_FACTOR());
//            CCMenu *menuBack = CCMenu::create(itemback, NULL);
//            menuBack->alignItemsVerticallyWithPadding(5);
//            
//            menuBack->setPosition(ccp(s.width/2 + 80,150));
//            this-> addChild(menuBack);

            
            unsigned long nTotalScore = strtoul((getStringForKey("TOTALSCORE")).c_str(), nullptr, 10);
//            int nTotalScore = CCUserDefault::sharedUserDefault()->getStringForKey("TOTALSCORE");
           
            // total
            String* pTotalScoreStr = String::createWithFormat("%lu",nTotalScore);
            m_labelScore->setString(pTotalScoreStr->getCString());
            m_labelScore->setColor(ccORANGE);
            m_labelTotalScoreTitle->setAnchorPoint(ccp(0, 0.5));
            m_labelTotalScoreTitle->setColor(ccc3(0, 0, 0));
            m_labelTotalScoreTitle->setPosition(ccp(20,
                                                    160));
            m_labelTotalScoreTitle->setColor(ccBLACK);
            m_labelTotalScoreTitle->setString(totalScoreTitleStr.c_str());
            m_labelTotalScoreTitle->setColor(ccWHITE);
            addChild(m_labelTotalScoreTitle);
            
            m_labelScore->setAnchorPoint(ccp(0, 0.5));
            m_labelScore->setPosition(ccp(m_labelTotalScoreTitle->getPositionX()
                                          + m_labelTotalScoreTitle->getContentSize().width,
                                          160));
            addChild(m_labelScore);
            
            m_labelNciyuanTitle->setAnchorPoint(ccp(0, 0.5));
            m_labelNciyuanTitle->setColor(ccc3(0, 0, 0));
            m_labelNciyuanTitle->setPosition(ccp(20,
                                          110));
            m_labelNciyuanTitle->setString(nicyuantitleStr.c_str());
            m_labelNciyuanTitle->setColor(ccWHITE);
            addChild(m_labelNciyuanTitle);
            
            m_labelNValue->setAnchorPoint(ccp(0, 0.5));
            m_labelNValue->setColor(ccc3(0, 0, 0));
            m_labelNValue->setPosition(ccp(m_labelNciyuanTitle->getPositionX()
                                           + m_labelNciyuanTitle->getContentSize().width + 5,110)
                                           );
            m_labelNValue->setColor(ccORANGE);
            
            int nValue = calculate_score(nTotalScore,0);
            String* temStr = String::createWithFormat("%d",nValue);

            if (nTotalScore == 0)
            {
                temStr = String::createWithFormat("%d!",0);
            }
            m_labelNValue->setString(temStr->getCString());
            addChild(m_labelNValue);
            
            
            m_labelCurrentNciyuanTitle->setAnchorPoint(ccp(0, 0.5));
            m_labelCurrentNciyuanTitle->setColor(ccc3(0, 0, 0));
            m_labelCurrentNciyuanTitle->setPosition(ccp(20,
                                                 60));
            m_labelCurrentNciyuanTitle->setString(currentNciyuanTitleStr);
            m_labelCurrentNciyuanTitle->setColor(ccWHITE);
            addChild(m_labelCurrentNciyuanTitle);
            
            m_labelCurrentNValue->setAnchorPoint(ccp(0, 0.5));
            m_labelCurrentNValue->setColor(ccc3(0, 0, 0));
            m_labelCurrentNValue->setPosition(ccp(m_labelCurrentNciyuanTitle->getPositionX()
                                           + m_labelCurrentNciyuanTitle->getContentSize().width + 5,60)
                                       );
            m_labelCurrentNValue->setColor(ccORANGE);
            
            if (nTotalScore == 0)
            {
                temStr = String::createWithFormat("%d!",0);
            }
            m_labelNValue->setString(temStr->getCString());
            addChild(m_labelCurrentNValue);

            
            //count down
            CCSprite* pClock = Sprite::create("Images/clock.png");
            pClock->setPosition(ccp(s.width - 250,10));
            pClock->setScale(CC_CONTENT_SCALE_FACTOR());
            addChild(pClock);
            
            m_labelCountDown->setAnchorPoint(ccp(0.0, 0.5));
            m_labelCountDown->setColor(ccc3(0, 0, 0));
            m_labelCountDown->setPosition(ccp(s.width - 220,10));
            //            m_labelNciyuanTitle->setString("您已达到的次元N是：");
            m_labelCountDown->setColor(ccRED);
            addChild(m_labelCountDown);

            m_labelCountDown->setVisible(DataHome::getInstance()->isCountDownModel);
            pClock->setVisible(DataHome::getInstance()->isCountDownModel);
            
            // current
            m_labelCurrentScoreTitle->setAnchorPoint(ccp(0, 0.5));
            m_labelCurrentScoreTitle->setColor(ccWHITE);
            m_labelCurrentScoreTitle->setPosition(ccp(20,
                                                 210));
            m_labelCurrentScoreTitle->setString(currentEnergyStr.c_str());
//            m_labelNciyuanTitle->setString("您已达到的次元N是：");
//            m_labelCurrentScoreTitle->setColor(ccBLACK);
            addChild(m_labelCurrentScoreTitle);
            
            m_labelCurrentScoreValue->setAnchorPoint(ccp(0, 0.5));
            m_labelCurrentScoreValue->setColor(ccc3(0, 0, 0));
            m_labelCurrentScoreValue->setPosition(ccp(m_labelCurrentScoreTitle->getPositionX()
                                           + m_labelCurrentScoreTitle->getContentSize().width + 5,210)
                                       );
            m_labelCurrentScoreValue->setColor(ccORANGE);
//            String* currentScoreStr = String::createWithFormat("%d",(int)(log2(nTotalScore)));
//            
//            if (nTotalScore == 0)
//            {
//                temStr = String::createWithFormat("%d!",0);
//            }
//            m_labelNValue->setString(currentScoreStr->getCString());
            addChild(m_labelCurrentScoreValue);
            
            m_labelTime->setAnchorPoint(ccp(1, 0.5));
            m_labelTime->setColor(ccc3(0, 0, 0));
            m_labelTime->setPosition(ccp(m_timeItem->getPosition().x - m_timeItem->getContentSize().width/2,
                                         m_timeItem->getContentSize().height/2));
            m_labelTime->setVisible(false);
            addChild(m_labelTime);
           
            
            Sprite* pDiamond = Sprite::create("Images/icon_cash_l.png");
            pDiamond->setAnchorPoint(ccp(0.5,0.5));
            pDiamond->setScale(CC_CONTENT_SCALE_FACTOR());
            pDiamond->setPosition(ccp(100,-15));
            addChild(pDiamond);
            
            auto buyDiamond = CCMenuItemImage::create("Images/icon_cash_l.png","Images/icon_cash_l.png",CC_CALLBACK_1(UpStateLayer::buyDiamond,this));
            buyDiamond->setScale(CC_CONTENT_SCALE_FACTOR());
            CCMenu* pMenu = CCMenu::create(buyDiamond, NULL);
            pMenu->alignItemsHorizontallyWithPadding(10);
            //    pItem1->setFontSize(30);
            //    pItem2->setFontSize(30);
            
            pMenu->setPosition(ccp(100,-15));
            addChild(pMenu);
            
            m_labelDiamond = CCLabelTTF::create("0","ArialRoundedMTBold",50);
            m_labelDiamond->setAnchorPoint(ccp(0, 0.5));
            m_labelDiamond->setColor(ccc3(255, 255, 255));
            m_labelDiamond->setPosition(ccp(pDiamond->getPosition().x + pDiamond->getContentSize().width/2 + 15,-15));
            addChild(m_labelDiamond);
            
            
            MenuItemFont::setFontName("American Typewriter");
            MenuItemFont::setFontSize(18);
            auto title1 = MenuItemFont::create("Sound");
            title1->setEnabled(false);
            MenuItemFont::setFontName( "fonts/Marker Felt.ttf" );
            MenuItemFont::setFontSize(34);
            auto item1 = MenuItemToggle::createWithCallback( CC_CALLBACK_1(UpStateLayer::musicControl, this),
                                                            MenuItemFont::create( "On" ),
                                                            MenuItemFont::create( "Off"),
                                                            nullptr );
            item1->setEnabled(true);
            auto musciMenu = Menu::create(item1, nullptr);
            musciMenu->setPosition(ccp(s.width - 50,10));
            
//            musciMenu->alignItemsInColumns(2, 2, 2, 2, 1, NULL);
            musciMenu->setVisible(false);
            addChild( musciMenu );
            
//            m_labelTime-
//            m_timeItem->addChild(m_labelTime,11);
//            m_scoreItem->addChild(m_labelScore ,11);
            
            setVisible(true);
            reload(nullptr);
            NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(UpStateLayer::reload), REFESH_USE_TOOL, NULL);

        }

		return true;
	}
	else
	{
		return false;
	}
    
}


void UpStateLayer::startAnimationDisplay()
{
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    setVisible(true);
    
    setAnchorPoint(ccp(0, 0));
    setPosition(ccp(0, s.height));
    
    CCMoveTo * moveTo = CCMoveTo::create(0.2, ccp(0, s.height-360));
    CCMoveTo * moveTo2 = CCMoveTo::create(0.2, ccp(0, s.height-243));
    CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(UpStateLayer:: AfterStartAnimationDisplayCall));
    
    runAction(CCSequence::create(moveTo, moveTo2, call, NULL));
}
void UpStateLayer::AfterStartAnimationDisplayCall()
{
    ControllerLayer * dhc = (ControllerLayer*)getParent();
    dhc->startGame();
}
void UpStateLayer::resetScoreString(CCString*string)
{
//    m_labelScore->runAction(CCSequence::create(DelayTime::create(1.5f), CCScaleTo::create(0.3f, 2.0f),CCJumpTo::create(0.3f, m_labelScore->getPosition(), 5.0f, 3), CCScaleTo::create(0.3f, 1.0f),NULL));
    m_labelScore->setString(string->getCString());
    
    String* temStr = String::createWithFormat("%d",(unsigned int)(log2(string->uintValue())));
    m_labelNValue->setString(temStr->getCString());
}

void UpStateLayer::resetScoreWithIntValue(unsigned long nValue)
{
//    m_labelScore->runAction(CCSequence::create(DelayTime::create(1.5f), CCScaleTo::create(0.3f, 2.0f), CCScaleTo::create(0.3f, 1.0f),NULL));
    
    
    
    unsigned long nTotalScore = strtoul((getStringForKey("TOTALSCORE")).c_str(), nullptr, 10);
    int nOldValue = calculate_score(nTotalScore,0);
    int nCurrentValue = calculate_score(nValue,0);
    
    
//    int currentValue = (unsigned int)(log(string->uintValue())/log(2));
    
    if (nCurrentValue > nOldValue)
    {
        int level = getIntegerForKey("level");
        level++;
        String* levelStr = String::createWithFormat("level: %d",level);
        m_labelLevel->setString(levelStr->getCString());
        auto action1 = ScaleTo::create(1, 1.5);
        auto action2 = ScaleTo::create(0.5, 1);
        auto action3 = ScaleTo::create(0.01, 0.01);
        m_labelLevel->runAction(Sequence::create(action1,action2,action3, NULL));
        setIntegerForKey("level",level);
    }

    
    String* scoreStr = String::createWithFormat("%d",nValue);
    m_labelScore->setString(scoreStr->getCString());

    String* temStr = String::createWithFormat("%d",(unsigned int)(log(nValue)/log(2)));
    m_labelNValue->setString(temStr->getCString());
    
    auto rotation = RotateBy::create(0.1, 30);
    auto aiyinsitanswing = Sequence::create(rotation,rotation->reverse(), NULL);
    m_pAiyinsitan->stopAllActions();
    m_pAiyinsitan->runAction(CCRepeat::create(aiyinsitanswing,2));

    
    auto num = nValue;
    char str[100];
    sprintf(str, " %lu" , num);
    setStringForKey("TOTALSCORE", str);
}
void UpStateLayer::resetCurrentScoreWithIntValue(unsigned long int nValue)
{
    String* temStr = String::createWithFormat("%lu",nValue);
    m_labelCurrentScoreValue->setString(temStr->getCString());
    
    int nciValue = calculate_score(nValue,0);
    String* currentNvalueStr = String::createWithFormat("%d 次元",nciValue);
    m_labelCurrentNValue->setString(currentNvalueStr->getCString());
}

void UpStateLayer::resetCunntDownWithIntValue(unsigned long int nValue)
{
    String* temStr = String::createWithFormat("%lu",nValue);
    m_labelCountDown->setString(temStr->getCString());
}
void UpStateLayer::resetTimeString(CCString*string)
{
    m_labelTime->setString(string->getCString());
}

void UpStateLayer::menuBePressed(Ref* pSender)
{
    if (getParent())
    {
        ControllerLayer *hc = (ControllerLayer*)getParent();
        hc-> gamePause();
    }
}

void UpStateLayer::musicControl(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()-> pauseAllEffects();
}

void UpStateLayer::reload(Ref* obj)
{
    int lifeLiquid = getIntegerForKey("LIFE_LIQUID");
    
    //    int lifeLiquid = UserDefault::getInstance()->getIntegerForKey("LIFE_LIQUID");
    char tempStr[10];
    sprintf(tempStr,"%d", lifeLiquid);
    m_labelDiamond->setString(tempStr);
}

void UpStateLayer::buyDiamond(void* sender)
{
    NotificationCenter::getInstance()->postNotification(DISPLAY_BUY_DIAMOND);
//
//    
//    auto buyLayer = buyDiamond)::create();
//    addChild(buyLayer);
}
void UpStateLayer::back(void* sender)
{
    auto scene = BallGameScene::scene();
    Director::getInstance()->replaceScene(scene);
}
//void removeSelf(Ref* pNode)
//{
//    if (pNode) {
//        pNode->removeFromParentAndCleanup(true);
//    }
//}