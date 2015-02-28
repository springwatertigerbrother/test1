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
        CCLayerColor* pBGLayer = CCLayerColor::create(ccc4(1,2,3,4));
//        pBGLayer->initWithColor(ccc4(111, 155, 160, 133));

        pBGLayer->setAnchorPoint(CCPoint(0,0));
        addChild(pBGLayer);

    }
    while(0);
    return true;
}



void BallGameScene::onEnter()
{
    
    CCLayer::onEnter();
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* pBg4 = Sprite::create("images/bg4.png");
    pBg4->setPosition(ccp(size.width/2,size.height/2));
    addChild(pBg4);
    pBg4->setScale(get_content_scale_factor(), get_content_scale_factor());
    
//    CCSprite* pBg = Sprite::create("images/aiyisitanfudiao.png");
    CCSprite* pBg = Sprite::create("images/aystthinging.png");
    pBg->setPosition(ccp(size.width/2,size.height/1.2));
    pBg->setOpacity(200);
    pBg->setScale(CC_CONTENT_SCALE_FACTOR());
    addChild(pBg);

    CCSprite* pemc2 = Sprite::create("images/emc2.png");
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
    
    menu->setPosition(ccp(size.width/2,size.height/3));
    
    
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

    MenuItemFont::setFontName("American Typewriter");
    MenuItemFont::setFontSize(30);
    auto title1 = MenuItemFont::create("Sound");
    title1->setEnabled(false);
    MenuItemFont::setFontName( "fonts/Marker Felt.ttf" );
    MenuItemFont::setFontSize(50);
    auto item1 = MenuItemToggle::createWithCallback( CC_CALLBACK_1(BallGameScene::musicControl, this),
                                                    MenuItemFont::create( "music On" ),
                                                    MenuItemFont::create( "music Off"),
                                                    nullptr );
    item1->setEnabled(true);
    auto musciMenu = Menu::create(item1, nullptr);
    musciMenu->setPosition(ccp(size.width/2,size.height/5));
    
    //            musciMenu->alignItemsInColumns(2, 2, 2, 2, 1, NULL);
//    musciMenu->setVisible(false);
    addChild( musciMenu );

    
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
    DataHome::getInstance()->isCountDownModel = true;
    
    CCScene * playingScene = GameCenterScene::scene();
    CCDirector::sharedDirector()->replaceScene(playingScene);
    
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
