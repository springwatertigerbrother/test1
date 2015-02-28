//
//  GameOverLayer.cpp
//  niweishenmezhemediao
//
//  Created by huge on 13/9/14.
//
//

#include "GameOverLayer.h"
#include "GameCenterScene.h"
#include "DataHome.h"
#include "ballGamescene.h"
//#include "AdScenesDemo.h"
//#include "AdViewToolX.h"
//#include "IADSimple.h"

//GameOverLayer::GameOverLayer()
//{
//
//}
//GameOverLayer::~GameOverLayer()
//{
//
//}

static int m_i_HistoryHighestScore;

CCScene* GameOverLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = NULL;
    
    do
    {
        scene = CCScene::create();
        CC_BREAK_IF(! scene);
        
        // 'layer' is an autorelease object
        GameOverLayer *layer = GameOverLayer::create();
        if (layer) {
            layer->retain();
            // add layer as a child to scene
            scene->addChild(layer);
        }
        
        
    }while (0);
    
    
    
    // return the scene
    return scene;
}

bool GameOverLayer::init()
{
    if ( !CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)))
    {
        return false;
    }
    //    setTouchEnabled(true);
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* pBg = Sprite::create("Images/bg3.png");
    pBg->setPosition(ccp(s.width/2,s.height/2));
    pBg->setScale(CC_CONTENT_SCALE_FACTOR());
    addChild(pBg);
    
    MenuItemImage* pItem1 = MenuItemImage::create("Images/restart.png", "Images/restart.png", CC_CALLBACK_0(GameOverLayer::ReStartGame, this)) ;
    MenuItemImage* pItem2 = MenuItemImage::create("Images/share.png", "Images/share.png", CC_CALLBACK_0(GameOverLayer::ShareGame,this)) ;
    MenuItemImage* pItem3 = MenuItemImage::create("Images/backHome.png", "Images/backHome.png", CC_CALLBACK_0(GameOverLayer::backToHome,this)) ;
    pItem1->setScale(CC_CONTENT_SCALE_FACTOR());
    pItem2->setScale(CC_CONTENT_SCALE_FACTOR());
    pItem3->setScale(CC_CONTENT_SCALE_FACTOR());
    //    pItem2->setFontSize(180);
    //    CCMenu* pMenu2 = CCMenu::create(pItem2,NULL);
    //    pItem2->setPosition(ccp(s.width/2, s.height/5));
    //    pMenu2->setPosition(CCPointZero);
    //    addChild(pMenu2);
    
    //    CCMenuItemFont* pItem1 = CCMenuItemFont::create("restart", this, menu_selector(GameOverLayer::ReStartGame));
    //    CCMenuItemFont* pItem2 = CCMenuItemFont::create("share",this,menu_selector(GameOverLayer::ExitGame));
    
    CCMenu* pMenu = CCMenu::create(pItem2,pItem1,pItem3, NULL);
    pMenu->alignItemsHorizontallyWithPadding(10);
    //    pItem1->setFontSize(30);
    //    pItem2->setFontSize(30);
    
    pMenu->setPosition(ccp(s.width/2, s.height/4.0));
    addChild(pMenu);
    
//    CCLabelBMFont* pGameoverLblBM = CCLabelBMFont::create("Game Over", "fonts/bitmapFontTest2.fnt");
//    pGameoverLblBM->setString("Game Over");
//    pGameoverLblBM->setScale(1);
//    pGameoverLblBM->setPosition(ccp(s.width/2,s.height*0.8));
//    addChild(pGameoverLblBM);
    
    CCLabelTTF* pCongratulationTitle = CCLabelTTF::create("0","ArialRoundedMTBold",50);
    pCongratulationTitle->setPosition(ccp(s.width/2,s.height*0.8 + 70));
    String* pCongratulationTitleStr = String::createWithFormat("恭喜您的世界已进入");
    pCongratulationTitle->setString(pCongratulationTitleStr->getCString());
    addChild(pCongratulationTitle);
    
    CCLabelTTF* pCongratulation = CCLabelTTF::create("0","ArialRoundedMTBold",60);
    pCongratulation->setPosition(ccp(s.width/2,s.height*0.8));
    unsigned long  nTotalScore = 0;
//    char tempStr[100] = (CCUserDefault::sharedUserDefault()->getStringForKey("TOTALSCORE")).c_str();
    nTotalScore = strtoul((CCUserDefault::sharedUserDefault()->getStringForKey("TOTALSCORE")).c_str(), nullptr, 10);
    if (nTotalScore<0)
    {
        nTotalScore = 0;
    }
    String* pCongratulationScoreStr = String::createWithFormat("%d 次元",(int)(log2(nTotalScore)));
    pCongratulation->setString(pCongratulationScoreStr->getCString());
    pCongratulation->setColor(ccColor3B::ORANGE);
    addChild(pCongratulation);
    
    pCongratulation->runAction(RepeatForever::create(CCSequence::create(DelayTime::create(1.5f), CCScaleTo::create(0.3f, 2.0f),CCScaleTo::create(0.3f, 1.0f),NULL)));
    
    //    CCLabelTTF* pGameoverLbl = CCLabelTTF::create("Game Over", "ArialRoundedMTBold", 100);
    //    pGameoverLbl->setColor(ccRED);
    //    pGameoverLbl->setPosition(ccp(s.width/2,s.height*0.7));
    //    addChild(pGameoverLbl);
    
    CCLabelTTF* pScoreTitle = CCLabelTTF::create("总能量","ArialRoundedMTBold",50);
    pScoreTitle->setPosition(ccp(s.width/2,s.height*0.7));
    pScoreTitle->setColor(ccc3Red);
    addChild(pScoreTitle);
    
    CCLabelTTF* pTotalScore = CCLabelTTF::create("0","ArialRoundedMTBold",46);
    pTotalScore->setPosition(ccp(s.width/2,s.height*0.65));
    String* pTotalScoreStr = String::createWithFormat("%d",(nTotalScore));
    pTotalScore->setString(pTotalScoreStr->getCString());
    pTotalScore->setColor(ccYELLOW);
    addChild(pTotalScore);

//    CCLabelBMFont* pBestTitle = CCLabelBMFont::create("best",  "fonts/bitmapFontTest.fnt", 1, kCCTextAlignmentCenter, CCPointZero);
    CCLabelTTF* pBestTitle = CCLabelTTF::create("单次最高获取能量","ArialRoundedMTBold",50);
    pBestTitle->setPosition(ccp(s.width/2,s.height*0.58));
    pBestTitle->setColor(ccc3Red);
    addChild(pBestTitle);
    
    CCLabelTTF* pSingleBestScore = CCLabelTTF::create("0","ArialRoundedMTBold",60);
    pSingleBestScore->setPosition(ccp(s.width/2,s.height*0.53));
    pSingleBestScore->setColor(ccBLUE);
    
    int bestSingleScore = UserDefault::getInstance()->getIntegerForKey("SINGLE_BEST_SCORE");
    String* pSinggleBestScoreStr = String::createWithFormat("%d",bestSingleScore);
    pSingleBestScore->setString(pSinggleBestScoreStr->getCString());
    addChild(pSingleBestScore);
    pSingleBestScore->runAction(RepeatForever::create(CCSequence::create(DelayTime::create(1.5f), CCScaleTo::create(0.3f, 2.0f),CCScaleTo::create(0.3f, 1.0f),NULL)));
    //    tempStr = "best:"+tempStr;
    //    CCLabelTTF* pHightestLbl = CCLabelTTF::create(tempStr.c_str(), "ArialRoundedMTBold", 100);
    //    pHightestLbl->setPosition(ccp(s.width/2,s.height*0.5));
    //    addChild(pHightestLbl);
    
//    AdViewToolX::setAdHidden(false);
//    AdViewToolX::setAdPosition(AdViewToolX::AD_POS_CENTER, AdViewToolX::AD_POS_BOTTOM);
    
//    IADSimple* simple = [IADSimple IADSimple];
//    [simple.bannerView setHidden:false];
    
    //    CCDirector::sharedDirector()->pushScene(AdBottomDemo::scene(AdSceneDemo::DemoAdBottom));
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey("HistoryHighestScore", m_i_HistoryHighestScore);
    
    return true;
}


void GameOverLayer::ReStartGame()
{
    
//    AdViewToolX::setAdHidden(true);
//    IADSimple* simple = [IADSimple IADSimple];
//    [simple.bannerView setHidden:false];
    
    CCScene * playingScene = GameCenterScene::scene();
    Director::getInstance()->replaceScene(playingScene);
//    if (this->getParent())
//    {
////        ((GameCenter*)(this->getParent()))->listener->setSwallowTouches(true);
//        CCSize s = CCDirector::sharedDirector()->getWinSize();
//        this->runAction(CCMoveTo::create(0.2, ccp(0,s.height)));
//
////        ((GameCenter*)(this->getParent()))->StartGame();
////        ((HelloWorld*)(this->getParent()))->setTouchEnabled(true);
//    }

//    this->removeFromParentAndCleanup(true);

}

void GameOverLayer::ExitGame()
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
}
void GameOverLayer::ShareGame()
{
    log("share");
}
void GameOverLayer::GameCenter()
{

}
void GameOverLayer::RateMe()
{
    
}
void GameOverLayer::backToHome()
{
    auto scene = BallGameScene::scene();
    Director::getInstance()->replaceScene(scene);
}
//
//void GameOverLayer::registerWithTouchDispatcher()
//{
//    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
//}
//
//bool GameOverLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
//{
//    
//    CCPoint touchLocation = pTouch->getLocation();
//
//    return true;
//}
