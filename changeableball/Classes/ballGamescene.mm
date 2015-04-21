//
//  ballGamescene.cpp
//  changeableball
//
//  Created by mac on 14-9-6.
//
//

#include "ballGamescene.h"
#include "GameCenterScene.h"
#include "DataHome.h"
#include "MUtils.h"
#include "IOSiAP_Bridge.h"
#import "UMSocialSnsData.h"
#include "NCSGameCenter.h"
// 引入相关的头文件
#include "Cocos2dx/Common/CCUMSocialSDK.h"
#include "Cocos2dx/ShareButton/UMShareButton.h"
#include "DataBase64.h"

using namespace cocos2d;

// 使用友盟命令空间
USING_NS_UM_SOCIAL;
// ...... 代码省略


CCScene* BallGameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = NULL;
    
    do
    {
        scene = CCScene::create();
        CC_BREAK_IF(! scene);
        
        // 'layer' is an autorelease object
        BallGameScene *layer = BallGameScene::create();
        if (layer) {
            layer->retain();
            // add layer as a child to scene
            scene->addChild(layer);
        }
      
    
    }while (0);
    

    
    // return the scene
    return scene;
}
bool BallGameScene::init()
{
    do
    {
        if (!cocos2d::CCLayer::init()) {
            return false;
        }
        CCLayerColor* pBGLayer = CCLayerColor::create(ccc4(88,34,241,255));
//        pBGLayer->initWithColor(ccc4(111, 155, 160, 133));

        pBGLayer->setAnchorPoint(CCPoint(0,0));
        addChild(pBGLayer);

//        std::string outputFile = "";
//        outputFile = FileUtils::getInstance()->getWritablePath() + "screenShot.png";
//        
//        NSFileManager* fileManager=[NSFileManager defaultManager];
//        NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,NSUserDomainMask, YES);
//        
//        //文件名
//        NSString *uniquePath=[[paths objectAtIndex:0] stringByAppendingPathComponent:@"screenShot.png"];
//        BOOL blHave=[[NSFileManager defaultManager] fileExistsAtPath:uniquePath];
//        if (!blHave) {
//            NSLog(@"no  have");
//        }else {
//            NSLog(@" have");
//            BOOL blDele= [fileManager removeItemAtPath:uniquePath error:nil];
//            if (blDele) {
//                NSLog(@"dele success");
//            }else {
//                NSLog(@"dele fail");
//            }
//            
//        }
        
//        // 创建分享按钮, 参数1为按钮正常情况下的图片, 参数2为按钮选中时的图片,参数3为友盟appkey, 参数4为分享回调
//        UMShareButton *shareButton = UMShareButton::create("Images/share.png","Images/share.png", "你的友盟appkey", share_selector(shareCallback)) ;
//        
//        CCUMSocialSDK *sdk = shareButton->getSocialSDK();
//        // sdk->setQQAppIdAndAppKey("设置QQ的app id", "appkey");
//        sdk->setWeiXinAppInfo("wx4709b0db1758b611",
//                              "e3bea36c663071278e45440d6e00f7c5");
//        // 显示在友盟分享面板上的平台
//        vector<int>* platforms = new vector<int>();
//        platforms->push_back(SINA);
//        platforms->push_back(RENREN) ;
//        platforms->push_back(DOUBAN) ;
////        platforms->push_back(QZONE) ;
////        platforms->push_back(QQ) ;
//        platforms->push_back(WEIXIN);
//        platforms->push_back(WEIXIN_CIRCLE);
//        platforms->push_back(FACEBOOK);
//
//        // 设置友盟分享面板上显示的平台
//        shareButton->setPlatforms(platforms);
//        // 设置文本分享内容
//        shareButton->setShareContent("我在 n 次元 游戏中已经进入了　%d，小伙伴你呢？？？") ;
//        // 设置要分享的图片, 图片支持本地图片和url图片, 但是url图片必须以http://或者https://开头
////        shareButton->setShareImage("/sdcard/header.jpeg") ;
//        shareButton->setShareImage("Images/emc2.png") ;
////        sdk->openShare("我在 n 次元 游戏中已经进入了　%d，小伙伴你呢？？？","Images/emc2.png", share_selector(shareCallback));
//
//        // 设置按钮的位置
//        shareButton->setPosition(ccp(150, 180));
//        // 然后开发者需要将该按钮添加到游戏场景中
//        CCMenu* pMenu = CCMenu::create(shareButton, NULL);
//        pMenu->setPosition(CCPointZero);
//        this->addChild(pMenu, 1);
//        
//        // ********************** 设置平台信息 ***************************
////         CCUMSocialSDK *sdk = shareButton->getSocialSDK();
////        // sdk->setQQAppIdAndAppKey("设置QQ的app id", "appkey");
////         sdk->setWeiXinAppInfo("设置微信和朋友圈的app id","app key");
//        // sdk->setYiXinAppKey("设置易信和易信朋友圈的app id");
//        // sdk->setLaiwangAppInfo("设置来往和来往动态的app id",
//        //                  "设置来往和来往动态的app key", "我的应用名");
//        // sdk->setFacebookAppId("你的facebook appid");
//        // 设置用户点击一条图文分享时用户跳转到的目标页面, 一般为app主页或者下载页面
//        // sdk->setTargetUrl("http://www.umeng.com/social");
//        //     // 打开或者关闭log
//        // sdk->setLogEnable(true) ;
//        // **********************   END ***************************
        
    }
    while(0);
    return true;
}



void BallGameScene::onEnter()
{
    
    CCLayer::onEnter();
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* pBg4 = Sprite::create("Images/bg1.png");
    pBg4->setPosition(ccp(size.width/2,size.height/2));
    pBg4->setOpacity(230);
    addChild(pBg4);
    pBg4->setScale(get_content_scale_factor(), get_content_scale_factor());
    
//    CCSprite* pBg = Sprite::create("Images/aiyisitanfudiao.png");
//    CCSprite* pBg = Sprite::create("Images/aystthinging.png");
//    pBg->setAnchorPoint(ccp(0.5,1));
//    pBg->setPosition(ccp(size.width/2,size.height));
//    pBg->setOpacity(200);
//    pBg->setScale(CC_CONTENT_SCALE_FACTOR());
//    addChild(pBg);

    CCSprite* pemc2 = Sprite::create("Images/emc2.png");
    pemc2->setPosition(ccp(size.width/2,size.height/1.3));
    pemc2->setScale(CC_CONTENT_SCALE_FACTOR());
    addChild(pemc2);

    pemc2->setAnchorPoint(ccp(-0.5,-0.5));
    pemc2->runAction(RepeatForever::create(RotateBy::create(10, 360) ) );
    
    m_playnow = CCMenuItemImage::create("Images/startStandard.png","Images/startStandard.png", CC_CALLBACK_1(BallGameScene::playingNow,this));
    m_playnow->setScale(CC_CONTENT_SCALE_FACTOR());
    m_countdown = CCMenuItemImage::create("Images/countdown.png","Images/countdown.png",CC_CALLBACK_1(BallGameScene::multiplePlayer,this));
    m_countdown->setScale(CC_CONTENT_SCALE_FACTOR());
    m_ranking = CCMenuItemImage::create("Images/ranking.png","Images/ranking.png", CC_CALLBACK_1(BallGameScene::ranking,this));
    m_ranking->setScale(CC_CONTENT_SCALE_FACTOR());
    m_share = CCMenuItemImage::create("Images/sharegray.png","Images/sharegray.png",CC_CALLBACK_1(BallGameScene::share,this));
    m_share->setScale(CC_CONTENT_SCALE_FACTOR());
//    
//    m_highscore = CCMenuItemImage::create("Images/high_score.png","Images/high_score.png",CC_CALLBACK_1(BallGameScene::highScore,this));
//    
//    m_settings = CCMenuItemImage::create("Images/settings.png","Images/settings.png", CC_CALLBACK_1(BallGameScene::settings,this));
//    
//    m_aboutus = CCMenuItemImage::create("Images/about_us.png","Images/about_us.png", CC_CALLBACK_1(BallGameScene::aboutus,this));
    
    CCMenu *menu = CCMenu::create(m_playnow,m_countdown,m_ranking,m_share, NULL);
    
    menu->alignItemsVerticallyWithPadding(30);
    
    menu->setPosition(ccp(size.width/2,size.height/2));
    
    
//    auto backgroundButton = cocos2d::extension::Scale9Sprite::create("Images/button.png");
//    auto backgroundHighlightedButton = cocos2d::extension::Scale9Sprite::create("Images/buttonHighlighted.png");
//    
//    auto title = "标准模式";
//    auto titleButton = Label::createWithTTF(title, "fonts/Marker Felt.ttf", 30);
//    
//    titleButton->setColor(Color3B(159, 168, 176));
//    
//    cocos2d::extension::ControlButton *button = cocos2d::extension::ControlButton::create(titleButton, backgroundButton);
//    button->setBackgroundSpriteForState(backgroundHighlightedButton, cocos2d::extension::Control::State::HIGH_LIGHTED);
//    button->setTitleColorForState(Color3B::WHITE, cocos2d::extension::Control::State::HIGH_LIGHTED);
//    button->addTargetWithActionForControlEvents(this, cccontrol_selector(BallGameScene::playingNow), cocos2d::extension::Control::EventType::TOUCH_DOWN);
//    button->setPosition(ccp(size.width/2,size.height/3));

//    MenuItemFont::setFontName("American Typewriter");
//    MenuItemFont::setFontSize(30);
//    auto title1 = MenuItemFont::create("Sound");
//    title1->setEnabled(false);
//    MenuItemFont::setFontName( "fonts/Marker Felt.ttf" );
//    MenuItemFont::setFontSize(50);
//    auto item1 = MenuItemToggle::createWithCallback( CC_CALLBACK_1(BallGameScene::musicControl, this),
//                                                    MenuItemFont::create( "music On" ),
//                                                    MenuItemFont::create( "music Off"),
//                                                    nullptr );
//    item1->setEnabled(true);
//    auto musciMenu = Menu::create(item1, nullptr);
//    musciMenu->setPosition(ccp(size.width/2,size.height/5));
//    
//    //            musciMenu->alignItemsInColumns(2, 2, 2, 2, 1, NULL);
////    musciMenu->setVisible(false);
//    addChild( musciMenu );

//    std::vector<std::string> vec;
//            vec.push_back("Hello");
//            vec.push_back("Variable");
//            vec.push_back("Size");
//            vec.push_back("!trteerterreer\nndf");
//    ControlButtoninit(this,vec);
    menu->setOpacity(200);
    this-> addChild(menu);
    
    CCLabelTTF* pCongratulationTitle = CCLabelTTF::create("0","ArialRoundedMTBold",30);
    pCongratulationTitle->setPosition(ccp(size.width/2 + 10,size.height*0.8 + 70));
    
    std::string yourworld;
    std::string nciyuan;
    std::string bicicle;
    std::string shareStr;
    yourworld = "your world is";
    nciyuan = "%d dimension";
    bicicle = "Life is like riding a bicycle.To keep your balance you must keep moving";
    shareStr = "I have into %d dimension in 'N dimension'game ,where are you friends?";
    
    LanguageType currentLanguageType = CCApplication::sharedApplication()->getCurrentLanguage();
    switch (currentLanguageType)
    {
        case cocos2d::LanguageType::CHINESE:
            yourworld = "您的世界已进入";
            nciyuan = "%d 次元";
            bicicle = "人生如同骑单车，要想保持平衡就必须前行";
            shareStr = "我在 n 次元 游戏中已经进入了 %d 次元，小伙伴你呢？？？";
            break;
        case cocos2d::LanguageType::ENGLISH:
            yourworld = "your world is";
            nciyuan = "%d dimension";
            bicicle = "Life is like riding a bicycle.To keep your balance you must keep moving";
            shareStr = "I have into %d dimension in 'N dimension'game ,where are you friends?";
            break;
        default:
            break;
    }
    String* pCongratulationTitleStr = String::createWithFormat(yourworld.c_str());
    pCongratulationTitle->setString(pCongratulationTitleStr->getCString());
    addChild(pCongratulationTitle);
    
    CCLabelTTF* pCongratulation = CCLabelTTF::create("0","ArialRoundedMTBold",30);
    pCongratulation->setPosition(ccp(size.width/2 + 10,size.height*0.8));
    unsigned long  nTotalScore = 0;
    //    char tempStr[100] = (CCUserDefault::sharedUserDefault()->getStringForKey("TOTALSCORE")).c_str();
//    nTotalScore = strtoul((CCUserDefault::sharedUserDefault()->getStringForKey("TOTALSCORE")).c_str(), nullptr, 10);
    nTotalScore = strtoul((getStringForKey("TOTALSCORE")).c_str(), nullptr, 10);
    if (nTotalScore<0)
    {
        nTotalScore = 0;
    }
    int scoreValue = calculate_score(nTotalScore,0);
    String* pCongratulationScoreStr = String::createWithFormat(nciyuan.c_str(),scoreValue);
    pCongratulation->setString(pCongratulationScoreStr->getCString());
    pCongratulation->setColor(ccColor3B::ORANGE);
    addChild(pCongratulation);
     
    pCongratulation->runAction(RepeatForever::create(CCSequence::create(DelayTime::create(1.5f), CCScaleTo::create(0.3f, 2.0f),CCScaleTo::create(0.3f, 1.0f),NULL)));
    
    
    CCLabelTTF* labelLife  = CCLabelTTF::create("60","ArialRoundedMTBold",15);
    labelLife->setAnchorPoint(ccp(0, 0.5));
    labelLife->setColor(ccRED);
    labelLife->setPosition(ccp(size.width/2 - 150,230));
    labelLife->setString(bicicle);
    labelLife->setDimensions(CCSize(400,0));
    //        labelLife->setVisible(false);
    addChild(labelLife,11);
    auto scaleAction = ScaleBy::create(2, 1.5);
    labelLife->runAction(RepeatForever::create(Sequence::create(scaleAction,scaleAction->reverse(), nil)));
    
    [[ NCSGameCenter sharedGameCenter] reportScore:nTotalScore forCategory:kLeaderboardID];

}


void BallGameScene:: startGame()
{
    
    this-> removeAllChildren();
    
}
//void BallGameScene::playingNow(Ref *senderz, cocos2d::extension::Control::EventType controlEvent)
//{
//    DataHome::getInstance()->isCountDownModel = false;
//    
//    CCScene * playingScene = GameCenterScene::scene();
//    CCDirector::sharedDirector()->replaceScene(playingScene);
//}

void BallGameScene:: playingNow(void* sender)
{
    DataHome::getInstance()->isCountDownModel = false;

    CCScene * playingScene = GameCenterScene::scene();
    CCDirector::sharedDirector()->replaceScene(playingScene);
//    [[CCDirector sharedDirector] replaceScene:[CCTransitionMoveInR transitionWithDuration:0.2 scene:playingScene]];
}
void BallGameScene:: countDownModel(void* sender)
{
    DataHome::getInstance()->isCountDownModel = true;
    
    CCScene * playingScene = GameCenterScene::scene();
    CCDirector::sharedDirector()->replaceScene(playingScene);
}

void BallGameScene:: ranking(void* sender)
{
    [[ NCSGameCenter sharedGameCenter] registerForAuthenticationNotification];
    [[ NCSGameCenter sharedGameCenter] showLeaderboard];

}
void BallGameScene:: share(void* sender)
{
    std::string shareStr;
    shareStr = "I have into %d dimension in 'N dimension'game ,where are you friends?";

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
    int nValue = calculate_score(nTotalScore,0);
    int bestSingleScore = getIntegerForKey("SINGLE_BEST_SCORE");
    int nbestciValue = calculate_score(bestSingleScore,0);

    String* pCongratulationScoreStr = String::createWithFormat(shareStr.c_str(),
                                                               nValue,nbestciValue);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    sdk->openShare(pCongratulationScoreStr->getCString(), "/sdcard/image.png", share_selector(shareCallback));
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //    sdk->setPlatformShareContent(WEIXIN_CIRCLE,"我在 n 次元 游戏中已经进入了　%d，小伙伴你呢？？？","Images/emc2.png");
    sdk->openShare(pCongratulationScoreStr->getCString(),outputFile.c_str(), nullptr);
#endif
    log("share");
}
void BallGameScene:: multiplePlayer(void* sender)
{
//    NSString *str = [NSString stringWithFormat:
//                     
//                     @"itms-apps://ax.itunes.apple.com/WebObjects/MZStore.woa /wa/viewContentsUserReviews?type=Purple+Software&id=%d",
//                     
//                     m_appleID ];
//    
//    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:str]];
    
//    if(1)
//    {
//        IOSiAP_Bridge* bridge = new IOSiAP_Bridge();
//        bridge->requestProducts(6);
//    }
//    if(0)
//    {
//        std::string outputFile = "";
//        outputFile = FileUtils::getInstance()->getWritablePath() + "screenShot.png";
//        cocos2d::utils::captureScreen(nil,outputFile);
//    // 获取一个CCUMSocialSDK实例
//    CCUMSocialSDK *sdk = CCUMSocialSDK::create("55121768fd98c588b0000a3e");
//    // 设置友盟appkey,如果create中设置了不用调用该函数
//    // sdk->setAppKey("4eaee02c527015373b000003");
//    // **********************   设置平台信息  ***************************
//    // sdk->setQQAppIdAndAppKey("设置QQ的app id", "appkey");
//     sdk->setWeiXinAppInfo("wx4709b0db1758b611","e3bea36c663071278e45440d6e00f7c5");
//    
//    // sdk->setYiXinAppKey("设置易信和易信朋友圈的app id");
//    // sdk->setLaiwangAppInfo("设置来往和来往动态的app id",
//    //              "设置来往和来往动态的app key", "我的应用名");
//    // sdk->setFacebookAppId("你的facebook appid");
//    //     // 打开或者关闭log
//    // sdk->setLogEnable(true) ;
//    // **********************   END ***************************
//    
//    // 设置用户点击一条图文分享时用户跳转到的目标页面, 一般为app主页或者下载页面
//    sdk->setTargetUrl("https://itunes.apple.com/us/app/kill-chimeny/id922862015?l=zh&ls=1&mt=8");
//    // 设置友盟分享面板上显示的平台
//    vector<int>* platforms = new vector<int>();
//    platforms->push_back(SINA);
//    platforms->push_back(RENREN) ;
//    platforms->push_back(WEIXIN_CIRCLE) ;
//    platforms->push_back(FACEBOOK);
//    platforms->push_back(QZONE) ;
//    platforms->push_back(QQ) ;
//    platforms->push_back(DOUBAN) ;
//
//    // 设置平台, 在调用分享、授权相关的函数前必须设置SDK支持的平台
//    sdk->setPlatforms(platforms) ;
//    
//    // 打开分享面板, 注册分享回调, 参数1为分享面板上的平台, 参数2为要分享的文字内容，
//    // 参数3为要分享的图片路径(android和IOS的图片地址格式不一致，因此分平台设置), 参数4为分享回调.
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    sdk->openShare("我在 n 次元 游戏中已经进入了　%d，小伙伴你呢？？？", "/sdcard/image.png", share_selector(shareCallback));
//#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
////    sdk->setPlatformShareContent(WEIXIN_CIRCLE,"我在 n 次元 游戏中已经进入了　%d，小伙伴你呢？？？","Images/emc2.png");
//    sdk->openShare("我的世界已经进入了　%d 次元，小伙伴你呢？？？",outputFile.c_str(), share_selector(shareCallback));
//#endif
//    }
//
    DataHome::getInstance()->isCountDownModel = true;
    
    CCScene * playingScene = GameCenterScene::scene();
    CCDirector::sharedDirector()->replaceScene(playingScene);
}

void BallGameScene:: highScore(void* sender)
{
    
//    CCScene * playingScene = [TopScoreLayer scene];
//    
//    [[CCDirector sharedDirector] pushScene:[CCTransitionMoveInR transitionWithDuration:0.2 scene:playingScene]];
}

void BallGameScene:: settings(void* sender)
{
    
}

void BallGameScene:: aboutus(void* sender)
{
    
}

void BallGameScene::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
    CCLOG("trans");
}

void BallGameScene::musicControl(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()-> stopAllEffects();

}

bool BallGameScene::ControlButtoninit(Node* obj,std::vector<std::string> vec)
{
    auto screenSize = Director::getInstance()->getWinSize();
    
    // Defines an array of title to create buttons dynamically
    //        std::vector<std::string> vec;
    //        vec.push_back("Hello");
    //        vec.push_back("Variable");
    //        vec.push_back("Size");
    //        vec.push_back("!trteerterreer\nndf");
    
    auto layer = Node::create();
    obj->addChild(layer, 1);
    
    double total_width = 0, width, height = 0,total_height = 0,offsetY = 100;
    
    int i = 0;
    
    for (auto& title : vec)
    {
        // Creates a button with this string as title
        ControlButton *button = standardButtonWithTitle(title.c_str());
        
        button->addTargetWithActionForControlEvents(this, cccontrol_selector(BallGameScene::touchDownAction), Control::EventType::TOUCH_DOWN);
        button->setTag(i++);
        button->setOpacity(50);
//        button->setScale(<#float scale#>)
//        if (i == 0)
//        {
//            button->setOpacity(50);
//            //                button->setColor(Color3B(0, 255, 0));
//        }
//        else if (i == 1)
//        {
//            button->setOpacity(50);
//            button->setColor(Color3B(0, 255, 0));
//        }
//        else if (i == 2)
//        {
//            button->setOpacity(50);
//            button->setColor(Color3B(0, 0, 255));
//        }
        button->setPosition(Vec2 (screenSize.width / 2, offsetY + total_height + button->getContentSize().height / 2));
        this->addChild(button);
        
        // Compute the size of the layer
        height = button->getContentSize().height;
        width = button->getContentSize().width;
        total_height += button->getContentSize().height;
        total_width += button->getContentSize().width;
        i++;
    }
    
    layer->setAnchorPoint(Vec2 (0.5, 0.5));
    layer->setContentSize(CCSize(total_width, height));
    layer->setPosition(Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f));
    
    //        // Add the black background
    //        auto background = Scale9Sprite::create("extensions/buttonBackground.png");
    //        background->setContentSize(Size(total_width + 14, height + 14));
    //        background->setPosition(Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f));
    //        addChild(background);
    return false;
}

ControlButton *BallGameScene::standardButtonWithTitle(const char * title)
{
    /** Creates and return a button with a default background and title color. */
    auto backgroundButton = Scale9Sprite::create("Images/buttonbg.png");
    auto backgroundHighlightedButton = Scale9Sprite::create("Images/buttonbg.png");
    
    auto titleButton = Label::createWithTTF(title, "fonts/Marker Felt.ttf", 30);
    
    //    titleButton->setColor(Color3B(159, 168, 176));
    
    ControlButton *button = ControlButton::create(titleButton, backgroundButton);
    button->setBackgroundSpriteForState(backgroundHighlightedButton, Control::State::HIGH_LIGHTED);
    button->setTitleColorForState(Color3B::WHITE, Control::State::HIGH_LIGHTED);
    button->setPreferredSize(CCSize(400,150));
    return button;
}

void BallGameScene::touchDownAction(Ref *senderz, Control::EventType controlEvent)
{
     Node* pNode = ((Node*)senderz);
     int tag = pNode->getTag();
    switch (tag)
    {
        case 0:
            log("dfsfs");
            break;
            
        default:
            break;
    }
}

/*
 * 分享回调, 该回调不是某个类的成员函数， 而是一个普通的函数, 具体使用参考HelloWorldScene的例子
 * @param platform 要分享到的目标平台
 * @param stCode 返回码, 200代表分享成功, 100代表开始分享
 * @param errorMsg 分享失败时的错误信息,android平台没有错误信息
 */
