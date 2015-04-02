//
//  BuyLifeLayer.cpp
//  changeableball
//
//  Created by huge on 7/3/15.
//
//

#include "BuyLifeLayer.h"
#include "GameOverLayer.h"
#include "config.h"
bool BuyLifeLayer::init()
{
    do
    {
        if (!cocos2d::CCLayer::init()) {
            return false;
        }
        CCLayerColor* pBGLayer = CCLayerColor::create(ccc4(88,34,241,200));
        //        pBGLayer->initWithColor(ccc4(111, 155, 160, 133));
        
        pBGLayer->setAnchorPoint(CCPoint(0,0));
        addChild(pBGLayer);
        
    }
    while(0);
    return true;
}



void BuyLifeLayer::onEnter()
{
    
    CCLayer::onEnter();
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
        
    m_BuyItem = CCMenuItemImage::create("Images/startStandard.png","Images/startStandard.png", CC_CALLBACK_1(BuyLifeLayer::CallBuyLife,this));
    m_BuyItem->setScale(CC_CONTENT_SCALE_FACTOR());
    m_UseLife = CCMenuItemImage::create("Images/countdown.png","Images/countdown.png",CC_CALLBACK_1(BuyLifeLayer::CallUseLife,this));
    m_UseLife->setScale(CC_CONTENT_SCALE_FACTOR());

    m_GameOver = CCMenuItemImage::create("Images/countdown.png","Images/countdown.png",CC_CALLBACK_1(BuyLifeLayer::gameOver,this));
    m_GameOver->setScale(CC_CONTENT_SCALE_FACTOR());
    
//    m_GameOver = CCMenuItemImage::create("Images/countdown.png","Images/countdown.png",CC_CALLBACK_1(BuyLifeLayer::gameOver,this));
//    m_GameOver->setScale(CC_CONTENT_SCALE_FACTOR());
//    
//    m_GameOver = CCMenuItemImage::create("Images/countdown.png","Images/countdown.png",CC_CALLBACK_1(BuyLifeLayer::gameOver,this));
//    m_GameOver->setScale(CC_CONTENT_SCALE_FACTOR());
//    
//    m_GameOver = CCMenuItemImage::create("Images/countdown.png","Images/countdown.png",CC_CALLBACK_1(BuyLifeLayer::gameOver,this));
//    m_GameOver->setScale(CC_CONTENT_SCALE_FACTOR());
    
    CCMenu *menu = CCMenu::create(m_BuyItem,m_UseLife,m_GameOver, NULL);
    
    menu->alignItemsVerticallyWithPadding(10);
    
    menu->setPosition(ccp(size.width/2,size.height/2));
    
//    m_labelLife  = CCLabelTTF::create("60","ArialRoundedMTBold",60);
//    m_labelLife->setAnchorPoint(ccp(0.5, 0.5));
//    m_labelLife->setColor(ccRED);
//    m_labelLife->setPosition(ccp(size.width/2,size.height/2));
//    m_labelLife->setString("生命药水不够\n请购买");
//    m_labelLife->setVisible(false);
//    addChild(m_labelLife,11);
    
    this-> addChild(menu);
    
    m_iap6 = CCMenuItemImage::create("Images/startStandard.png","Images/startStandard.png", CC_CALLBACK_1(BuyLifeLayer::CallBuyLife,this));
    m_iap6->setScale(CC_CONTENT_SCALE_FACTOR());
    m_iap18  = CCMenuItemImage::create("Images/startStandard.png","Images/startStandard.png", CC_CALLBACK_1(BuyLifeLayer::gameOver,this));

    m_iap18->setScale(CC_CONTENT_SCALE_FACTOR());

    m_iap24 = CCMenuItemImage::create("Images/countdown.png","Images/countdown.png",CC_CALLBACK_1(BuyLifeLayer::gameOver,this));
    m_iap24->setScale(CC_CONTENT_SCALE_FACTOR());

    
    m_shopMenu = CCMenu::create(m_iap6,m_iap18,m_iap24, NULL);
    
    int padding = 10;
    m_shopMenu->alignItemsVerticallyWithPadding(padding);
    
    m_shopMenu->setPosition(ccp(size.width/2,2* (m_iap6->getContentSize().height + padding)));
    this-> addChild(m_shopMenu);

    
    
}
void BuyLifeLayer::CallBuyLife(void* sender)
{
    EventCustom event(BUY_LIFE_LIQUID);
    _eventDispatcher->dispatchEvent(&event);
}
void BuyLifeLayer::CallUseLife(void* sender)
{
    int lifeLiquid = UserDefault::getInstance()->getIntegerForKey("LIFE_LIQUID");
    
    if (lifeLiquid > 0)
    {
        EventCustom event(USE_LIFE_LIQUID);
        _eventDispatcher->dispatchEvent(&event);
    }
    else
    {
//        m_labelLife->setVisible(true);
//        m_labelLife->runAction(FadeOut::create(1));
//
        CCSize size = Director::getInstance()->getWinSize();
        CCLabelTTF* labelLife  = CCLabelTTF::create("60","ArialRoundedMTBold",60);
        labelLife->setAnchorPoint(ccp(0.5, 0.5));
        labelLife->setColor(ccRED);
        labelLife->setPosition(ccp(size.width/2,size.height/2));
        labelLife->setString("生命药水不够\n请购买");
//        labelLife->setVisible(false);
        addChild(labelLife,11);
        labelLife->runAction(FadeOut::create(1));
//        CallFunc* call = [](){};
        "生命药水不够，请购买";
    }
        
}
void BuyLifeLayer::gameOver(void* sender)
{
    auto scene = GameOverLayer::scene();
    Director::getInstance()->replaceScene(scene);
}