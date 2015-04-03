//
//  BuyLifeLayer.h
//  changeableball
//
//  Created by huge on 7/3/15.
//
//

#ifndef __changeableball__BuyLifeLayer__
#define __changeableball__BuyLifeLayer__
#include"cocos2d.h"

#include <iostream>
USING_NS_CC;
class BuyLifeLayer :public cocos2d::CCLayer
{
    cocos2d::CCMenuItemImage * m_BuyItem;
    cocos2d::CCMenuItemImage * m_UseLife;
    cocos2d::CCMenuItemImage * m_GameOver;
    
    cocos2d::CCMenuItemImage * m_iap6;
    
    cocos2d::CCMenuItemImage * m_iap18;
    cocos2d::CCMenuItemImage * m_iap24;
    CCMenu *m_shopMenu;

    virtual void onEnter();
    virtual bool init();

    void CallBuyLife(void* sender);
    void CallUseLife(void* sender);
    void gameOver(void* sender);
    CCLabelTTF * m_labelDiamond;

public:
    CREATE_FUNC(BuyLifeLayer);

};

#endif /* defined(__changeableball__BuyLifeLayer__) */
