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
#include "DataHome.h"
#include "BuyLifeLayer.h"
#include "MUtils.h"
#include "DataBase64.h"
#include "AlertLayer.h"
#include "ballGamescene.h"
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
int DataManager::markMinusOne(int i,int j)
{
    
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


void DataManager::findNeighborMark(int i,int j,int color)
{
    if(i>=0&&i<6	&&j>= 0	&&j< 6){}else{return ;}
    if(shuzu[i][j]==color){
        
        shuzu[i][j]=-1;
        findNeighborMark(i-1,j,color);
        findNeighborMark(i+1,j,color);
        findNeighborMark(i,j-1,color);
        findNeighborMark(i,j+1,color);
//        findNeighborMark(i-1,j-1,color);
//        findNeighborMark(i-1,j+1,color);
//        findNeighborMark(i+1,j+1,color);
//        findNeighborMark(i+1,j-1,color);

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
    m_selectedTool = 0;
    
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
   
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(DataManager::useSuperTool), USE_SUPER_TOOL, NULL);


//    m_pDrawNode = DrawNode::create();
//    addChild(m_pDrawNode, 10);
    
    
    CCSize s = Director::getInstance()->getWinSize();
    std::string bg_cstr ;
//    if (DataHome::getInstance()->isCountDownModel)
//    {
//        bg_cstr ="Images/artwork_darkenergy-sm.jpg";
//    }
//    else
    {
        bg_cstr ="Images/gamebg.png";
    }
    
    m_pBg = Sprite::create(bg_cstr);
    m_pBg->setPosition(ccp(s.width/2,s.height/2 - 0));
//    m_pBg->setOpacity(170);
    addChild(m_pBg,-10);
    m_pBg->setZOrder(-100);
    m_pBg->setScale(3*CC_CONTENT_SCALE_FACTOR(), 3*CC_CONTENT_SCALE_FACTOR());
    CCSpawn* spawn1 = Spawn::create(ScaleTo::create(0.5, 0.1*CC_CONTENT_SCALE_FACTOR()), RotateBy::create(0.5, 360), NULL);
    CCSpawn* spawn2 = Spawn::create(ScaleTo::create(0.5, 1*CC_CONTENT_SCALE_FACTOR()), RotateBy::create(0.5,-360), NULL);
    m_pBg->runAction(Sequence::create(spawn1,spawn2,NULL) );

       
    mCoreLayer = CCLayerColor::create(ccc4(255, 255, 255, 255));//WithColor:ccc4(230, 230, 230, 255)
    if ( !mCoreLayer )
    {
        return false;
    }
    
    m_pTotalScoreLabel = CCLabelTTF::create();
//    m_pTotalScoreLabel->setString(scoreStr);
//    m_pTotalScoreLabel->setPosition(ccp(s.width/2, s.height*0.66));
    m_pTotalScoreLabel->setVisible(false);
    m_pTotalScoreLabel->setColor(ccYELLOW);
    m_pTotalScoreLabel->setScale(2);
    m_pTotalScoreLabel->setFontSize(30);
    this-> addChild(m_pTotalScoreLabel,10000);
    
    m_pGood = Sprite::create("Images/good.png");
    m_pGood->setPosition(ccp(s.width/2, s.height/2 + 50));
    m_pGood->setScale(CC_CONTENT_SCALE_FACTOR());
    m_pGood->setVisible(false);
    m_pGood->runAction(FadeOut::create(0.1));
    addChild(m_pGood,1000);
    
//    Sprite* pMoon = Sprite::create("Images/yueliang.png");
//    pMoon->setAnchorPoint(ccp(1,1));
//    pMoon->setPosition(ccp(s.width - 10,s.height - 10));
//    pMoon->setScale(CC_CONTENT_SCALE_FACTOR());
//    addChild(pMoon);
    std::string supertool;
    
    LanguageType currentLanguageType = CCApplication::sharedApplication()->getCurrentLanguage();
    switch (currentLanguageType)
    {
        case cocos2d::LanguageType::CHINESE:
        {
            supertool = "超级道具";
        }
            break;
        case cocos2d::LanguageType::ENGLISH:
        {
            supertool = "supertool";

        }
            break;
        default:
            break;
    }
    

    
    MenuItemFont::setFontSize(30);
    auto superTool =  MenuItemFont::create(supertool.c_str(), CC_CALLBACK_1(DataManager::selectedTool, this));
    superTool->setTag(supertoolTag);
    
    MenuItemImage* pItem1 = MenuItemImage::create("Images/bombbtn.png", "Images/bombbtn.png", CC_CALLBACK_1(DataManager::selectedTool, this)) ;
    pItem1 ->setTag(bomb);
    pItem1->setScale(CC_CONTENT_SCALE_FACTOR());
    MenuItemImage* pItem2 = MenuItemImage::create("Images/mushroom.png", "Images/mushroom.png", CC_CALLBACK_1(DataManager::selectedTool,this)) ;
    pItem2->setTag(wave);
    pItem2->setScale(CC_CONTENT_SCALE_FACTOR());

    Menu* pMenu = Menu::create(superTool,pItem1,pItem2, NULL);
    pMenu->alignItemsHorizontallyWithPadding(1);
//    pMenu->setAnchorPoint(ccp(0,0.5));
    //    pItem1->setFontSize(30);
    //    pItem2->setFontSize(30);
    
    pMenu->setPosition(ccp(s.width/2  + 180, s.height - 250));
    addChild(pMenu);
    
    auto particle2 = ParticleSystemQuad::create("Particles/huoyan.plist");
    particle2->setPosition(ccp(s.width/2  + 100, s.height - 250));
    //    //    _emitter = ParticleExplosion::create();
    particle2->retain();
        addChild(particle2, 1000);
    

//    auto menu = Menu::create(
//                             MenuItemFont::create("Left", CC_CALLBACK_1(LabelTTFTest::setAlignmentLeft, this)),
//                             MenuItemFont::create("Center", CC_CALLBACK_1(LabelTTFTest::setAlignmentCenter, this)),
//                             MenuItemFont::create("Right", CC_CALLBACK_1(LabelTTFTest::setAlignmentRight, this)),
//                             NULL);
//    menu->alignItemsVerticallyWithPadding(4);
//    menu->setPosition(Vec2(50, s.height / 2 - 20));
//    this->addChild(menu);
    
    initElements();

//    if (mCoreLayer)
//    {
////        mCoreLayer->setTouchEnabled(true);
////        addChild(mCoreLayer);
//        for (int y = 0; y<TOTALY; y++) {
//            for (int x = 0; x<TOTALX; x++) {
//                
//                BallSprite * drawS = BallSprite::create();
//                
//                //[drawS spawnAtX:x Y:y Width:BallSprite_WIDTH Height:BallSprite_HEIGH];
//                drawS->spawnAtXY(x, y, DRAWSPRITE_WIDTH,DRAWSPRITE_HEIGH);
//                m_TypeArray[x][y] = drawS->getType();
//                
//                m_ballSpriteArray.push_back(drawS);
////
////                CCSprite* sp = CCSprite::create("Default.png");
////                mCoreLayer->addChild(sp);
//                
//                addChild(drawS);
//            }
//        }
//        m_stackArray.clear();
//        
//    }
//    
//    for (int i = 0; i< m_ballSpriteArray.size(); i++) {
//        
//        BallSprite * ds = (BallSprite*)m_ballSpriteArray[i];
//        
//        m_TypeArray[i%TOTALX][i/TOTALY] = ds->getType();
//        shuzu[i%TOTALX][i/TOTALY] = m_TypeArray[i%TOTALX][i/TOTALY];
//        
//    }
    this->clear();
    if(!enableDispel())
    {
        initElements();
    }
//    mCoreLayer->setVisible(true);
//    this->addChild(mCoreLayer);
    loadEffectSounds();
//    setTouchEnabled(true);
//    metetors();
    
    std::string clearaway;
    std::string clearaway2;
    std::string helpStr;
    std::string backStr;

    clearaway = "click ?? top of screen to clear away words";
    clearaway2 = "click ?? ";
    helpStr = GAME_RULE_CHINISE;

    switch (currentLanguageType)
    {
        case cocos2d::LanguageType::CHINESE:
        {
            clearaway = "点击右上方的 “??” 使文字消失或出现";
            clearaway2 = "点击 ?? ";
            helpStr = GAME_RULE_CHINISE;
            backStr = "返回";

        }
            break;
        case cocos2d::LanguageType::ENGLISH:
        {
            clearaway = "click ?? right top of screen to clear away words";
            clearaway2 = "click ?? ";
            helpStr = GAME_RULE_ENGLISH;
            backStr = "back";

        }
            break;
        default:
            break;
    }
    
    
    Sprite* helpSprite = Sprite::create("Images/helppicture.png");
    helpSprite->setAnchorPoint(ccp(0.5,0));
    helpSprite->setPosition(ccp(s.width/2,100));
    helpSprite->setScale(CC_CONTENT_SCALE_FACTOR()*0.5);
    m_pLabelHelp = CCLabelTTF::create();
    //    m_pTotalScoreLabel->setString(scoreStr);
    m_pLabelHelp->setPosition(ccp(s.width/2, s.height*0.7));
    m_pLabelHelp->setVisible(true);
    m_pLabelHelp->setColor(ccYELLOW);
//    m_pLabelHelp->setScale(2);
    m_pLabelHelp->setFontSize(28);
    m_pLabelHelp->setString(helpStr);
    m_pLabelHelp->setDimensions(CCSizeMake(600,0));
    m_pLabelHelp->setAnchorPoint(ccp(0.5,1));
    

    CCLabelTTF* pLabelHelpCancel = CCLabelTTF::create();
    //    m_pTotalScoreLabel->setString(scoreStr);
    pLabelHelpCancel->setPosition(ccp(s.width/2+50, s.height-50));
    pLabelHelpCancel->setVisible(true);
    pLabelHelpCancel->setColor(ccRED);
    //    m_pLabelHelp->setScale(2);
    pLabelHelpCancel->setFontSize(28);
    pLabelHelpCancel->setString(clearaway2.c_str());
    pLabelHelpCancel->runAction(RepeatForever::create(CCSequence::create(DelayTime::create(1.5f + 0.3f), CCScaleTo::create(0.3f, 2.0f),CCScaleTo::create(0.3f, 1.0f),NULL)));
    
    
    CCLabelTTF* pLabelHelpCancel2 = CCLabelTTF::create();
    //    m_pTotalScoreLabel->setString(scoreStr);
    pLabelHelpCancel2->setPosition(ccp(s.width/2, 100));
    pLabelHelpCancel2->setVisible(true);
    pLabelHelpCancel2->setColor(ccRED);
    //    m_pLabelHelp->setScale(2);
    pLabelHelpCancel2->setFontSize(28);
    pLabelHelpCancel2->setString(clearaway.c_str());
    pLabelHelpCancel2->runAction(RepeatForever::create(CCSequence::create(DelayTime::create(1.5f + 0.3f), CCScaleTo::create(0.3f, 2.0f),CCScaleTo::create(0.3f, 1.0f),NULL)));

    
    m_helpLayer = CCLayerColor::create(ccc4(88,34,241,200));
    
    m_helpLayer->setAnchorPoint(CCPoint(0.5,1));
    
    m_helpLayer-> addChild(helpSprite);
    CCLayerColor* colorLayer = CCLayerColor::create(ccc4(88,34,241,100));
    colorLayer->setAnchorPoint(CCPoint(0,0));
    m_helpLayer-> addChild(colorLayer);

    m_helpLayer-> addChild(pLabelHelpCancel);
    m_helpLayer->addChild(pLabelHelpCancel2);
    addChild(m_helpLayer);
    
    m_helpLayer-> addChild(m_pLabelHelp,10000);
    m_helpLayer->setVisible(false);

    
    auto helpItem= MenuItemFont::create("??", CC_CALLBACK_1(DataManager::help, this));
    helpItem->setFontSize(200);
    helpItem->setScale(2);
    MenuItemFont::setFontName("American Typewriter");
    MenuItemFont::setFontSize(40);
    auto itemback = MenuItemFont::create(backStr.c_str(), CC_CALLBACK_1(DataManager::back, this));
    itemback->setScale(1);
    
    CCMenu *menu = CCMenu::create(itemback,helpItem, NULL);
    
    menu->alignItemsHorizontallyWithPadding(20);
    
    menu->setPosition(ccp(s.width/2 + 150,s.height-30));
    this-> addChild(menu);

    CCSize size = Director::getInstance()->getWinSize();
    CCPoint pos = ccp(size.width/2,size.height/2);
    
//    auto particle = ParticleSystemQuad::create("Particles/shanshuodexing.plist");
//    particle->setPosition(pos);
//    //    _emitter = ParticleExplosion::create();
//    particle->retain();
//    addChild(particle, 1000);
    
//    auto particle2 = ParticleSystemQuad::create("Particles/huoyan.plist");
//    particle2->setPosition(pos);
//    //    _emitter = ParticleExplosion::create();
//    particle2->retain();
//    addChild(particle2, 1000);
    
//    registerWithTouchDispatcher();
    return true;
}

void DataManager::loadEffectSounds()
{
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/1.aif");
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/2.aif");
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/3.aif");
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/4.aif");
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/5.aif");
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/6.aif");
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/7.aif");
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/8.aif");
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/9.aif");
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/10.aif");
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/11.aif");
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/12.aif");
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/13.aif");
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
    m_pBg->setOpacity(170);

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
        playingSound(m_stackArray.size(),ds->getType());
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
            playingSound(m_stackArray.size(),ds->getType());//play sounds
            return;
        }

        if (containObject(ds,m_stackArray))
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
        //        if ((absValue == 1 ||absValue == 2) && ds->selectedType())
        if ((absValue == 1) && ds->selectedType())
        {
            m_stackArray.push_back(ds);//play sounds
            ds->getType();
             playingSound(m_stackArray.size(),ds->getType());
        }
        tds = NULL;
    }
    
    int nSum = 0;
    BallSprite* pLastElement =  getLastSelected();
    int nTypeValue =  0;
    if(pLastElement)
    {
        nTypeValue = pLastElement->getType();

    }
    int nNumber = m_stackArray.size();
    //        nSum = nNumber*pow(2, nTypeValue); //2^nTypeValue
    nSum = nNumber*pow(nTypeValue,2); //nTypeValue ^ 2
    
    char scoreStr[50] = {0};
    std::sprintf(scoreStr," %d X %d^2 = %d",nNumber,nTypeValue,nSum);
    m_pTotalScoreLabel->setVisible(true);
    m_pTotalScoreLabel->setString(scoreStr);
    m_pTotalScoreLabel->setPosition(ccp(m_movePos.x,m_movePos.y + 70));
}
void DataManager::removeSelf(Node* pNode)
{
    Node* tempNode = (Node*)pNode;
    if (tempNode) {
        tempNode->removeFromParentAndCleanup(true);
    }
}
void DataManager:: touchEnd(CCPoint local)
{
    useTool(local);
    
     if (m_stackArray.size()>=ELIMINABLE_NUM)
     {
         
    int nSum2 = 0;
    BallSprite* pLastElement =  getLastSelected();
    int nTypeValue =  0;
    if(pLastElement)
    {
        nTypeValue = pLastElement->getType();
        
    }
    int nNumber = m_stackArray.size();
    //        nSum = nNumber*pow(2, nTypeValue); //2^nTypeValue
    nSum2 = nNumber*pow(nTypeValue,2); //nTypeValue ^ 2
    
    char scoreStr[50] = {0};
    std::sprintf(scoreStr,"+ %d",nSum2);
    m_pTotalScoreLabel->setVisible(true);
    m_pTotalScoreLabel->setString(scoreStr);
    
    CCSize size = Director::getInstance()->getWinSize();
    CCLabelTTF * labelScore = CCLabelTTF::create("0","ArialRoundedMTBold",60);
    labelScore->setString(scoreStr);
    addChild(labelScore,1000);
    labelScore->setPosition(m_pTotalScoreLabel->getPosition());
    labelScore->runAction(Sequence::create(MoveTo::create(0.9, ccp(250,size.height-50)),CCCallFuncN::create( CC_CALLBACK_1(DataManager::removeSelf, this)), NULL));
     }
    
    m_drawLine = false;
    m_pBg->setOpacity(255);

    int disappearCount = 0;
    
    m_pTotalScoreLabel->setVisible(false);

    
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
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    //zhao
    int nSum = 0;
    if (m_stackArray.size()>=ELIMINABLE_NUM)
    {
        BallSprite* pLastElement =  getLastSelected();
        
        //提示字 zhao
        int nTypeValue = pLastElement->getType();
        int nNumber = m_stackArray.size();
//        nSum = nNumber*pow(2, nTypeValue); //2^nTypeValue
        nSum = nNumber*pow(nTypeValue,2); //nTypeValue ^ 2
//
//        char scoreStr[50] = {0};
//        std::sprintf(scoreStr," %d X %d^2 = %d",nNumber,nTypeValue,nSum);
//        CCString* scoreStr = CCString::create("n = %d X 2^%d = %d",nNumber,nTypeValue,nSum);
 
        
        CCMoveTo* pMoveto1 = CCMoveTo::create(2,ccp(10, s.height));
        auto pScaleby = ScaleBy::create(0.5, 1.2);
        //         CCFadeIn* pFadein1 = [CCFadeIn actionWithDuration:2];
//        CCCallFuncO* call = [CCCallBlockO actionWithBlock:^(id object){
//                              [pTotalScoreLabel removeFromParent];
//                              } object:self];
//        CCCallFuncN* call = CCCallFuncN::create(this, callfuncN_selector(DataManager::hideScoreEffect));
//        CCSpawn* pSp = CCSpawn::create(pMoveto1, NULL);
//        CCSequence* pSq = CCSequence::create(pScaleby,DelayTime::create(0.5), pScaleby->reverse(),call, NULL);
//        m_pTotalScoreLabel->runAction(pSq);
        
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
    if (m_stackArray.size() >= 5)
    {
//        m_pGood->setVisible(true);
        CallFuncN* call1 = CallFuncN::create(CC_CALLBACK_1(DataManager::removeSelf,this));
        auto pGood = Sprite::create("Images/good.png");
        pGood->setPosition(ccp(s.width/2, s.height/2 + 50));
        pGood->setScale(CC_CONTENT_SCALE_FACTOR());
//        pGood->setVisible(false);
        pGood->runAction(Sequence::create(FadeOut::create(0.1), NULL));
        addChild(pGood,1000);
        
        auto action1 = FadeIn::create(0.50f);
        auto action1Back = action1->reverse();
        auto action2 = ScaleBy::create(0.5,1.5);
        auto action2Back = action2->reverse();
        
        pGood->runAction(Sequence::create(action1,action2,action2Back,action1Back,call1,NULL));
        
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sounds/good.mp3");
    }
    if (m_stackArray.size() >= 6)
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sounds/youbang.wav");
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sounds/xibanya.mp3");
        
    }

    m_stackArray.clear();
    
    this->clear();
    
    if(!enableDispel())
    {
        GameCenterScene* pGameCenter = dynamic_cast<GameCenterScene*>(this->getParent());
        if (pGameCenter)
        {
            pGameCenter->buyLayer->setVisible(true);
        }
        m_canPlaying = false;
        
//        auto buyLayer = BuyLifeLayer::create();
//        addChild(buyLayer);
        
//        auto scene = GameOverLayer::scene();
//        Director::getInstance()->replaceScene(scene);
//        
//        log("gameover");
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
     
//     m_pDrawNode->drawSegment(pos, m_movePos, 20,Color4F::ORANGE);
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
    
    if(!enableDispel() && ! (DataHome::getInstance()->isCountDownModel))
    {
        GameCenterScene* pGameCenter = dynamic_cast<GameCenterScene*>(this->getParent());
        if (pGameCenter)
        {
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sounds/xiaoxinjiayou.mp3");

            pGameCenter->buyLayer->setVisible(true);
        }
        m_canPlaying = false;

//        auto buyLayer = BuyLifeLayer::create();
//        addChild(buyLayer);

//        auto scene = GameOverLayer::scene();
//        Director::getInstance()->replaceScene(scene);
        
        log("gameover");
    }
    else if(!enableDispel() && (DataHome::getInstance()->isCountDownModel))
    {
        initElements();
        startAnimtionDisplay();
        startPlaying();
    }

//    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sounds/fall.mp3");
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
             CCPoint touchLocation = touch->getLocation();
             //         touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
             CCPoint local =  convertToNodeSpace(touchLocation);

            touchEnd(local);
         }
         
    void DataManager::onTouchCancelled(Touch *touch, Event *unused_event)
         {
             CCPoint touchLocation = touch->getLocation();
             //         touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
             CCPoint local =  convertToNodeSpace(touchLocation);
             
             touchEnd(local);
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
         
    void DataManager::playingSound(int count,int nType)
         {
         
         if (count>13) {
         count = 15;
         }
             std::string typeStr;
             switch (nType) {
                 case 1:
                     typeStr = "A";
                     count = count%4;
                     if (count == 0)
                     {
                         count = 4;
                     }
                     break;
                 case 2:
                     typeStr = "B";
                     count = count%4;
                     if (count == 0)
                     {
                         count = 4;
                     }
                     break;
                 case 3:
                     typeStr = "C";
                     count = count%7;
                     if (count == 0)
                     {
                         count = 7;
                     }
                     break;
                 case 4:
                 {
                     typeStr = "D";
                     count = count%11;
                     if (count == 0)
                     {
                         count = 11;
                     }
                 }
                     break;
                 case 5:
                     typeStr = "E";
                     count = count%7;
                     if (count == 0)
                     {
                         count = 8;
                     }
                     break;
                 case 6:
                     typeStr = "F";
                     break;
                 default:
                     break;
             }
         CCString * soundName = CCString::createWithFormat("Sounds/%s%d.aif",typeStr.c_str(), count);
         if(typeStr == "B")
         {
             soundName = CCString::createWithFormat("Sounds/%s.wav",typeStr.c_str());
         }
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

void DataManager::metetors()
{
    Size s = Director::getInstance()->getWinSize();
    for (int i = 0; i<10;i++)
    {
        CCSprite* pMeteor = Sprite::create("Images/meteor.png");
        float x = s.width*0.5 + random()%(int)(s.width);
        float y = s.height - random()%(int)(200);
        
        pMeteor->setPosition(ccp(x,y));
        pMeteor->setScale(CC_CONTENT_SCALE_FACTOR()*(random()%5));
        
        pMeteor->runAction(Sequence::create(MoveBy::create(0.8, ccp(-500,-500)), NULL));
        addChild(pMeteor);
    }

}
//void DataManager::registerWithTouchDispatcher()
//{
//    CCDirector::sharedDirector()->getEventDispatcher()->addTargetedDelegate(this, -128, false);
//}
void DataManager::help(void *sender)
{
    if (m_helpLayer->isVisible())
    {
        m_helpLayer->setVisible(false);
    }
    else
    {
        m_helpLayer->setVisible(true);
    }
}

// tools
void DataManager::selectedTool(void* sender)
{
    m_pTotalScoreLabel->setString("dfdfd");
    Node* pNode = ((Node*)sender);
    if (!pNode)
    {
        return;
    }
    int tag = pNode->getTag();
    int consumeDiamond = 0;
    switch (tag)
    {
        case bomb:
        {
            consumeDiamond = BOMB_COSUMED_DIAMOND;
        }
            break;
            
        case wave:
        {
            consumeDiamond = PULSE_COSUMED_DIAMOND;
        }
            break;
        case supertoolTag:
        {
            consumeDiamond = SUPER_COSUMED_DIAMOND;
        }
            break;

        default:
            break;
    }

    if (consumeDiamond == SUPER_COSUMED_DIAMOND)
    {
        auto alert = AlertLayer::create();
        alert->setPosition(ccp(0,-200));
        addChild(alert);
        return;
    }
    if (!checkDiamondWithConsume(consumeDiamond, this))
    {
        return;
    }
    m_selectedTool = tag;

    pNode->runAction(Sequence::create(ScaleTo::create(0.3, 1.6*CC_CONTENT_SCALE_FACTOR()),ScaleTo::create(0.3, 1*CC_CONTENT_SCALE_FACTOR()),NULL));
}
void DataManager::useWave(CCPoint local)
{
    BallSprite * ds = getCurrentSelectSprite(local);
    
    if (ds) {
        ds->runAction(Sequence::create(CallFuncN::create(CC_CALLBACK_1(DataManager::waveParticles,this)),DelayTime::create(1),CallFuncN::create(CC_CALLBACK_1(DataManager::waveChangeType,this)), NULL));
    }
    
    
}
void DataManager::usebomb(CCPoint local)
{
    
    BallSprite * ds = getCurrentSelectSprite(local);
    
    
    if (ds) {
        _emitter = ParticleSystemQuad::create("Particles/ExplodingRing.plist");
        
        //    _emitter = ParticleExplosion::create();
        _emitter->retain();
        addChild(_emitter, 1000);
        
        //    _emitter->setTexture( Director::getInstance()->getTextureCache()->addImage(s_stars1) );
        _emitter->setPosition(ds->m_drawNode->getPosition());
        _emitter->setAutoRemoveOnFinish(true);
        _emitter->setEndColor(calcColorWithType(ds->getType()-1));
        _emitter->setStartColor(calcColorWithType(ds->getType()-1));
        
        ds->disappear(true);
    }
    m_selectedTool = none;
    
}

void DataManager::superTool(CCPoint local)
{
    CCSize size = Director::getInstance()->getWinSize();
    CCPoint pos = ccp(size.width/2,size.height/2 -100);
    
    super_emitter = ParticleSystemQuad::create("Particles/ball5.plist");
    super_emitter->setPosition(pos);
        //    _emitter = ParticleExplosion::create();
        super_emitter->retain();
        addChild(super_emitter, 1000);
    super_emitter->setScale(CC_CONTENT_SCALE_FACTOR());
    m_selectedTool = none;
    
}

void DataManager::useTool(CCPoint local)
{
    BallSprite * ds = getCurrentSelectSprite(local);
    if (!ds)
    {
        return;
    }
    switch (m_selectedTool)
    {
        case bomb:
        {
            usebomb(local);
            consumeDiamond(BOMB_COSUMED_DIAMOND);
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sounds/bomb.mp3");
            
        }
            break;
            
        case wave:
        {
            useWave(local);
            consumeDiamond(PULSE_COSUMED_DIAMOND);
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sounds/pulse.mp3");

        }
            break;
        case supertoolTag:
        {
            superTool(local);
        }
            break;
            
        default:
            break;
    }
    m_selectedTool = none;
    NotificationCenter::getInstance()->postNotification(REFESH_USE_TOOL);

}
ccColor4F DataManager::calcColorWithType(int nType)
{
    ccColor4F retColor;

    switch (nType) {
        case 0:
            retColor = ccc4fRed;
            break;
        case 1:
            retColor = ccc4fOrange;
            break;
        case 2:
            retColor = ccc4fGreen;
            break;
        case 3:
            retColor = ccc4fBlue;
            break;
        case 4:
            retColor = ccc4fPurple;
            break;

        default:
            retColor = ccc4fPurple;
            break;
    }
    return retColor;
}

void DataManager::waveChangeType(Node* pNode)
{
    BallSprite * ds = (BallSprite*)(pNode);

    if (ds)
    {
        int type = ds->getType();
        int x = ds->getX();
        int y = ds->getY();
        
        int index1 = x-1+y*TOTALY;
        int index2 = x+1+y*TOTALY;
        int index3 = x+(y+1)*TOTALY;
        int index4 = x+(y-1)*TOTALY;
        int index5 = x-1+(y-1)*TOTALY;
        int index6 = x+1+(y+1)*TOTALY;
        int index7 = x-1+(y+1)*TOTALY;
        int index8 = x+1+(y-1)*TOTALY;
        
        std::vector<int>  indexVec;
        if (x-1>=0) {
            indexVec.push_back(index1);
        }
        if (x+1<6) {
            indexVec.push_back(index2);
        }
        if (y+1<6) {
            indexVec.push_back(index3);
        }
        if (y-1>=0) {
            indexVec.push_back(index4);
        }
        if (x-1>=0&&y-1>=0) {
            indexVec.push_back(index5);
        }
        if (x+1<6&&y+1<6) {
            indexVec.push_back(index6);

        }
        if (x-1>=0&&y+1<6) {
            indexVec.push_back(index7);

        }
        if (x+1<6&&y-1>=0) {
            indexVec.push_back(index8);
        }
        for (int i = 0; i<indexVec.size(); i++)
        {
            BallSprite* pLastElement = m_ballSpriteArray[indexVec[i]];
            if(pLastElement)
            {
                pLastElement->changeTypeWithType(type);
                m_selectedTool = none;
            }
        }

}
}
    void DataManager::waveParticles(Node* pNode)
    {
        
        BallSprite * ds = (BallSprite*)(pNode);
        
        if (ds)
        {
        _emitter = ParticleExplosion::create();
        _emitter->retain();
        addChild(_emitter, 1000);
        
        _emitter->setTexture( Director::getInstance()->getTextureCache()->addImage(s_stars1) );
        _emitter->setPosition(ds->m_drawNode->getPosition());
        _emitter->setEndColor(calcColorWithType(ds->getType()-1));
        _emitter->setStartColor(calcColorWithType(ds->getType()-1));
        _emitter->setAutoRemoveOnFinish(true);
        }
    }
void DataManager::changeAllElements(Node* pNode)
{
    int num = m_ballSpriteArray.size();
    for (int i = 0; i<num; i++)
    {
        BallSprite* pLastElement = m_ballSpriteArray[i];
        if(pLastElement)
        {
            pLastElement->changeTypeWithType(5);
        }
    }
}
void DataManager::consumeDiamond(int nDiamond)
{
    int lifeLiquid = getIntegerForKey("LIFE_LIQUID");
    
    
    if (lifeLiquid >= nDiamond)
    {
        lifeLiquid -= nDiamond;
        
        if (lifeLiquid<0)
        {
            lifeLiquid = 0;
        }
        setIntegerForKey("LIFE_LIQUID", lifeLiquid);
    }
}
void DataManager::useSuperTool(Ref* obj)
{
    consumeDiamond(SUPER_COSUMED_DIAMOND);
    NotificationCenter::getInstance()->postNotification(REFESH_USE_TOOL);

    int randValue = rand()%10;
    
    if (randValue == 1)
    {
        
        superTool(CCPointZero);
        
        runAction(Sequence::create(CCDelayTime::create(3),CallFuncN::create(CC_CALLBACK_1(DataManager::removeSuperEffect, this)),CallFuncN::create(CC_CALLBACK_1(DataManager::changeAllElements,this)), NULL ));    }
    else
    {
        std::string enoughDiamond;
        enoughDiamond = "insufficient\ndiamond\nshoping ^O^";
        
        LanguageType currentLanguageType = CCApplication::sharedApplication()->getCurrentLanguage();
        switch (currentLanguageType)
        {
            case cocos2d::LanguageType::CHINESE:
            {
                enoughDiamond = "运气不佳，没有成功获取道具，再试试手气！";
            }
                break;
            case cocos2d::LanguageType::ENGLISH:
            {
                enoughDiamond = "sorry,you can not get the tool,try again";
            }
                break;
            default:
                break;
        }
        
        //        m_labelLife->setVisible(true);
        //        m_labelLife->runAction(FadeOut::create(1));
        //
        CCSize size = Director::getInstance()->getWinSize();
        CCLabelTTF* labelLife  = CCLabelTTF::create("60","ArialRoundedMTBold",40);
        labelLife->setAnchorPoint(ccp(0.5, 0.5));
        labelLife->setColor(ccRED);
        labelLife->setPosition(ccp(size.width/2,size.height/2 + 150));
        labelLife->setString(enoughDiamond);
        labelLife->setDimensions(CCSize(500,0));
        //        labelLife->setVisible(false);
        addChild(labelLife,11);
        labelLife->runAction(Sequence::create(DelayTime::create(5), FadeOut::create(3), NULL));
        //        CallFunc* call = [](){};
        "生命药水不够，请购买";
    }
    
    
}
void DataManager::removeSuperEffect(Node* pNode)
{
    super_emitter->removeFromParentAndCleanup(true);
}
void DataManager::back(void* sender)
{
    auto scene = BallGameScene::scene();
    Director::getInstance()->replaceScene(scene);
}