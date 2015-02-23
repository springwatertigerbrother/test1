//
//  BallSprite.cpp
//  changeableball
//
//  Created by huge on 3/9/14.
//
//

#include "BallSprite.h"
#include "DataManager.h"
#include "config.h"
#include "DataHome.h"

#define caleActiontag 100

int zoomvalue = DataHome::getInstance()->wZoomvalue;
float wFontSize = DataHome::getInstance()->wFontSize;

BallSprite::BallSprite()
{

}
BallSprite:: ~BallSprite()
{

}
CCPoint BallSprite:: calcPos(int x ,int y)
{
    
    float width = this->getAnchorPoint().x * m_w + x * m_w +addWidth;
    float height = this->getAnchorPoint().y * m_h + y * m_h +AddHeigh;
    return ccp(width, height);
}

void BallSprite::calcColor()
{
    int type = arc4random()%TOTAL_TYPE;
    switch (type) {
        case 0:
            m_BallColor = ccc4fBlue;
            m_type = 1;
            break;
        case 1:
            m_BallColor = ccc4fGreen;   m_type = 2;
            break;
        case 2:
            m_BallColor = ccc4fRed;  m_type = 3;
            break;
        case 3:
            m_BallColor = ccc4fPurple;  m_type = 4;
            break;
        case 4:
            m_BallColor = ccc4fOrange;  m_type = 5;
            break;
            
        default:
            m_BallColor = ccc4fPurple;  m_type = 6;
            break;
    }
}


 void BallSprite::spawnAtXY(int x ,int y, float w, float h)
{
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    float nZoomFactor = size.width/320;
    m_hasSelected = true;
    m_disappear = false;
    m_x = x;
    m_y = y;
    
    m_w = w*2*nZoomFactor;
    m_h = h*2*nZoomFactor;
    
    calcColor();
    
    //    [self setContentSize:CGSizeMake(DRAWSPRITE_RADIUES*zoomvalue, DRAWSPRITE_RADIUES*zoomvalue)];
    
    float wd = this->getAnchorPoint().x * m_w + x * m_w+addWidth;
    
    //zhao
    CCString* typeStr = CCString::createWithFormat("%d",m_type);

    m_drawNode = CCDrawNode::create();
    m_ValueLabel = CCLabelTTF::create();
    m_ValueLabel->setString(typeStr->getCString());
    m_ValueLabel->setFontSize(wFontSize);
    m_drawNode-> addChild(m_ValueLabel);
    
//    if (m_ValueLabel)
//    {
//        auto action1 = ScaleBy::create(0.3, 1.1);
//        auto seq = Sequence::create(action1,action1->reverse(), NULL);
//        m_ValueLabel->runAction(RepeatForever::create(seq));
//    }

    m_drawNode-> setPosition(ccp(wd, size.height/2));
    
    
    m_drawNode->setContentSize(CCSizeMake(DRAWSPRITE_RADIUES*zoomvalue, DRAWSPRITE_RADIUES*zoomvalue));
    
    addChild(m_drawNode);
    
    m_drawNode->drawDot(ccp(0, 0),DRAWSPRITE_RADIUES*zoomvalue,m_BallColor);
    
    m_selectNode = CCDrawNode::create();
    m_drawNode->addChild(m_selectNode);
    
    ccColor4F col = ccc4f(m_BallColor.r, m_BallColor.g, m_BallColor.b, 255*0.75);
    
    m_selectNode->drawDot(ccp(0, 0),DRAWSPRITE_RADIUES*zoomvalue,col);
    m_selectNode->setVisible(false);
    //    [m_drawNode clear];
}

void BallSprite::respawn()
{
    
    m_disappear = false;
    m_drawNode->stopAllActions();
    m_drawNode-> clear();
    m_drawNode->setScale(1.0f);
    
    m_selectNode-> clear();
    m_selectNode->setScale(1.0);
    
    calcColor();
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    float wd = getAnchorPoint().x * m_w + m_x * m_w +addWidth;
    
    CCString* typeStr = CCString::createWithFormat("%d",m_type);
    
    //zhao
    if (m_ValueLabel)
    {
        m_ValueLabel->setString(typeStr->getCString());
        m_ValueLabel->setFontSize(wFontSize);
    }
    m_drawNode-> setPosition(ccp(wd, size.height));
    
    m_drawNode->drawDot(this->getPosition(), DRAWSPRITE_RADIUES*zoomvalue,m_BallColor);
    
    ccColor4F col = ccc4f(m_BallColor.r, m_BallColor.g, m_BallColor.b, 255*0.75);
    
    m_selectNode->drawDot(ccp(0, 0),DRAWSPRITE_RADIUES*zoomvalue,col);
    
    respawnDropdown();
}


void BallSprite::spawnDropdown()
{
    m_dropCount = 0;
    
    stopAllActions();
    
    CCPoint pos = calcPos(m_x,m_y);
    
    CCDelayTime * wait = CCDelayTime::create(m_y*SPAWN_DROPDOWN_TIME/5);
    
    CCMoveTo * moveto = CCMoveTo::create(SPAWN_DROPDOWN_TIME/2 ,pos);
    
    CCJumpTo * jump = CCJumpTo::create(SPAWN_JUMP_TIME,pos,30,1);
    
    CCCallFunc* callB = CCCallFunc::create(this, callfunc_selector(BallSprite::spawnDropDownCallBack));
    
    CCSequence * seq = CCSequence::create(wait,moveto,jump,callB, NULL);
    
    m_drawNode->runAction(seq);
}
void BallSprite::spawnDropDownCallBack()
{
    m_hasSelected = false;
    this->setVisible(true);
}

void BallSprite::respawnDropdown()
{
    m_dropCount = 0;
    
    stopAllActions();
    
    CCPoint pos = calcPos(m_x,m_y);
    
    //    CCActionInterval * wait = [CCActionInterval actionWithDuration:m_y*SPAWN_DROPDOWN_TIME/5];
    
    CCMoveTo * moveto = CCMoveTo::create( SPAWN_DROPDOWN_TIME/3,pos);
    
    CCJumpTo * jump = CCJumpTo::create(SPAWN_JUMP_TIME/3*2,pos,20,1);
    
    CCCallFunc* callB = CCCallFunc::create(this, callfunc_selector(BallSprite::respawnDropdownCallBack));

    
    CCSequence * seq = CCSequence::create(moveto,jump,callB,NULL);
    
    m_drawNode->runAction(seq);
}
void BallSprite:: respawnDropdownCallBack()
{
    m_hasSelected = false;
    this->setVisible(true);
}


void BallSprite::resetPropertyAxY(int x,int y)
{
    if (y <m_y) {
        m_dropCount ++;
    }
    m_x = x;
    m_y = y;
}
void BallSprite::resetDropdown()// 重置后掉落函数
{
    m_hasSelected = true;
    
    CCPoint pos = calcPos(m_x,m_y);
    
    CCMoveTo *moveto = CCMoveTo::create(RESET_DROPDOWN_TIME,pos);
    
    CCJumpTo * jump = CCJumpTo::create(RESET_JUMP_TIME/3,pos,15,1);
    CCCallFunc* callB = CCCallFunc::create(this, callfunc_selector(BallSprite::resetDropdownCallBack));
    
    CCSequence * seq = CCSequence::create( moveto, jump, callB, NULL);
    
    m_drawNode-> runAction(seq);
    m_dropCount = 0;
}
void BallSprite::resetDropdownCallBack()
{
    m_hasSelected = false;
}

bool BallSprite::positionInContent(CCPoint pos)
{
    //
    //    CGFloat width = DRAWSPRITE_WIDTH;
    //    CGFloat height = DRAWSPRITE_HEIGH;
    
    float orgx = m_drawNode->getPosition().x - DRAWSPRITE_WIDTH;
    float orgy = m_drawNode->getPosition().y - DRAWSPRITE_HEIGH;
    
    CCRect rect = CCRectMake(orgx, orgy, DRAWSPRITE_WIDTH*2, DRAWSPRITE_HEIGH*2);
    
    return  rect.containsPoint(pos);;
}

bool BallSprite::selectedType()
{
    
    m_hasSelected = true;
    
    m_selectNode->stopAllActions();
    m_selectNode->setScale(1.0);
    m_selectNode->setVisible(true);
    
    CCScaleBy * scaleBy = CCScaleBy::create(0.1,2.0);
    CCCallFunc* callB = CCCallFunc::create(this, callfunc_selector(BallSprite::selectedTypeCallback));
    
    CCSequence * seq = CCSequence::create(scaleBy,scaleBy->reverse(), callB, NULL);
    seq->setTag(caleActiontag);
    m_selectNode->runAction(seq);
    
    return true;
}
void BallSprite::selectedTypeCallback()
{
    m_selectNode->setVisible(false);
}

void BallSprite::disappear(bool callf)
{
    CCScaleBy * scaleBy = CCScaleBy::create(0.1, 1.5);
    CCScaleBy * scaleBy2 = CCScaleBy::create(0.2 ,0);
    CCSequence * seq = NULL;
    
    if (callf) {
        CCCallFunc* callB = CCCallFunc::create(this, callfunc_selector(BallSprite::disappearCallback));

        seq = CCSequence ::create(scaleBy,scaleBy2,callB, NULL);
    }else{
        seq = CCSequence ::create(scaleBy,scaleBy2, NULL);
    }
    
    m_disappear = true;
    
    m_drawNode->runAction(seq);
}
void BallSprite::disappearCallback()
{
    if (this->getParent())
    {
        DataManager* pData = (DataManager*)this->getParent();
        pData->disappearEnd();
    }
}

void BallSprite::unselected()
{
    m_hasSelected = false;
}

CCPoint BallSprite::getDrawNodePosition()
{
    return m_drawNode->getPosition();
}


void BallSprite::KeepSelected()
{
    m_hasSelected = true;
    
    m_selectNode->stopAllActions();
    
    m_selectNode->setVisible(true);
    
    CCScaleBy * scaleBy = CCScaleBy::create (0.1,1.7);
    
    m_selectNode->runAction(scaleBy);
}

void BallSprite::unKeepSelected()
{
    
    m_hasSelected = false;
    m_selectNode->stopAllActions();
    
    CCScaleTo * scaleTo = CCScaleTo::create(0.1,1.0);
    CCCallFunc* callB = CCCallFunc::create(this, callfunc_selector(BallSprite::unKeepSelectedCallback));
    
    CCSequence * seq = CCSequence::create(scaleTo, callB, NULL);
    seq->setTag(caleActiontag);
    m_selectNode->runAction(seq);
}
void  BallSprite::unKeepSelectedCallback()
{
    m_selectNode->setVisible(false);
}
void BallSprite::BallSprite::changeType(int nNum)
{
    //    int nType = ChangedSprite.m_type;
    //    if (nType < 5) {
    //        nType++;
    //    }
    //    ChangedSprite.m_type = nType;
    
    if (m_type < MAX_TYPE_VALUE) {
        if (nNum >= CONTINIOUS_NUM) {
            m_type = m_type - 2 + nNum ;
            if (m_type > MAX_TYPE_VALUE) {
                m_type = MAX_TYPE_VALUE;
            }
        }
    }
    //self.scaleX = 1.5;
    int type = m_type - 1;
    switch (type) {
        case 0:
            m_BallColor = ccc4fBlue;
            //m_type = 1;
            break;
        case 1:
            m_BallColor = ccc4fGreen;   //m_type = 2;
            break;
        case 2:
            m_BallColor = ccc4fRed;  //m_type = 3;
            break;
        case 3:
            m_BallColor = ccc4fPurple; // m_type = 4;
            break;
        case 4:
            m_BallColor = ccc4fOrange;  //m_type = 5;
            break;
            
        default:
            m_BallColor = ccc4fPurple;  //m_type = 6;
            break;
    }
    
    m_drawNode->drawDot(this->getPosition(),DRAWSPRITE_RADIUES*zoomvalue,m_BallColor);
    
    ccColor4F col = ccc4f(m_BallColor.r, m_BallColor.g, m_BallColor.b, 255*0.75);
    
    m_selectNode->drawDot(ccp(0, 0),DRAWSPRITE_RADIUES*zoomvalue,col);
    
    CCString* typeStr = CCString::createWithFormat("%d",m_type);
    if (m_ValueLabel)
    {
        m_ValueLabel->setString(typeStr->getCString());
        m_ValueLabel->setFontSize(wFontSize);
    }
}



