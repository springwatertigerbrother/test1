//
//  DataUpdateLayer.cpp
//  changeableball
//
//  Created by huge on 6/9/14.
//
//

#include "DataUpdateLayer.h"
#include "ControllerLayer.h"

bool UpStateLayer::init()
{
    if ( CCLayerColor::initWithColor( ccc4(100,255,255,255) ) )
	{
        
        CCSize s = CCDirector::sharedDirector()->getWinSize();
//         initWithColor(ccc4(198, 203, 206, 255),s.width,s.height);
        {
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
            
            m_labelScore = CCLabelTTF::create("0","Arial",30);
            m_labelTime  = CCLabelTTF::create("60","Arial",30);
            m_labelNciyuanTitle = CCLabelTTF::create("0","Arial",30);
            m_labelTotalScoreTitle = CCLabelTTF::create("0","Arial",30);
            m_labelNValue = CCLabelTTF::create("0","Arial",30);


            
            m_labelScore->setAnchorPoint(ccp(0, 0.5));
            m_labelScore->setColor(ccc3(0, 0, 0));
            m_labelScore->setPosition(ccp(100,
                                          150));
            addChild(m_labelScore);
            
            unsigned long nTotalScore = strtoul((CCUserDefault::sharedUserDefault()->getStringForKey("TOTALSCORE")).c_str(), nullptr, 10);
//            int nTotalScore = CCUserDefault::sharedUserDefault()->getStringForKey("TOTALSCORE");
            String* pTotalScoreStr = String::createWithFormat("%lu",nTotalScore);
            m_labelScore->setString(pTotalScoreStr->getCString());
            m_labelScore->setColor(ccORANGE);
            m_labelNciyuanTitle->setAnchorPoint(ccp(0, 0.5));
            m_labelNciyuanTitle->setColor(ccc3(0, 0, 0));
            m_labelNciyuanTitle->setPosition(ccp(10,
                                          80));
            m_labelNciyuanTitle->setString("您已达到的次元N是：");
            m_labelNciyuanTitle->setColor(ccBLACK);
            addChild(m_labelNciyuanTitle);
            
            m_labelNValue->setAnchorPoint(ccp(0, 0.5));
            m_labelNValue->setColor(ccc3(0, 0, 0));
            m_labelNValue->setPosition(ccp(m_labelNciyuanTitle->getPositionX()
                                           + m_labelNciyuanTitle->getContentSize().width + 5,80)
                                           );
            m_labelNValue->setColor(ccORANGE);
            String* temStr = String::createWithFormat("%d",(int)(log2(nTotalScore)));

            if (nTotalScore == 0)
            {
                temStr = String::createWithFormat("%d!",0);
            }
            m_labelNValue->setString(temStr->getCString());
            addChild(m_labelNValue);
            
            m_labelTotalScoreTitle->setAnchorPoint(ccp(0, 0.5));
            m_labelTotalScoreTitle->setColor(ccc3(0, 0, 0));
            m_labelTotalScoreTitle->setPosition(ccp(10,
                                          150));
            m_labelTotalScoreTitle->setColor(ccBLACK);
            m_labelTotalScoreTitle->setString("总分：");
            addChild(m_labelTotalScoreTitle);

            m_labelTime->setAnchorPoint(ccp(1, 0.5));
            m_labelTime->setColor(ccc3(0, 0, 0));
            m_labelTime->setPosition(ccp(m_timeItem->getPosition().x - m_timeItem->getContentSize().width/2,
                                         m_timeItem->getContentSize().height/2));
            m_labelTime->setVisible(false);
            addChild(m_labelTime);
            
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
    m_labelScore->runAction(CCSequence::create(DelayTime::create(1.5f), CCScaleTo::create(0.3f, 2.0f),CCJumpTo::create(0.3f, m_labelScore->getPosition(), 5.0f, 3), CCScaleTo::create(0.3f, 1.0f),NULL));
    m_labelScore->setString(string->getCString());
    
    String* temStr = String::createWithFormat("%d",(int)(log2(string->intValue())));
    m_labelNValue->setString(temStr->getCString());
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