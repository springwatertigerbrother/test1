//
//  AdviewAd.cpp
//  changeableball
//
//  Created by huge on 12/4/15.
//
//

#include "AdviewAd.h"


AdviewAd::AdviewAd() {
    // TODO Auto-generated constructor stub
}
AdviewAd::~AdviewAd() {
    // TODO Auto-generated destructor stub
}
void AdviewAd::showBanner() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo showBanner;
    //第二个参数 "org/cocos2dx/cpp/AdViewCocos2dx"表示引入的类名
    //第三个参数 "showBannerStatic"表示该类下需要执行的方法
    //第四个参数 "()V" 表示"showBannerStatic"不需要传入参数并且返回值类型void类型
    bool isHave = JniHelper::getStaticMethodInfo(showBanner,"org/cocos2dx/cpp/AdViewCocos2dx" ,"showBannerStatic","()V");
    if (!isHave) { CCLog("jni:showBannerStatic false");
    } else {
        showBanner.env->CallStaticVoidMethod(showBanner.classID, showBanner.methodID);
    }
#endif
}
void AdviewAd::hideBanner() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo hideBanner;
    bool isHave = JniHelper::getStaticMethodInfo(hideBanner,"org/cocos2dx/cpp/AdViewCocos2dx" ,"hideBannerStatic","()V");
    if (!isHave) { CCLog("jni:showBannerStatic false");
    } else {
        hideBanner.env->CallStaticVoidMethod(hideBanner.classID, hideBanner.methodID);
    }
#endif
}
void AdviewAd::close() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo close;
    bool isHave = JniHelper::getStaticMethodInfo(close,"org/cocos2dx/cpp/AdViewCocos2dx","clo se","()V");
    if (!isHave) { CCLog("jni:hideBannerStatic false");
    } else {
        CCLog("jni:hideBannerStatic true");
        close.env->CallStaticVoidMethod(close.classID, close.methodID); }
#endif
}
void AdviewAd::requestInstl() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo close;
    bool isHave = JniHelper::getStaticMethodInfo(close,"org/cocos2dx/cpp/AdViewCocos2dx","req uestInstlStatic","()V");
    if (!isHave) { CCLog("jni:requestInstlStatic false");
    } else {
        CCLog("jni:requestInstlStatic true");
        close.env->CallStaticVoidMethod(close.classID, close.methodID); }
#endif
}
void AdviewAd::showInstl() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo close;
    bool isHave = JniHelper::getStaticMethodInfo(close,"org/cocos2dx/cpp/AdViewCocos2dx","sho wInstlStatic","()V");
    if (!isHave) { CCLog("jni:showInstlStatic false");
    } else {
        CCLog("jni:showInstlStatic true");
        close.env->CallStaticVoidMethod(close.classID, close.methodID); }
#endif
}
