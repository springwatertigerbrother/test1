//
//  DataManager.h
//  changeableball
//
//  Created by huge on 3/9/14.
//
//

#ifndef __changeableball__DataManager__
#define __changeableball__DataManager__

#include <iostream>
#include "cocos2d.h"
#include "config.h"
#include "BallSprite.h"
//#include "GameCenterScene.h"

#define  BALLVEC std::vector<BallSprite*>

using namespace cocos2d;

class DataManager:public CCLayer
{
public:
//    CCArray* m_ballSpriteArray;
    virtual bool init();
    DataManager();
    virtual ~DataManager();
    CREATE_FUNC(DataManager);
    
//    virtual void draw();
    virtual void draw(cocos2d::Renderer *renderer,const cocos2d::Mat4& transform,uint32_t flags);

    std::vector<BallSprite*> m_ballSpriteArray;

    ccColor4F m_currentDrawColor;
    int m_TypeArray[TOTALX][TOTALY];//zhao
    int m_lastNum;
    std::vector<BallSprite*> m_stackArray;
    
    bool m_drawLine;
    
    bool m_objectHasContina;
    
    bool m_removeAllSameColor;
    
    bool m_toolsDisappear;
    
    bool m_toolsDisappearType;
    
    bool m_canPlaying;
    
    CCPoint m_movePos;
    CC_SYNTHESIZE_READONLY(CCLayerColor*,mCoreLayer,CoreLayer);

    void startAnimtionDisplay();
    void startPlaying();
    bool touchBegine(CCPoint local);
    void touchMove(CCPoint local);
    void touchEnd(CCPoint local);
    void disappearEnd();// 消除结束

    bool allDrawNodeBeSelected(bool disappearType);//全部选中
    BallSprite* getLastSelected(); //获取最后一个被选中的
    
    //-(void) cancelAllDrawNodeBeSelected;// 取消全部选中的情况
    
    void moveOut();
    void moveIn();
    
    int changeArray();
    void loadEffectSounds();
    
    BallSprite* getCurrentSelectSprite(CCPoint pos);
    int disappearAllSameColorDotsWithSelected();
    bool containObject(BallSprite* object,std::vector<BallSprite*> container);
    void hideScoreEffect(CCNode* pSender);
    void calcDropDownResultArray (BallSprite* ball,std::vector<BallSprite*> &resultArray);
    void cancelAllDrawNodeBeSelected();
    
//    virtual void registerWithTouchDispatcher(void);
//    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
//
    
    bool onTouchBegan(Touch *touch, Event *unused_event);
    void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);
    
    void playingSound(int count,int nType);
    
    void metetors();
    //判断是否还有可消除的
    int shuzu[6][6];
    int sum[6][6];
    void printXiaoChu();
    void clear();
    //mark all
    int markMinusOne(int i,int j);
    void findNeighborMark(int i,int j,int color);
    void printXiaoChu(int shuzu[6][6]);
    bool enableDispel();
    
    // init elements
    void initElements();
    
    // tools
    void selectedTool(void* sender);
    void useWave(CCPoint local);
    void usebomb(CCPoint local);
    void superTool(CCPoint local);
    int m_selectedTool;
    void useTool(CCPoint local);
    void useSuperTool(Ref* obj);
    
    CCSprite* m_pBg;
    CCSprite* m_pGood;
    //draw line
    DrawNode* m_pDrawNode;
    
    CCLabelTTF* m_pTotalScoreLabel;
    CCLabelTTF* m_pLabelHelp;
    LayerColor* m_helpLayer;
    void help(void* sender);
    ParticleSystemQuad*    _emitter;
    ParticleSystemQuad*    super_emitter;
    ccColor4F calcColorWithType(int nType);

    void waveChangeType(Node* pNode);
    void waveParticles(Node* pNode);
    void changeAllElements(Node* pNode);
    void consumeDiamond(int nDiamond);
    void removeSelf(Node* pNode);
    void removeSuperEffect(Node* pNode);
    void back(void* sender);

};

#endif /* defined(__changeableball__DataManager__) */
