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
    if ( CCLayerColor::initWithColor( ccc4(255,255,255,255) ) )
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
            addChild(menu);
            
            m_labelScore = CCLabelTTF::create("0","Arial",18);
            m_labelTime  = CCLabelTTF::create("60","Arial",18);
            
            m_labelScore->setAnchorPoint(ccp(0, 0.5));
            m_labelScore->setColor(ccc3(0, 0, 0));
            m_labelScore->setPosition(ccp(m_scoreItem->getContentSize().width/2+10,
                                          m_scoreItem->getContentSize().height/2));
            addChild(m_labelScore);
            m_labelTime->setAnchorPoint(ccp(0, 0.5));
            m_labelTime->setColor(ccc3(0, 0, 0));
            m_labelTime->setPosition(ccp(m_timeItem->getContentSize().width/2+10,
                                         m_timeItem->getContentSize().height/2));
            addChild(m_labelTime);
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
    
    CCMoveTo * moveTo = CCMoveTo::create(0.2, ccp(0, s.height-260));
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
    m_labelScore->runAction(CCSequence::create(CCScaleTo::create(0.3f, 2.0f),CCJumpTo::create(0.3f, m_labelScore->getPosition(), 5.0f, 3), CCScaleTo::create(0.3f, 1.0f),NULL));
    m_labelScore->setString(string->getCString());
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