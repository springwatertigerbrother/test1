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
    CCLabelTTF* m_labelTotalScoreTitle;
    CCMenuItemImage * m_scoreItem;
    CCMenuItemImage * m_timeItem;
public:
    virtual bool init();
    CREATE_FUNC(UpStateLayer);

    void startAnimationDisplay();
    void AfterStartAnimationDisplayCall();


void resetTimeString(CCString* string);
void resetScoreString(CCString* string);
void menuBePressed(Ref* pSender);
void startAnimationDisplay(Ref* pSender);
    
};
#endif /* defined(__changeableball__DataUpdateLayer__) */
