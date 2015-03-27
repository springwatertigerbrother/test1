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

// 引入相关的头文件
#include "Cocos2dx/Common/CCUMSocialSDK.h"
#include "Cocos2dx/ShareButton/UMShareButton.h"
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


using namespace cocos2d;

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

        
        // 创建分享按钮, 参数1为按钮正常情况下的图片, 参数2为按钮选中时的图片,参数3为友盟appkey, 参数4为分享回调
        UMShareButton *shareButton = UMShareButton::create("Images/share.png","Images/share.png", "你的友盟appkey", share_selector(shareCallback)) ;
        
        CCUMSocialSDK *sdk = shareButton->getSocialSDK();
        // sdk->setQQAppIdAndAppKey("设置QQ的app id", "appkey");
        sdk->setWeiXinAppInfo("wx4709b0db1758b611",
                              "e3bea36c663071278e45440d6e00f7c5");
        // 显示在友盟分享面板上的平台
        vector<int>* platforms = new vector<int>();
        platforms->push_back(SINA);
        platforms->push_back(RENREN) ;
        platforms->push_back(DOUBAN) ;
//        platforms->push_back(QZONE) ;
//        platforms->push_back(QQ) ;
        platforms->push_back(WEIXIN);
        platforms->push_back(WEIXIN_CIRCLE);
        platforms->push_back(FACEBOOK);

        // 设置友盟分享面板上显示的平台
        shareButton->setPlatforms(platforms);
        // 设置文本分享内容
        shareButton->setShareContent("我在 n 次元 游戏中已经进入了　%d，小伙伴你呢？？？") ;
        // 设置要分享的图片, 图片支持本地图片和url图片, 但是url图片必须以http://或者https://开头
//        shareButton->setShareImage("/sdcard/header.jpeg") ;
        shareButton->setShareImage("Images/emc2.png") ;
//        sdk->openShare("我在 n 次元 游戏中已经进入了　%d，小伙伴你呢？？？","Images/emc2.png", share_selector(shareCallback));

        // 设置按钮的位置
        shareButton->setPosition(ccp(150, 180));
        // 然后开发者需要将该按钮添加到游戏场景中
        CCMenu* pMenu = CCMenu::create(shareButton, NULL);
        pMenu->setPosition(CCPointZero);
        this->addChild(pMenu, 1);
        
        // ********************** 设置平台信息 ***************************
//         CCUMSocialSDK *sdk = shareButton->getSocialSDK();
//        // sdk->setQQAppIdAndAppKey("设置QQ的app id", "appkey");
//         sdk->setWeiXinAppInfo("设置微信和朋友圈的app id","app key");
        // sdk->setYiXinAppKey("设置易信和易信朋友圈的app id");
        // sdk->setLaiwangAppInfo("设置来往和来往动态的app id",
        //                  "设置来往和来往动态的app key", "我的应用名");
        // sdk->setFacebookAppId("你的facebook appid");
        // 设置用户点击一条图文分享时用户跳转到的目标页面, 一般为app主页或者下载页面
        // sdk->setTargetUrl("http://www.umeng.com/social");
        //     // 打开或者关闭log
        // sdk->setLogEnable(true) ;
        // **********************   END ***************************
        
    }
    while(0);
    return true;
}



void BallGameScene::onEnter()
{
    
    CCLayer::onEnter();
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* pBg4 = Sprite::create("Images/bg4.png");
    pBg4->setPosition(ccp(size.width/2,size.height/2));
    pBg4->setOpacity(230);
    addChild(pBg4);
    pBg4->setScale(get_content_scale_factor(), get_content_scale_factor());
    
//    CCSprite* pBg = Sprite::create("Images/aiyisitanfudiao.png");
    CCSprite* pBg = Sprite::create("Images/aystthinging.png");
    pBg->setAnchorPoint(ccp(0.5,1));
    pBg->setPosition(ccp(size.width/2,size.height));
    pBg->setOpacity(200);
    pBg->setScale(CC_CONTENT_SCALE_FACTOR());
    addChild(pBg);

    CCSprite* pemc2 = Sprite::create("Images/emc2.png");
    pemc2->setPosition(ccp(size.width/2,size.height/1.3));
    pemc2->setScale(CC_CONTENT_SCALE_FACTOR());
    addChild(pemc2);

    pemc2->setAnchorPoint(ccp(-0.5,-0.5));
    pemc2->runAction(RepeatForever::create(RotateBy::create(10, 360) ) );
    
    m_playnow = CCMenuItemImage::create("Images/startStandard.png","Images/startStandard.png", CC_CALLBACK_1(BallGameScene::playingNow,this));
    m_playnow->setScale(CC_CONTENT_SCALE_FACTOR());
    m_multiplayer = CCMenuItemImage::create("Images/countdown.png","Images/countdown.png",CC_CALLBACK_1(BallGameScene::multiplePlayer,this));
    m_multiplayer->setScale(CC_CONTENT_SCALE_FACTOR());
//    
//    m_highscore = CCMenuItemImage::create("Images/high_score.png","Images/high_score.png",CC_CALLBACK_1(BallGameScene::highScore,this));
//    
//    m_settings = CCMenuItemImage::create("Images/settings.png","Images/settings.png", CC_CALLBACK_1(BallGameScene::settings,this));
//    
//    m_aboutus = CCMenuItemImage::create("Images/about_us.png","Images/about_us.png", CC_CALLBACK_1(BallGameScene::aboutus,this));
    
    CCMenu *menu = CCMenu::create(m_playnow,m_multiplayer, NULL);
    
    menu->alignItemsVerticallyWithPadding(10);
    
    menu->setPosition(ccp(size.width/2,size.height/5));
    
    
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

    
    this-> addChild(menu);
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

void BallGameScene:: multiplePlayer(void* sender)
{
    
    
    if(0)
    {
        IOSiAP_Bridge* bridge = new IOSiAP_Bridge();
        bridge->requestProducts(6);
    }
    if(1)
    {
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
    
    // sdk->setYiXinAppKey("设置易信和易信朋友圈的app id");
    // sdk->setLaiwangAppInfo("设置来往和来往动态的app id",
    //              "设置来往和来往动态的app key", "我的应用名");
    // sdk->setFacebookAppId("你的facebook appid");
    //     // 打开或者关闭log
    // sdk->setLogEnable(true) ;
    // **********************   END ***************************
    
    // 设置用户点击一条图文分享时用户跳转到的目标页面, 一般为app主页或者下载页面
    sdk->setTargetUrl("http://www.umeng.com/social");
    // 设置友盟分享面板上显示的平台
    vector<int>* platforms = new vector<int>();
    platforms->push_back(SINA);
    platforms->push_back(RENREN) ;
    platforms->push_back(WEIXIN_CIRCLE) ;
    platforms->push_back(FACEBOOK);
    platforms->push_back(QZONE) ;
    platforms->push_back(QQ) ;
    platforms->push_back(DOUBAN) ;

    // 设置平台, 在调用分享、授权相关的函数前必须设置SDK支持的平台
    sdk->setPlatforms(platforms) ;
    
    // 打开分享面板, 注册分享回调, 参数1为分享面板上的平台, 参数2为要分享的文字内容，
    // 参数3为要分享的图片路径(android和IOS的图片地址格式不一致，因此分平台设置), 参数4为分享回调.
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    sdk->openShare("我在 n 次元 游戏中已经进入了　%d，小伙伴你呢？？？", "/sdcard/image.png", share_selector(shareCallback));
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    sdk->setPlatformShareContent(WEIXIN_CIRCLE,"我在 n 次元 游戏中已经进入了　%d，小伙伴你呢？？？","Images/emc2.png");
    sdk->openShare("我在 n 次元 游戏中已经进入了　%d，小伙伴你呢？？？",outputFile.c_str(), share_selector(shareCallback));
#endif
    }
//
//    DataHome::getInstance()->isCountDownModel = true;
//    
//    CCScene * playingScene = GameCenterScene::scene();
//    CCDirector::sharedDirector()->replaceScene(playingScene);
    
    //    [[NetWorkHandle getSharedNetWork] startMatchOppoent:self];
//    CCScene * playingScene = MutablePlayerScene node];
//    
//    [[CCDirector sharedDirector] pushScene:[CCTransitionMoveInR transitionWithDuration:0.2 scene:playingScene]];
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

/*
 * 分享回调, 该回调不是某个类的成员函数， 而是一个普通的函数, 具体使用参考HelloWorldScene的例子
 * @param platform 要分享到的目标平台
 * @param stCode 返回码, 200代表分享成功, 100代表开始分享
 * @param errorMsg 分享失败时的错误信息,android平台没有错误信息
 */
