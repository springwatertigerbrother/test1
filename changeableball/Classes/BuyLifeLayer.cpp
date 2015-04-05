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
#include "IOSiAP_Bridge.h"

enum buttonTag
{
    rivive_button_tag = 1,
    gameOver_button_tag = 2,
    
    buy6_tag = 6,
    buy12_tag = 12,
    buy18_tag = 18,
    buy68_tag = 68
};

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

void BuyLifeLayer::reload(Ref* obj)
{
    int lifeLiquid = UserDefault::getInstance()->getIntegerForKey("LIFE_LIQUID");
    char tempStr[10];
    sprintf(tempStr,"%d", lifeLiquid);
    m_labelDiamond->setString(tempStr);
    
    m_shopMenu->setEnabled(true);
    pLabelUpload->setVisible(false);
}

void BuyLifeLayer::onEnter()
{
    
    CCLayer::onEnter();
    
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(BuyLifeLayer::reload), REFESH_BUYLIFE_UI, NULL);

    CCSize size = CCDirector::sharedDirector()->getWinSize();
        
//    m_BuyItem = CCMenuItemImage::create("Images/startStandard.png","Images/startStandard.png", CC_CALLBACK_1(BuyLifeLayer::CallBuyLife,this));
//    m_BuyItem->setScale(CC_CONTENT_SCALE_FACTOR());
//    m_BuyItem->setTag(0);
//    
//    CCLabelTTF* testLabel1 = CCLabelTTF::create("复活 \n revive","ArialRoundedMTBold",16);
//    testLabel1->setPosition(ccp(m_BuyItem->getContentSize().width/2,m_BuyItem->getContentSize().height/2));
//    m_BuyItem->addChild(testLabel1);
//    
    
    m_UseLife = CCMenuItemImage::create("Images/fuhuo.png","Images/fuhuo.png",CC_CALLBACK_1(BuyLifeLayer::CallUseLife,this));
    m_UseLife->setScale(CC_CONTENT_SCALE_FACTOR());
    m_UseLife->setTag(rivive_button_tag);
//    CCLabelTTF* testLabel2 = CCLabelTTF::create("复活 \n revive","ArialRoundedMTBold",16);
//    testLabel2->setPosition(ccp(m_BuyItem->getContentSize().width/2,m_BuyItem->getContentSize().height/2));
//    m_UseLife->addChild(testLabel2);

    m_GameOver = CCMenuItemImage::create("Images/gameover.png","Images/gameover.png",CC_CALLBACK_1(BuyLifeLayer::gameOver,this));
    m_GameOver->setScale(CC_CONTENT_SCALE_FACTOR());
    
//    m_GameOver = CCMenuItemImage::create("Images/countdown.png","Images/countdown.png",CC_CALLBACK_1(BuyLifeLayer::gameOver,this));
//    m_GameOver->setScale(CC_CONTENT_SCALE_FACTOR());
//    
//    m_GameOver = CCMenuItemImage::create("Images/countdown.png","Images/countdown.png",CC_CALLBACK_1(BuyLifeLayer::gameOver,this));
//    m_GameOver->setScale(CC_CONTENT_SCALE_FACTOR());
//    
//    m_GameOver = CCMenuItemImage::create("Images/countdown.png","Images/countdown.png",CC_CALLBACK_1(BuyLifeLayer::gameOver,this));
//    m_GameOver->setScale(CC_CONTENT_SCALE_FACTOR());
    
//    CCMenu *menu = CCMenu::create(m_BuyItem,m_UseLife,m_GameOver, NULL);
//    
//    menu->alignItemsVerticallyWithPadding(10);
//    
//    menu->setPosition(ccp(size.width/2,size.height/2));
    
//    m_labelLife  = CCLabelTTF::create("60","ArialRoundedMTBold",60);
//    m_labelLife->setAnchorPoint(ccp(0.5, 0.5));
//    m_labelLife->setColor(ccRED);
//    m_labelLife->setPosition(ccp(size.width/2,size.height/2));
//    m_labelLife->setString("生命药水不够\n请购买");
//    m_labelLife->setVisible(false);
//    addChild(m_labelLife,11);
    
    
    m_iap6 = CCMenuItemImage::create("Images/zuan100.png","Images/zuan100.png", CC_CALLBACK_1(BuyLifeLayer::CallBuyLife,this));
    m_iap6->setScale(CC_CONTENT_SCALE_FACTOR()*0.8);
    m_iap6->setTag(buy6_tag);
//    CCLabelTTF* testLabel = CCLabelTTF::create("复活 \n revive","ArialRoundedMTBold",16);
//    testLabel->setPosition(ccp(m_iap6->getContentSize().width/2,m_iap6->getContentSize().height/2));
//    m_iap6->addChild(testLabel);
    m_iap18  = CCMenuItemImage::create("Images/zuan500.png","Images/zuan500.png", CC_CALLBACK_1(BuyLifeLayer::CallBuyLife,this));
    m_iap18->setScale(CC_CONTENT_SCALE_FACTOR()*0.8);
    m_iap18->setTag(buy18_tag);

    m_iap68 = CCMenuItemImage::create("Images/zuan2000.png","Images/zuan2000.png",CC_CALLBACK_1(BuyLifeLayer::CallBuyLife,this));
    m_iap68->setScale(CC_CONTENT_SCALE_FACTOR()*0.8);
    m_iap68->setTag(buy68_tag);
    
//    auto item7= MenuItemFont::create("Quit", CC_CALLBACK_1(BuyLifeLayer::CallBuyLife, this));

//    CCMenu *menu = CCMenu::create(m_UseLife,m_iap6,m_iap18,m_iap68, m_GameOver, NULL);
    m_shopMenu = CCMenu::create(m_UseLife,m_iap6,m_iap18,m_iap68, m_GameOver, NULL);
    m_shopMenu->alignItemsVerticallyWithPadding(5);
    
    m_shopMenu->setPosition(ccp(size.width/2,size.height/2));
    this-> addChild(m_shopMenu);
    
    Sprite* pDiamond = Sprite::create("Images/icon_cash_l.png");
    pDiamond->setAnchorPoint(ccp(1,1));
    pDiamond->setScale(CC_CONTENT_SCALE_FACTOR());
    pDiamond->setPosition(ccp(size.width*0.5 - 15,size.height-5));
    addChild(pDiamond);
    
    m_labelDiamond = CCLabelTTF::create("60","ArialRoundedMTBold",60);
    m_labelDiamond->setAnchorPoint(ccp(0,1));
    m_labelDiamond->setPosition(ccp(size.width*0.5 ,size.height-10));
    
    int lifeLiquid = UserDefault::getInstance()->getIntegerForKey("LIFE_LIQUID");
    char tempStr[10];
    sprintf(tempStr,"%d", lifeLiquid);
    m_labelDiamond->setString(tempStr);
    addChild(m_labelDiamond);
    
    CCLabelTTF* pConsumedDiamond = CCLabelTTF::create("30","ArialRoundedMTBold",30);
    pConsumedDiamond->setAnchorPoint(ccp(0.5,1));
    pConsumedDiamond->setPosition(ccp(size.width*0.5,size.height-100));
    
    sprintf(tempStr,"小伙伴使用%d钻石复活吧 ^O^", RIVIVE_COSUMED_DIAMOND);
    pConsumedDiamond->setString(tempStr);
    addChild(pConsumedDiamond);
    pConsumedDiamond->runAction(CCRepeatForever::create(Sequence::create(ScaleTo::create(0.5, 0.5), ScaleTo::create(0.5,1),DelayTime::create(1),NULL)));
    
//    m_shopMenu = CCMenu::create(m_iap6,m_iap18,m_iap24, NULL);
//    
//    int padding = 10;
//    m_shopMenu->alignItemsVerticallyWithPadding(padding);
//    
//    m_shopMenu->setPosition(ccp(size.width/2,2* (m_iap6->getContentSize().height + padding)));
//    this-> addChild(m_shopMenu);

    pLabelUpload = CCLabelTTF::create("正在去往商店。。。","ArialRoundedMTBold",50);
    pLabelUpload->setAnchorPoint(ccp(0.5,1));
    pLabelUpload->setPosition(ccp(size.width*0.5,size.height*0.5));
    pLabelUpload->setVisible(false);
    addChild(pLabelUpload);
    
}
void BuyLifeLayer::CallBuyLife(void* sender)
{

    Node* pNode = (Node*)(sender);
    int price = pNode->getTag();
    
    IOSiAP_Bridge* bridge = new IOSiAP_Bridge();
    bridge->requestProducts(price);
    
    m_shopMenu->setEnabled(false);
    pLabelUpload->setVisible(true);

//
//    EventCustom event(BUY_LIFE_LIQUID);
//    _eventDispatcher->dispatchEvent(&event);
}
void BuyLifeLayer::CallUseLife(void* sender)
{
    int lifeLiquid = UserDefault::getInstance()->getIntegerForKey("LIFE_LIQUID");
    
    if (lifeLiquid > RIVIVE_COSUMED_DIAMOND)
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
        labelLife->setString("钻石不够\n请购买");
//        labelLife->setVisible(false);
        addChild(labelLife,11);
        labelLife->runAction(FadeOut::create(2));
//        CallFunc* call = [](){};
        "生命药水不够，请购买";
    }
        
}
void BuyLifeLayer::gameOver(void* sender)
{
    auto scene = GameOverLayer::scene();
    Director::getInstance()->replaceScene(scene);
}
