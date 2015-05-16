/*
 *  AdInstlManagerDelegate.h
 *  AdInstlSDK_iOS
 *
 *  Created by zhiwen on 12-12-27.
 *  Copyright 2012 www.adview.cn. All rights reserved.
 *
 */

@class AdInstlManager;

typedef enum
{
    InstlEventType_None = 0,
    InstlEventType_StartLoadAd,
    InstlEventType_DidLoadAd,
    InstlEventType_FailLoadAd,
    InstlEventType_WillPresentAd,
    InstlEventType_DidDismissAd,
    InstlEventType_WillPresentModal,    //like inline browser view.
    InstlEventType_DidDismissModal,
    
    InstlEventType_DidShowAd,
    InstlEventType_DidClickAd,
}InstlEventType;

typedef enum {
    AdInstlLoadType_Loading = 0,
    AdInstlLoadType_DidLoadAd,
    AdInstlLoadType_FailLoadAd,
    AdInstlLoadType_PresentAd,
    AdInstlLoadType_NotInit,
} AdInstlLoadType;

NSString *AdInstlEventType_Name(InstlEventType type);

@protocol AdInstlManagerDelegate<NSObject>

@optional
/**
 * 信息回调
 */
- (void)adInstlManager:(AdInstlManager*)manager didGetEvent:(InstlEventType)eType error:(NSError*)error;
/**
 * 取得配置的回调通知
 */
- (void)adInstlDidReceiveConfig:(AdInstlManager*)manager;

/**
 * 配置全部无效或为空的通知
 */
- (void)adInstlReceivedNotificationAdsAreOff:(AdInstlManager*)manager;

/**
 * 是否打开测试模式，缺省为NO
 */
- (BOOL)adInstlTestMode;

/**
 * 是否打开日志模式，缺省为NO
 */
- (BOOL)adInstlLogMode;

/**
 * 是否获取地理位置，缺省为NO
 */
- (BOOL)adInstlOpenGps;

/**
 * 是否使用html5广告，缺省为NO
 */
- (BOOL)adInstlUsingHtml5;

@end