//
//  DataUpdateLayer.h
//  changeableball
//
//  Created by huge on 6/9/14.
//
//

#ifndef __changeableball__DataUpdateLayer__
#define __changeableball__DataUpdateLayer__
#include"cocos2d.h"

#include <iostream>
USING_NS_CC;

class UpStateLayer :public cocos2d::CCLayerColor {
    
    CCLabelTTF * m_labelTime;
    CCLabelTTF * m_labelScore;
    CCLabelTTF* m_labelNciyuanTitle;
    CCLabelTTF* m_labelNValue;
    CCLabelTTF* m_labelCurrentNciyuanTitle;
    CCLabelTTF* m_labelCurrentNValue;
    CCLabelTTF* m_labelTotalScoreTitle;
    CCLabelTTF* m_labelCurrentScoreTitle;
    CCLabelTTF* m_labelCurrentScoreValue;
    CCLabelTTF* m_labelCountDown;
    CCLabelTTF * m_labelDiamond;
    
    void reload(Ref* obj);

    CCMenuItemImage * m_scoreItem;
    CCMenuItemImage * m_timeItem;
    
    CCSprite* m_pAiyinsitan;

public:
    virtual bool init();
    CREATE_FUNC(UpStateLayer);

    void startAnimationDisplay();
    void AfterStartAnimationDisplayCall();


void resetTimeString(CCString* string);
    void resetScoreString(CCString* string);
    void resetScoreWithIntValue(unsigned long nValue);
    void resetCurrentScoreWithIntValue(unsigned long nValue);
    void resetCunntDownWithIntValue(unsigned long nValue);
void menuBePressed(Ref* pSender);
void startAnimationDisplay(Ref* pSender);
    void musicControl(Ref* pSender);
//    void removeSelf(Node* pNode);
};
#endif /* defined(__changeableball__DataUpdateLayer__) */
