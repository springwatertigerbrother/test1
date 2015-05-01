//
//  AlertLayer.h
//  changeableball
//
//  Created by huge on 15/5/1.
//
//

#ifndef __changeableball__AlertLayer__
#define __changeableball__AlertLayer__

#include"cocos2d.h"

#include <iostream>
USING_NS_CC;
class AlertLayer :public cocos2d::CCLayer
{
    cocos2d::CCMenuItemImage * m_BuyItem;
    cocos2d::CCMenuItemImage * m_UseLife;
    cocos2d::CCMenuItemImage * m_GameOver;
    
    cocos2d::CCMenuItemImage * m_iap6;
    
    cocos2d::CCMenuItemImage * m_iap18;
    cocos2d::CCMenuItemImage * m_iap68;
    CCMenu *m_shopMenu;
    
    CCLabelTTF* pLabelUpload;
    
    virtual void onEnter();
    virtual bool init();
    
    void CallBuyLife(void* sender);
    void CallUseLife(void* sender);
    void gameOver(void* sender);
    CCLabelTTF * m_labelDiamond;
    
    void reload(Ref* obj);
public:
    CREATE_FUNC(AlertLayer);
    
};

#endif /* defined(__changeableball__AlertLayer__) */
