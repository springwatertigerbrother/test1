

#ifndef __mlib__MUtils__
#define __mlib__MUtils__

#include <iostream>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "config.h"

using namespace cocos2d::extension;
using namespace cocos2d;

float get_content_scale_factor();
cocos2d::Size get_design_resolution_size();
float get_resolution_scale();
void initialize_resolution();
ControlButton* standardButtonWithTitle(const char * title);
bool ControlButtoninit(Node* obj,std::vector<std::string> vec);

int calculate_score(int nScore,int n);
//
//void shareCallback(int platform, int stCode, std::string& errorMsg)
//{
//    if ( stCode == 100 )
//    {
//        CCLog("#### HelloWorld 开始分享");
//    }
//    else if ( stCode == 200 )
//    {
//        CCLog("#### HelloWorld 分享成功");
//    }
//    else
//    {
//        CCLog("#### HelloWorld 分享出错");
//    }
//    
//    CCLog("platform num is : %d.", platform);
//}

#endif /* defined(__mlib__MUtils__) */
