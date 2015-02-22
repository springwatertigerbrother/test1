//
//  ballGamescene.cpp
//  changeableball
//
//  Created by mac on 14-9-6.
//
//

#include "ballGamescene.h"
#include "GameCenterScene.h"

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
    
    m_playnow = CCMenuItemImage::create("Images/play_now.png","Images/play_now.png", CC_CALLBACK_1(BallGameScene::playingNow,this));
    
    m_multiplayer = CCMenuItemImage::create("Images/multiple_player.png","Images/multiple_player.png",CC_CALLBACK_1(BallGameScene::multiplePlayer,this));
    
    m_highscore = CCMenuItemImage::create("Images/high_score.png","Images/high_score.png",CC_CALLBACK_1(BallGameScene::highScore,this));
    
    m_settings = CCMenuItemImage::create("Images/settings.png","Images/settings.png", CC_CALLBACK_1(BallGameScene::settings,this));
    
    m_aboutus = CCMenuItemImage::create("Images/about_us.png","Images/about_us.png", CC_CALLBACK_1(BallGameScene::aboutus,this));
    
    CCMenu *menu = CCMenu::create(m_playnow, m_multiplayer,
                    m_highscore, m_settings, m_aboutus, NULL);
    
    menu->alignItemsVerticallyWithPadding(10);
    
    menu->setPosition(ccp(size.width/2,size.height/3));
    
    this-> addChild(menu);
}


void BallGameScene:: startGame()
{
    
    this-> removeAllChildren();
    
}


void BallGameScene:: playingNow(void* sender)
{
    
    CCScene * playingScene = GameCenterScene::scene();
    CCDirector::sharedDirector()->replaceScene(playingScene);
//    [[CCDirector sharedDirector] replaceScene:[CCTransitionMoveInR transitionWithDuration:0.2 scene:playingScene]];
}

void BallGameScene:: multiplePlayer(void* sender)
{
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

