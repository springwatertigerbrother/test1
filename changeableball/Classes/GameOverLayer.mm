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
#import "UMSocialSnsData.h"
#include "NCSGameCenter.h"
#include "DataBase64.h"
#include "MUtils.h"
// 引入相关的头文件
#include "Cocos2dx/Common/CCUMSocialSDK.h"
#include "Cocos2dx/ShareButton/UMShareButton.h"

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

// 使用友盟命令空间
USING_NS_UM_SOCIAL;
// ...... 代码省略

void shareCallback(int platform, int stCode, string& errorMsg)
{
    if ( stCode == 100 )
    {
        CCLog("#### HelloWorld 开始分享");
    }
    else if ( stCode == 200 )
    {
        CCLog("#### HelloWorld 分享成功");
    }
    else
    {
        CCLog("#### HelloWorld 分享出错");
    }
    
    CCLog("platform num is : %d.", platform);
}

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
    if ( !CCLayerColor::initWithColor(ccc4(38, 156, 252, 255)))
    {
        return false;
    }
    
    std::string yourworld;
    std::string nciyuan;
    std::string totalScoreTitleStr;
    std::string sigleMost;
    std::string sigleState;
    std::string shareDiscription;
    LanguageType currentLanguageType = CCApplication::sharedApplication()->getCurrentLanguage();
    if (currentLanguageType == cocos2d::LanguageType::CHINESE)
    {
        yourworld = "恭喜您的世界已进入";
        nciyuan = "%d 次元";
        totalScoreTitleStr = "总能量：";
        sigleMost = "单次最高能量";
        sigleState ="最佳战斗力";
        shareDiscription = "炫耀奖励钻石1000";
    }
    else
    {
        yourworld = "hi,your world is";
        nciyuan = "%d dimension";
        totalScoreTitleStr = "total energy";
        sigleMost = "peak energy";
        sigleState ="most power";
        shareDiscription = "flaunt to get 1000 diamonds";
    }
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sounds/good.mp3");

    //    setTouchEnabled(true);
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
//    CCSprite* pBg = Sprite::create("Images/bg3.png");
//    pBg->setPosition(ccp(s.width/2,s.height/2));
//    pBg->setScale(CC_CONTENT_SCALE_FACTOR());
//    addChild(pBg);
////    pBg->setColor(Color3B(255, 0, 0));
//    pBg->setOpacity(200);
    MenuItemImage* pItem1 = MenuItemImage::create("Images/restartn.png", "Images/restart.png", CC_CALLBACK_0(GameOverLayer::ReStartGame, this)) ;
    
    MenuItemImage* pItem2 = MenuItemImage::create("Images/sharen.png", "Images/share.png", CC_CALLBACK_0(GameOverLayer::ShareGame,this)) ;
    MenuItemImage* pItem3 = MenuItemImage::create("Images/backHome.png", "Images/backHomep.png", CC_CALLBACK_0(GameOverLayer::backToHome,this)) ;
    MenuItemImage* pItem4 = MenuItemImage::create("Images/rankingn.png", "Images/paihang.png", CC_CALLBACK_0(GameOverLayer::ranking,this)) ;

    
    pItem1->setScale(CC_CONTENT_SCALE_FACTOR()*0.7);
    pItem2->setScale(CC_CONTENT_SCALE_FACTOR()*0.7);
    pItem3->setScale(CC_CONTENT_SCALE_FACTOR()*0.7);
    pItem4->setScale(CC_CONTENT_SCALE_FACTOR()*0.7);
    
//    CCLabelTTF* testLabel = CCLabelTTF::create("排行榜 \n ranking","ArialRoundedMTBold",32);
//    testLabel->setPosition(ccp(pItem4->getContentSize().width/2,pItem4->getContentSize().height/2));
//    pItem4->addChild(testLabel);
    
    //    pItem2->setFontSize(180);
    //    CCMenu* pMenu2 = CCMenu::create(pItem2,NULL);
    //    pItem2->setPosition(ccp(s.width/2, s.height/5));
    //    pMenu2->setPosition(CCPointZero);
    //    addChild(pMenu2);
    
    //    CCMenuItemFont* pItem1 = CCMenuItemFont::create("restart", this, menu_selector(GameOverLayer::ReStartGame));
    //    CCMenuItemFont* pItem2 = CCMenuItemFont::create("share",this,menu_selector(GameOverLayer::ExitGame));
    
    CCMenu* pMenu = CCMenu::create(pItem2,pItem1,pItem3, pItem4, NULL);
    pMenu->alignItemsHorizontallyWithPadding(10);
    //    pItem1->setFontSize(30);
    //    pItem2->setFontSize(30);
    
    pMenu->setPosition(ccp(s.width/2, s.height/6.0));
    addChild(pMenu);
    
//    CCLabelBMFont* pGameoverLblBM = CCLabelBMFont::create("Game Over", "fonts/bitmapFontTest2.fnt");
//    pGameoverLblBM->setString("Game Over");
//    pGameoverLblBM->setScale(1);
//    pGameoverLblBM->setPosition(ccp(s.width/2,s.height*0.8));
//    addChild(pGameoverLblBM);
    
    CCLabelTTF* pCongratulationTitle = CCLabelTTF::create("0","ArialRoundedMTBold",50);
    pCongratulationTitle->setPosition(ccp(s.width/2,s.height*0.8 + 70));
    String* pCongratulationTitleStr = String::createWithFormat(yourworld.c_str());
    pCongratulationTitle->setString(pCongratulationTitleStr->getCString());
    addChild(pCongratulationTitle);
    
    CCLabelTTF* pCongratulation = CCLabelTTF::create("0","ArialRoundedMTBold",40);
    pCongratulation->setPosition(ccp(s.width/2,s.height*0.8));
    unsigned long  nTotalScore = 0;
//    char tempStr[100] = (CCUserDefault::sharedUserDefault()->getStringForKey("TOTALSCORE")).c_str();
    nTotalScore = strtoul((getStringForKey("TOTALSCORE")).c_str(), nullptr, 10);
    if (nTotalScore<0)
    {
        nTotalScore = 0;
    }
    
    int nciValue = calculate_score(nTotalScore,0);
    String* pCongratulationScoreStr = String::createWithFormat(nciyuan.c_str(),nciValue);
    pCongratulation->setString(pCongratulationScoreStr->getCString());
    pCongratulation->setColor(ccColor3B::ORANGE);
    addChild(pCongratulation);
    
//    pCongratulation->runAction(RepeatForever::create(CCSequence::create(DelayTime::create(1.5f), CCScaleTo::create(0.3f, 2.0f),CCScaleTo::create(0.3f, 1.0f),NULL)));
    
    //    CCLabelTTF* pGameoverLbl = CCLabelTTF::create("Game Over", "ArialRoundedMTBold", 100);
    //    pGameoverLbl->setColor(ccRED);
    //    pGameoverLbl->setPosition(ccp(s.width/2,s.height*0.7));
    //    addChild(pGameoverLbl);
    
    CCLabelTTF* pScoreTitle = CCLabelTTF::create(totalScoreTitleStr.c_str(),"ArialRoundedMTBold",50);
    pScoreTitle->setPosition(ccp(s.width/2,s.height*0.7));
    pScoreTitle->setColor(ccc3Red);
    addChild(pScoreTitle);
    
    CCLabelTTF* pTotalScore = CCLabelTTF::create("0","ArialRoundedMTBold",40);
    pTotalScore->setPosition(ccp(s.width/2,s.height*0.7 - 60));
    String* pTotalScoreStr = String::createWithFormat("%d",(nTotalScore));
    pTotalScore->setString(pTotalScoreStr->getCString());
    pTotalScore->setColor(ccYELLOW);
    addChild(pTotalScore);
//    pTotalScore->runAction(RepeatForever::create(CCSequence::create(DelayTime::create(1.5f + 0.3f), CCScaleTo::create(0.3f, 2.0f),CCScaleTo::create(0.3f, 1.0f),NULL)));

//    CCLabelBMFont* pBestTitle = CCLabelBMFont::create("best",  "fonts/bitmapFontTest.fnt", 1, kCCTextAlignmentCenter, CCPointZero);
    CCLabelTTF* pBestTitle = CCLabelTTF::create(sigleMost.c_str(),"ArialRoundedMTBold",50);
    pBestTitle->setPosition(ccp(s.width/2,s.height*0.55));
    pBestTitle->setColor(ccc3Red);
    addChild(pBestTitle);
    
    CCLabelTTF* pSingleBestScore = CCLabelTTF::create("0","ArialRoundedMTBold",40);
    pSingleBestScore->setPosition(ccp(s.width/2,s.height*0.55- 60));
    pSingleBestScore->setColor(ccBLUE);
    
    int bestSingleScore = getIntegerForKey("SINGLE_BEST_SCORE");

//    int bestSingleScore = UserDefault::getInstance()->getIntegerForKey("SINGLE_BEST_SCORE");
    String* pSinggleBestScoreStr = String::createWithFormat("%d",bestSingleScore);
    pSingleBestScore->setString(pSinggleBestScoreStr->getCString());
    addChild(pSingleBestScore);
    pSingleBestScore->runAction(RepeatForever::create(CCSequence::create(DelayTime::create(1.5f + 0.6f), CCScaleTo::create(0.3f, 2.0f),DelayTime::create(1),CCScaleTo::create(0.3f, 1.0f),NULL)));
    
    CCLabelTTF* pBestNTitle = CCLabelTTF::create(sigleState.c_str(), "ArialRoundedMTBold",50);
    pBestNTitle->setPosition(ccp(s.width/2,s.height*0.40));
    pBestNTitle->setColor(ccc3Red);
    addChild(pBestNTitle);
    
    CCLabelTTF* pBestNvalue = CCLabelTTF::create("n", "ArialRoundedMTBold",40);
    pBestNvalue->setPosition(ccp(s.width/2,s.height*0.40-60));
    pBestNvalue->setColor(ccWHITE);
    addChild(pBestNvalue);
    String* pBestNvalueStr = String::createWithFormat(nciyuan.c_str(),calculate_score(bestSingleScore,0));
    pBestNvalue->setString(pBestNvalueStr->getCString());
    pBestNvalue->runAction(RepeatForever::create(CCSequence::create(DelayTime::create(1.5f + 0.9f), CCScaleTo::create(0.3f, 2.0f),DelayTime::create(1), CCScaleTo::create(0.3f, 1.0f),NULL)));

    //    tempStr = "best:"+tempStr;
    //    CCLabelTTF* pHightestLbl = CCLabelTTF::create(tempStr.c_str(), "ArialRoundedMTBold", 100);
    //    pHightestLbl->setPosition(ccp(s.width/2,s.height*0.5));
    //    addChild(pHightestLbl);
    
//    AdViewToolX::setAdHidden(false);
//    AdViewToolX::setAdPosition(AdViewToolX::AD_POS_CENTER, AdViewToolX::AD_POS_BOTTOM);
    
//    IADSimple* simple = [IADSimple IADSimple];
//    [simple.bannerView setHidden:false];
    
    
    CCLabelTTF* pshareBunus = CCLabelTTF::create(shareDiscription.c_str(), "ArialRoundedMTBold",20);
    pshareBunus->setAnchorPoint(ccp(0,0.5));
    pshareBunus->setPosition(ccp(20,240));
//    pshareBunus->setColor(ccc3Red);
    addChild(pshareBunus);
    pshareBunus->runAction(RepeatForever::create(CCSequence::create(DelayTime::create(1.5f + 0.9f), CCScaleTo::create(0.3f, 2.0f),DelayTime::create(1), CCScaleTo::create(0.3f, 1.0f),NULL)));
    //    CCDirector::sharedDirector()->pushScene(AdBottomDemo::scene(AdSceneDemo::DemoAdBottom));
    setIntegerForKey("HistoryHighestScore", m_i_HistoryHighestScore);
//    CCUserDefault::sharedUserDefault()->setIntegerForKey("HistoryHighestScore", m_i_HistoryHighestScore);
    CCUserDefault::sharedUserDefault()->flush();
//    char buffer[32];
//    sprintf(buffer, "%s%d", "Himi",iKey);
    
        [[ NCSGameCenter sharedGameCenter] reportScore:nTotalScore forCategory:kLeaderboardID];

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

    
    
    int lastTime  = getIntegerForKey("LAST_TIME");
    
    time_t nowtime;
    struct tm *timeinfo;
    time( &nowtime );
    timeinfo = localtime( &nowtime );
    int year, month, day;
    year = timeinfo->tm_year + 1900;
    month = timeinfo->tm_mon + 1;
    day = timeinfo->tm_mday;
    
    if (day != lastTime)
    {
        setIntegerForKey("LAST_TIME",day);
        int sharetimes = getIntegerForKey("SHARE_TIMES");
       
        if (sharetimes<5)
        {
            sharetimes++;
            setIntegerForKey("SHARE_TIMES",sharetimes);
            
            int lifeLiquid = getIntegerForKey("LIFE_LIQUID");
            
            lifeLiquid += 1000;
            setIntegerForKey("LIFE_LIQUID",lifeLiquid);
        }
    }
    

    
//    log("%d time",nowtime);
    
    std::string shareStr;
    LanguageType currentLanguageType = CCApplication::sharedApplication()->getCurrentLanguage();
    switch (currentLanguageType)
    {
        case cocos2d::LanguageType::CHINESE:
            
            shareStr = "我在 n 次元 游戏中已经进入了 %d 次元，最佳战斗力是 %d 次元，小伙伴你呢？？？";
            break;
        case cocos2d::LanguageType::ENGLISH:
            
            shareStr = "I have into %d dimension in 'N dimension'game ,where are you friends?";
            break;
        default:
            break;
    }
    
    std::string outputFile = "";
    outputFile = FileUtils::getInstance()->getWritablePath() + "screenShot.png";
    cocos2d::utils::captureScreen(nil,outputFile);
    // 获取一个CCUMSocialSDK实例
    CCUMSocialSDK *sdk = CCUMSocialSDK::create("55121768fd98c588b0000a3e");
    // 设置友盟appkey,如果create中设置了不用调用该函数
    // sdk->setAppKey("4eaee02c527015373b000003");
    // **********************   设置平台信息  ***************************
    // sdk->setQQAppIdAndAppKey("设置QQ的app id", "appkey");
    sdk->setWeiXinAppInfo("wx4709b0db1758b611","e3bea36c663071278e45440d6e00f7c5");
    sdk->setFacebookAppId("378679852325190");
    // sdk->setYiXinAppKey("设置易信和易信朋友圈的app id");
    // sdk->setLaiwangAppInfo("设置来往和来往动态的app id",
    //              "设置来往和来往动态的app key", "我的应用名");
    // sdk->setFacebookAppId("你的facebook appid");
    //     // 打开或者关闭log
    // sdk->setLogEnable(true) ;
    // **********************   END ***************************
    
    // 设置用户点击一条图文分享时用户跳转到的目标页面, 一般为app主页或者下载页面
//    sdk->setTargetUrl("https://itunes.apple.com/us/app/n-ci-yuan/id975972814?l=zh&ls=1&mt=8");
    sdk->setTargetUrl(SHARED_URL);
    // 设置友盟分享面板上显示的平台
    vector<int>* platforms = new vector<int>();
    platforms->push_back(SINA);
    platforms->push_back(RENREN) ;
    platforms->push_back(WEIXIN_CIRCLE) ;
    platforms->push_back(FACEBOOK);
//    platforms->push_back(QZONE) ;
//    platforms->push_back(QQ) ;
    platforms->push_back(DOUBAN) ;

    
    // 设置平台, 在调用分享、授权相关的函数前必须设置SDK支持的平台
    sdk->setPlatforms(platforms) ;
    
    // 打开分享面板, 注册分享回调, 参数1为分享面板上的平台, 参数2为要分享的文字内容，
    // 参数3为要分享的图片路径(android和IOS的图片地址格式不一致，因此分平台设置), 参数4为分享回调.
//    int nDimension = UserDefault()->getInstance->geti
//    char tempStr[100] ="";
    
    unsigned long  nTotalScore = 0;
    //    char tempStr[100] = (CCUserDefault::sharedUserDefault()->getStringForKey("TOTALSCORE")).c_str();
    nTotalScore = strtoul((getStringForKey("TOTALSCORE")).c_str(), nullptr, 10);
    if (nTotalScore<0)
    {
        nTotalScore = 0;
    }
//    char shareContent[200] = "";
//    sprintf(shareContent, "我在 n 次元 游戏中已经进入了　%d 次元，小伙伴你呢？？？",)
    
    int nciValue = calculate_score(nTotalScore,0);
    int bestSingleScore = getIntegerForKey("SINGLE_BEST_SCORE");
    int nbestciValue = calculate_score(bestSingleScore,0);
    String* pCongratulationScoreStr = String::createWithFormat(shareStr.c_str(),
                                                               nciValue,nbestciValue);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    sdk->openShare(pCongratulationScoreStr->getCString(), "/sdcard/image.png", share_selector(shareCallback));
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //    sdk->setPlatformShareContent(WEIXIN_CIRCLE,"我在 n 次元 游戏中已经进入了　%d，小伙伴你呢？？？","Images/emc2.png");
    sdk->openShare(pCongratulationScoreStr->getCString(),outputFile.c_str(), share_selector(shareCallback));
#endif
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
void GameOverLayer::ranking()
{
    [[ NCSGameCenter sharedGameCenter] registerForAuthenticationNotification];
    [[ NCSGameCenter sharedGameCenter] showLeaderboard];
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
