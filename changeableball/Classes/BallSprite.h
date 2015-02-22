//
//  BallSprite.h
//  changeableball
//
//  Created by huge on 3/9/14.
//
//

#ifndef __changeableball__BallSprite__
#define __changeableball__BallSprite__

#include <iostream>
#include "cocos2d.h"
#include "config.h"
using namespace cocos2d;

class BallSprite:public CCSprite
{
    int m_w;
    int m_h;
    
    bool m_hasSelected;//可否被选择
    
    CCDrawNode * m_drawNode;// 画当前颜色的圆点
    
    CCDrawNode * m_selectNode;// 用于 被选中时播放动画
    CCLabelTTF * m_ValueLabel;// 球的值
    int m_dropCount;
public:
    BallSprite();
    virtual ~BallSprite();
    CREATE_FUNC(BallSprite);

public:
    CC_SYNTHESIZE(int,m_x,X);
    CC_SYNTHESIZE(int,m_y,Y);
    CC_SYNTHESIZE(ccColor4F,m_BallColor,BallColor);
    CC_SYNTHESIZE(bool,m_disappear,Disappear);
    CC_SYNTHESIZE(int,m_type,Type);
public:
    
    CCPoint  calcPos(int x ,int y);
    void calcColor();

    void spawnAtXY(int x,int y, float w,float h);
    void respawn();// 重新生成
    void spawnDropdown();//生成后掉落下来
    void spawnDropDownCallBack();
    void respawnDropdown();
    void respawnDropdownCallBack();

    void resetPropertyAxY(int x,int y);// 重置属性 x和y坐标值
    
    void resetDropdown();// 重置后掉落函数
    void resetDropdownCallBack();
    bool positionInContent(CCPoint pos);// 判断是移动的点是否在 检查范围内
    
    bool selectedType();// 被选中调用该方法
    void selectedTypeCallback();
    void disappear(bool callf);// 消失
    void disappearCallback();//

    void unselected();// 取消选中状态
    
    CCPoint getDrawNodePosition();//得到当前 绘制节点的位置
    
    void KeepSelected();//保持被选中状态
    
    void unKeepSelected();// 取消保持被选中状态
    void unKeepSelectedCallback();

    void changeType(int nNum);//更换类型
    
};



#endif /* defined(__changeableball__BallSprite__) */
