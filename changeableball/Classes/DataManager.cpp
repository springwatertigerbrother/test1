//
//  DataManager.cpp
//  changeableball
//
//  Created by huge on 3/9/14.
//
//
#include "config.h"
#include "DataManager.h"
#include <algorithm>
#include "SimpleAudioEngine.h"
#include "GameCenterScene.h"
#include "GameOverLayer.h"

static inline int calcIndex(int x,int y){
    return TOTALX * y + x;
}


void DataManager::printXiaoChu(int shuzu[6][6]){
    for(int i=0;i<6;i++){
        
        for(int j=0;j<6;j++){
            
            
            std::cout<<shuzu[j][i]<<'\t';
        }
        std::cout<<std::endl;
    }
    
}

void DataManager::clear(){
    
    for(int i=0;i<6;i++){
        
        for(int j=0;j<6;j++){
            
            
            if(shuzu[i][j]==-1){
                continue;
            }
            markMinusOne(i,j);
            //cout<<shuzu[j][i]<<" ";
        }
    }
}
//mark all
int DataManager::markMinusOne(int i,int j){
    
    int color=shuzu[i][j];
    sum[i][j]=0;
    if(i>=0&&i<6	&&j>= 0	&&j< 6){}else{return 11;}
    if(i-1>=0 && color==shuzu[i-1][j]){
        
        
        sum[i][j]++;
    }
    if(i+1<6 &&color==shuzu[i+1][j] ){
        sum[i][j]++;
        
    }
    if(j-1>=0&&color==shuzu[i ][j-1]  ){
        sum[i][j]++;
        
    }
    if(j+1<6&&color==shuzu[i ][j+1]  ){
        sum[i][j]++;
        
    }
    
    if(sum[i][j]>=2){
        findNeighborMark(i,j,color);
    }
}


void DataManager::findNeighborMark(int i,int j,int color){
    if(i>=0&&i<6	&&j>= 0	&&j< 6){}else{return ;}
    if(shuzu[i][j]==color){
        
        shuzu[i][j]=-1;
        findNeighborMark(i-1,j,color);
        findNeighborMark(i+1,j,color);
        findNeighborMark(i,j-1,color);
        findNeighborMark(i,j+1,color);
        
    }
}

bool DataManager::enableDispel()
{
    for(int i = 0;i < TOTALX;i++)
        for(int j = 0;j <TOTALY;j++)
        {
            if(shuzu[i][j] == -1)
                return true;
        }
    return false;
}
DataManager::DataManager()
{
    m_drawLine = false;
}
bool DataManager::containObject(BallSprite* object,std::vector<BallSprite*> container)
{
    std::vector<BallSprite*>::iterator it;

    for (it = container.begin(); it != container.end(); it++)
    {
        if (*it == object)
        {
            return true;
        }
        
    }
    return false;
}
void DataManager::initElements()
{
    for(int i = 0; i<m_ballSpriteArray.size();i++)
    {
        ((BallSprite*) m_ballSpriteArray[i])->removeFromParentAndCleanup(true);
    }
    m_ballSpriteArray.clear();
    
    if (mCoreLayer)
    {
        for (int y = 0; y<TOTALY; y++) {
            for (int x = 0; x<TOTALX; x++) {
                
                BallSprite * drawS = BallSprite::create();
                
                drawS->spawnAtXY(x, y, DRAWSPRITE_WIDTH,DRAWSPRITE_HEIGH);
                m_TypeArray[x][y] = drawS->getType();
                m_ballSpriteArray.push_back(drawS);
                addChild(drawS);
            }
        }
        m_stackArray.clear();
    }
    
    for (int i = 0; i< m_ballSpriteArray.size(); i++) {
        
        BallSprite * ds = (BallSprite*)m_ballSpriteArray[i];
        
        m_TypeArray[i%TOTALX][i/TOTALY] = ds->getType();
        shuzu[i%TOTALX][i/TOTALY] = m_TypeArray[i%TOTALX][i/TOTALY];
        
    }
    this->clear();
    if(!enableDispel())
    {
        initElements();
    }
}
bool DataManager::init()
{
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(DataManager::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(DataManager::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(DataManager::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    mCoreLayer = CCLayerColor::create(ccc4(255, 255, 255, 255));//WithColor:ccc4(230, 230, 230, 255)
    if ( !mCoreLayer )
    {
        return false;
    }
    if (mCoreLayer)
    {
//        mCoreLayer->setTouchEnabled(true);
//        addChild(mCoreLayer);
        for (int y = 0; y<TOTALY; y++) {
            for (int x = 0; x<TOTALX; x++) {
                
                BallSprite * drawS = BallSprite::create();
                
                //[drawS spawnAtX:x Y:y Width:BallSprite_WIDTH Height:BallSprite_HEIGH];
                drawS->spawnAtXY(x, y, DRAWSPRITE_WIDTH,DRAWSPRITE_HEIGH);
                m_TypeArray[x][y] = drawS->getType();
                
                m_ballSpriteArray.push_back(drawS);
//
//                CCSprite* sp = CCSprite::create("Default.png");
//                mCoreLayer->addChild(sp);
                
                addChild(drawS);
            }
        }
        m_stackArray.clear();
        
    }
    
    for (int i = 0; i< m_ballSpriteArray.size(); i++) {
        
        BallSprite * ds = (BallSprite*)m_ballSpriteArray[i];
        
        m_TypeArray[i%TOTALX][i/TOTALY] = ds->getType();
        shuzu[i%TOTALX][i/TOTALY] = m_TypeArray[i%TOTALX][i/TOTALY];
        
    }
    this->clear();
    if(!enableDispel())
    {
        initElements();
    }
//    mCoreLayer->setVisible(true);
//    this->addChild(mCoreLayer);
    loadEffectSounds();
//    setTouchEnabled(true);

//    registerWithTouchDispatcher();
    return true;
}

void DataManager::loadEffectSounds()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/1.aif");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/2.aif");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/3.aif");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/4.aif");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/5.aif");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/6.aif");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/7.aif");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/8.aif");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/9.aif");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/10.aif");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/11.aif");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/12.aif");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/13.aif");
}


BallSprite* DataManager::getCurrentSelectSprite(CCPoint pos)
{
    if (m_ballSpriteArray.size())
    {
        
        for (std::vector<BallSprite*>::iterator node = m_ballSpriteArray.begin();node!= m_ballSpriteArray.end();node++)
        {
            
            if (*node && (*node)->positionInContent(pos))
            {
                return *node;
            }
        }
    }
    
    return NULL;
}

bool DataManager::touchBegine(CCPoint local)
{
    
    if (m_toolsDisappear)
    {
        
//        toolDisappearSelected:local];
        
        return false;
    }
    
    m_movePos = local;
    m_objectHasContina = false;
    m_removeAllSameColor = false;
    
    if (m_stackArray.size() !=0)
    {
        std::vector<BallSprite*>::iterator node;
        for (node = m_stackArray.begin();node!= m_stackArray.end();node++)
        {
            (*node)->unselected();
        }
        m_stackArray.clear();
    }
    
    BallSprite * ds = getCurrentSelectSprite(local);
    
    if (ds && ds->selectedType()) {
        
        m_stackArray.push_back(ds);
//        playingSound(m_stackArray.size();
        m_currentDrawColor = ds->getBallColor();
        m_drawLine = true;
        return true;
    }
    return true;
}

void DataManager:: touchMove(CCPoint local)
{
    
    m_movePos = local;
    BallSprite * ds = getCurrentSelectSprite(local);

    if (ds && ccc4FEqual(m_currentDrawColor, ds->getBallColor()))
    {
        
        if (ds == m_stackArray.back())
        {
            return;
        }
        if (m_stackArray.size() >=2 &&
            ds == m_stackArray[m_stackArray.size()-2])
        {//退一格
            
            BallSprite * tds = m_stackArray.back();
            tds->unselected();
            if (m_objectHasContina)
            {
                m_removeAllSameColor = false;
                m_objectHasContina = false;
            }
            m_stackArray.pop_back();
            ds->selectedType();
            playingSound(m_stackArray.size());//play sounds
            return;
        }

        if (m_objectHasContina && containObject(ds,m_stackArray))
        {
            return;
        }
        
        m_objectHasContina = false;
        BallSprite * tds = NULL;
        if (m_stackArray.size())
        {
           tds = m_stackArray.back();
        }
        
        if (!tds||!ds)
        {
            return;
        }

        int absValue = abs(ds->getX() - tds->getX()) + abs(ds->getY() - tds->getY());
        if (absValue == 1 && ds->selectedType())
        {
            m_stackArray.push_back(ds);//play sounds
             playingSound(m_stackArray.size());
        }
        tds = NULL;
    }
}

void DataManager:: touchEnd()
{
    m_drawLine = false;
    
    int disappearCount = 0;
    
    if (m_stackArray.size()>=ELIMINABLE_NUM) {
        if (m_removeAllSameColor) {
            
             disappearAllSameColorDotsWithSelected();
            
        }else{
            for (int i=0; i<m_stackArray.size()-1; i++) {
                BallSprite * node = m_stackArray[i];
                if (node) {
                    if (i == m_stackArray.size()-2) {
                        node->disappear(true);
                    }
                    node->disappear(false);
                    disappearCount ++;
                }
            }
        }
    }else{
        
        std::vector<BallSprite*>::iterator it;
        for (it=m_stackArray.begin();it!=m_stackArray.end();it++) {
            (*it)->unselected();
        }
    }
    
    //zhao
    int nSum = 0;
    if (m_stackArray.size()>=ELIMINABLE_NUM)
    {
        BallSprite* pLastElement =  getLastSelected();
        
        //提示字 zhao
        CCSize s = CCDirector::sharedDirector()->getWinSize();
        int nTypeValue = pLastElement->getType();
        int nNumber = m_stackArray.size();
//        nSum = nNumber*pow(2, nTypeValue); //2^nTypeValue
        nSum = nNumber*pow(nTypeValue,2); //nTypeValue ^ 2
        
        char scoreStr[50] = {0};
        std::sprintf(scoreStr," %d X %d^2 = %d",nNumber,nTypeValue,nSum);
//        CCString* scoreStr = CCString::create("n = %d X 2^%d = %d",nNumber,nTypeValue,nSum);
        CCLabelTTF* pTotalScoreLabel = CCLabelTTF::create();
        pTotalScoreLabel->setString(scoreStr);
        pTotalScoreLabel->setPosition(ccp(s.width/2, s.height*0.7));
        pTotalScoreLabel->setColor(ccc3(242, 13, 43));
        pTotalScoreLabel->setScale(2);
        pTotalScoreLabel->setFontSize(30);
        this->getParent()->addChild(pTotalScoreLabel);
        
        CCMoveTo* pMoveto1 = CCMoveTo::create(2,ccp(10, s.height));
        auto pScaleby = ScaleBy::create(0.5, 1.2);
        //         CCFadeIn* pFadein1 = [CCFadeIn actionWithDuration:2];
//        CCCallFuncO* call = [CCCallBlockO actionWithBlock:^(id object){
//                              [pTotalScoreLabel removeFromParent];
//                              } object:self];
        CCCallFuncN* call = CCCallFuncN::create(this, callfuncN_selector(DataManager::hideScoreEffect));
        CCSpawn* pSp = CCSpawn::create(pMoveto1, NULL);
        CCSequence* pSq = CCSequence::create(pScaleby,DelayTime::create(0.5), pScaleby->reverse(),call, NULL);
        pTotalScoreLabel->runAction(pSq);
        
        //zhao
        std::vector<BallSprite*>::iterator it;
        for (it = m_ballSpriteArray.begin();it!= m_ballSpriteArray.end();it++) {
            if (*it == pLastElement)
            {
                pLastElement->changeType(m_stackArray.size());
                
            }
            
        }
    }
    
    if (m_stackArray.size()>=ELIMINABLE_NUM && this->getParent()) {
        GameCenterScene* pGameCenter = dynamic_cast<GameCenterScene*>(this->getParent());
        if (pGameCenter)
        {
            pGameCenter->addScore(nSum);
            
        }
    }
    m_stackArray.clear();
    
    this->clear();
    
    if(!enableDispel())
    {
        auto scene = GameOverLayer::scene();
        Director::getInstance()->replaceScene(scene);
        
        log("gameover");
    }
}
void DataManager:: hideScoreEffect(CCNode* pSender)
{
    if (pSender) {
        pSender->removeFromParent();
    }
}

int DataManager::disappearAllSameColorDotsWithSelected()
         {
    int count = 0;
    bool dis = true;
    for (int i=0; i<m_ballSpriteArray.size(); i++) {
        BallSprite* node = m_ballSpriteArray[i];
        if (node && ccc4FEqual(m_currentDrawColor, node->getBallColor())) {
            if (dis) {
                node->disappear(true);
                dis = false;
            }
            node->disappear(false);
            count ++;
        }
    }
    return count;
}
         
void DataManager::draw(cocos2d::Renderer *renderer,const cocos2d::Mat4& transform,uint32_t flags)
{
//         CCNode::draw();
 
 if (m_drawLine && m_canPlaying)
 {
 
 glLineWidth(20);
 
 ccColor4B c4b = ccc4BFromccc4F(m_currentDrawColor);
 ccDrawColor4B(c4b.r, c4b.g, c4b.b, c4b.a);
 
 if (m_stackArray.size()>=2)
 {
     BallSprite * ds = m_stackArray[0];
     CCPoint pos = ds->getDrawNodePosition();
         for (int c=1; c<m_stackArray.size(); c++)
        {
             ds  = m_stackArray[c];
             CCPoint pos1 = ds->getDrawNodePosition();
             ccDrawLine(pos, pos1);
             pos = pos1;
        }
  }
     BallSprite * ds = m_stackArray.back();
     CCPoint pos = ds->getDrawNodePosition();
     ccDrawLine(pos, m_movePos);
  }
 }
 
 void DataManager::disappearEnd()
{
 
   BALLVEC dropArray;
 
 for (int i = 0; i< m_ballSpriteArray.size(); i++)
 {
         BallSprite * ds = (BallSprite*)m_ballSpriteArray[i];
         calcDropDownResultArray(ds, dropArray);
 }
 
 for (int i = 0; i<dropArray.size(); i++) {
 
         BallSprite * ds = (BallSprite*)dropArray[i];
         ds->resetDropdown();
 }
 
 for (int i = 0; i< m_ballSpriteArray.size(); i++) {
 
 BallSprite * ds = (BallSprite*)m_ballSpriteArray[i];
 
 if (ds->getDisappear()) {
         ds->respawn();
 }
 }
 // update m_TypeArray
    for (int i = 0; i< m_ballSpriteArray.size(); i++) {
        
        BallSprite * ds = (BallSprite*)m_ballSpriteArray[i];
                    
        m_TypeArray[i%TOTALX][i/TOTALY] = ds->getType();
        shuzu[i%TOTALX][i/TOTALY] = m_TypeArray[i%TOTALX][i/TOTALY];

    }
    
    this->clear();
    
    if(!enableDispel())
    {
        auto scene = GameOverLayer::scene();
        Director::getInstance()->replaceScene(scene);
        
        log("gameover");
    }
 }
 
         
void DataManager::calcDropDownResultArray (BallSprite* ball,std::vector<BallSprite*> &resultArray)
        {
         
         if (!ball)
         {
            return;
         }
         
         while (true) {
         int x = ball->getX();
         int y = ball->getY();
         
         int index = y*TOTALY + x;
         int nIndex = (y-1) * TOTALY +x;
         
         if (nIndex<0) {
            break;
         }
         
         BallSprite * nDS = (BallSprite *)m_ballSpriteArray[nIndex];
         if (nDS && nDS->getDisappear())
         {
         int nX = nDS->getX();
         int nY = nDS->getY();
         
         nDS->resetPropertyAxY(x,y);
         ball->resetPropertyAxY(nX,nY);
         
         std::swap(m_ballSpriteArray[index],m_ballSpriteArray[nIndex]);
         if (!containObject(ball, resultArray) && !ball->getDisappear())
         {
            resultArray.push_back(ball);
         }
         }
             
         if(nDS && !nDS->getDisappear()){
         break;
         }
         }
         }
         
//    void DataManager::toolDisappearSelected(CGPoint) local{
//         
//         BallSprite * ds = [self getCurrentSelectSprite:local];
//         
//         int count = 0;
//         
//         if (ds) {
//         
//         [self cancelAllDrawNodeBeSelected];
//         
//         if (m_toolsDisappearType) {
//         
//         m_currentDrawColor = ds.m_color;
//         count = [self disappearAllSameColorDotsWithSelected];
//         }else{
//         [ds disappear:YES];
//         count = 1;
//         }
//         m_toolsDisappear = NO;
//         
//         
//         
//         if (self.parent) {
//         
//         DotPlayingScnen * playing = (DotPlayingScnen*)self.parent;
//         
//         if (playing) {
//         [playing playingScoreAdd:count];
//         }
//         }
//         }
//         
//         }
         
         
         bool DataManager::allDrawNodeBeSelected(bool disappearType)
         {
         
         if (m_toolsDisappear)
         {
            return false;
         }
         
         m_toolsDisappearType = disappearType;
         m_toolsDisappear = true;
         
         for (int i=0; i< m_ballSpriteArray.size(); i++) {
         
         BallSprite *ds = (BallSprite *)m_ballSpriteArray[i];
         if (ds)
         {
            ds->KeepSelected();
         }
         }
         
         return true;
         }
         
         
    void DataManager::cancelAllDrawNodeBeSelected()
         {
         
         for (int i=0; i< m_ballSpriteArray .size(); i++) {
         
         BallSprite *ds = (BallSprite *)m_ballSpriteArray[i];
         if (ds) {
            ds->unKeepSelected();
         }
         }
         }
         
         
    void DataManager::startAnimtionDisplay()
         {
         this->setVisible(true);
         if (m_ballSpriteArray.size())
         {
         BALLVEC::iterator it;
         for(it = m_ballSpriteArray.begin();it!=m_ballSpriteArray.end();it++)
         {
                if(*it)
             {
             (*it)->spawnDropdown();
             }
         }
         }
         }
 
void DataManager::startPlaying()
         {
         
         m_toolsDisappear = false;
         m_canPlaying = true;
         
         setTouchMode(kCCTouchesOneByOne);
         setTouchEnabled(true);
         }
         
bool DataManager:: onTouchBegan(Touch *touch, Event *unused_event)

         {
         
         if (!m_canPlaying) {
            return true;
         }
         
//         CCPoint touchLocation = touch->locationInView(pTouch->getLocationInView());
//         touchLocation = [[CCDirector sharedDirector] convertToGL: touchLocation];

         CCPoint touchLocation = touch->getLocation();
//         touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
         CCPoint local =  convertToNodeSpace(touchLocation);
            
         return touchBegine(local);
         }
         
void DataManager:: onTouchMoved(Touch *touch, Event *unused_event)
         {
         
         if (!m_canPlaying) {
         return ;
         }
         
         
         CCPoint touchLocation = touch->getLocation();
//         touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
         CCPoint local =  convertToNodeSpace(touchLocation);
         
         this->touchMove(local);
         }
         
    void DataManager:: onTouchEnded(Touch *touch, Event *unused_event)
         {
            touchEnd();
         }
         
    void DataManager::onTouchCancelled(Touch *touch, Event *unused_event)
         {
          touchEnd();
         }
         
    void DataManager:: moveOut()
         {
         m_canPlaying = false;
          setVisible(false);
         }
         
    void DataManager:: moveIn()
         {
            m_canPlaying = true;
            setVisible(true);
         }
         
         
#pragma mark -
         
    void DataManager::playingSound(int count)
         {
         
         if (count>13) {
         count = 13;
         }
         
         CCString * soundName = CCString::createWithFormat("Sounds/%d.aif",count);
         
         CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(soundName->getCString());
         
         }
         
         
    BallSprite* DataManager:: getLastSelected() //获取最后一个被选中的
         {
         if(m_stackArray.size()>0 )
         {
            return m_stackArray.back();
         }
         return NULL;
         }

         DataManager:: ~DataManager()
         {
             m_stackArray.clear();
             m_ballSpriteArray.pop_back();
         }

//void DataManager::registerWithTouchDispatcher()
//{
//    CCDirector::sharedDirector()->getEventDispatcher()->addTargetedDelegate(this, -128, false);
//}

