//
//  AdviewAd.h
//  changeableball
//
//  Created by huge on 12/4/15.
//
//

#include <stdio.h>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#include "cocos2d.h" 

#endif


#ifndef __changeableball__AdviewAd__
#define __changeableball__AdviewAd__


using namespace cocos2d;

class AdviewAd {
public: AdviewAd();
virtual ~AdviewAd(); static void showBanner(); static void hideBanner(); static void requestInstl(); static void showInstl(); static void close();
};

#endif /* defined(__changeableball__AdviewAd__) */
