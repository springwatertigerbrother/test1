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
    if ( !CCLayerColor::initWithColor(ccc4(200, 100, 100, 100)))
    {
        return false;
    }
    //    setTouchEnabled(true);
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    MenuItemImage* pItem1 = MenuItemImage::create("images/restartn.png", "images/restartp.png", CC_CALLBACK_0(GameOverLayer::ReStartGame, this)) ;
    MenuItemImage* pItem2 = MenuItemImage::create("images/start2normal.png", "images/start2press.png", CC_CALLBACK_0(GameOverLayer::ExitGame,this)) ;
    //    pItem2->setFontSize(180);
    //    CCMenu* pMenu2 = CCMenu::create(pItem2,NULL);
    //    pItem2->setPosition(ccp(s.width/2, s.height/5));
    //    pMenu2->setPosition(CCPointZero);
    //    addChild(pMenu2);
    
    //    CCMenuItemFont* pItem1 = CCMenuItemFont::create("restart", this, menu_selector(GameOverLayer::ReStartGame));
    //    CCMenuItemFont* pItem2 = CCMenuItemFont::create("share",this,menu_selector(GameOverLayer::ExitGame));
    
    CCMenu* pMenu = CCMenu::create(pItem1,NULL);
    pMenu->alignItemsVerticallyWithPadding(20);
    //    pItem1->setFontSize(30);
    //    pItem2->setFontSize(30);
    
    pMenu->setPosition(ccp(s.width/2, s.height/4.5));
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
    String* pCongratulationScoreStr = String::createWithFormat("%d 次元",(int)(log2(nTotalScore)));
    pCongratulation->setString(pCongratulationScoreStr->getCString());
    pCongratulation->setColor(ccColor3B::ORANGE);
    addChild(pCongratulation);
    
    //    CCLabelTTF* pGameoverLbl = CCLabelTTF::create("Game Over", "ArialRoundedMTBold", 100);
    //    pGameoverLbl->setColor(ccRED);
    //    pGameoverLbl->setPosition(ccp(s.width/2,s.height*0.7));
    //    addChild(pGameoverLbl);
    
    CCLabelTTF* pScoreTitle = CCLabelTTF::create("总分","Arial",50);
    pScoreTitle->setPosition(ccp(s.width/2,s.height*0.7));
    addChild(pScoreTitle);
    
    CCLabelTTF* pTotalScore = CCLabelTTF::create("0","Arial",46);
    pTotalScore->setPosition(ccp(s.width/2,s.height*0.65));
    String* pTotalScoreStr = String::createWithFormat("%d",(nTotalScore));
    pTotalScore->setString(pTotalScoreStr->getCString());
    pTotalScore->setColor(ccYELLOW);
    addChild(pTotalScore);

//    CCLabelBMFont* pBestTitle = CCLabelBMFont::create("best",  "fonts/bitmapFontTest.fnt", 1, kCCTextAlignmentCenter, CCPointZero);
    CCLabelTTF* pBestTitle = CCLabelTTF::create("单次最高得分","Arial",50);
    pBestTitle->setPosition(ccp(s.width/2,s.height*0.58));
    addChild(pBestTitle);
    
    CCLabelTTF* pSingleBestScore = CCLabelTTF::create("0","Arial",50);
    pSingleBestScore->setPosition(ccp(s.width/2,s.height*0.53));
    pSingleBestScore->setColor(ccGREEN);
    
    int bestSingleScore = UserDefault::getInstance()->getIntegerForKey("SINGLE_BEST_SCORE");
    String* pSinggleBestScoreStr = String::createWithFormat("%d",bestSingleScore);
    pSingleBestScore->setString(pSinggleBestScoreStr->getCString());
    addChild(pSingleBestScore);
    
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
