//
//  AdInstlAdapterDianru.m
//  AdInstlSDK_iOS
//
//  Created by adview on 14-2-25.
//
//

#import "AdInstlAdapterDianru.h"

#import "adViewConfig.h"
#import "AdViewAdNetworkConfig.h"
#import "AdInstlManagerDelegate.h"
#import "adViewLog.h"
#import "adViewAdNetworkRegistry.h"
#import "adViewExtraManager.h"
#import "AdInstlManagerImpl.h"

@implementation AdInstlAdapterDianru

@synthesize adView;
@synthesize rootController;

+ (AdInstlAdNetworkType)networkType
{
    return AdInstlAdNetworkTypeDianRu;
}

+ (void)load
{
	if(NSClassFromString(@"IndexSwitch") != nil)
    {
		[[AdViewAdNetworkRegistry sharedInstlRegistry] registerClass:self];
	}
}

- (BOOL)loadAdInstl:(UIViewController*)controller
{
    Class dianRuInstlClass = NSClassFromString(@"IndexSwitch");
	if(nil == dianRuInstlClass) return NO;
    if (controller == nil) return NO;
    self.rootController = controller;
    
    [TalkingDataSDK init];
    
    BOOL bUseGPS = [self isOpenGps];
    
    DR_INIT(self.networkConfig.pubId, bUseGPS, nil);
    
    DR_CREATE(DR_INSERSCREEN, self);
    
    [self.adInstlManager adapter:self requestString:@"req"];

    return YES;
}

- (BOOL)showAdInstl:(UIViewController*)controller
{
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_5_0
    BOOL isNotPresent = (![controller isViewLoaded] || [controller isBeingDismissed] || [controller isMovingFromParentViewController]);
#else
    BOOL isNotPresent = ![controller isViewLoaded];
#endif
    if (nil == controller || isNotPresent) {
        [self.adInstlManager adapter:self requestString:@"fail"];
        [self.adInstlManager adapter:self didGetEvent:InstlEventType_FailLoadAd error:nil];
        return NO;
    }

    
    if (nil != self.adView)
    {
        [self.rootController.view addSubview:self.adView];
        [self.adInstlManager adapter:self didGetEvent: InstlEventType_WillPresentAd error:nil];
        [self.adInstlManager adapter:self requestString:@"show"];
    } else {
        [self.adInstlManager adapter:self requestString:@"fail"];
        [self.adInstlManager adapter:self didGetEvent:InstlEventType_FailLoadAd error:nil];
        return NO;
    }
    
    return YES;
    
}

- (void)notifyDidLoadAd:(UIView*)view
{
    [self.adInstlManager adapter:self didGetEvent: InstlEventType_DidLoadAd error:nil];
}


#pragma mark DianRuSDK Delegate
/*
 请求广告条数
 如果广告条数大于0，那么code=0，代表成功
 反之code = -1
 */
- (void)dianruDidDataReceivedView:(UIView *)view dianruCode:(int)code
{
    if (code == 0)
    {
        [self.adInstlManager adapter:self requestString:@"suc"];
        [self performSelector:@selector(notifyDidLoadAd:) withObject:view afterDelay:0.3f];
        //[self.adInstlManager adapter:self didGetEvent:InstlEventType_DidLoadAd error:nil];    //只需要保留一行，afterDelay可以确保时机正确
    } else {//失败
        self.adView = nil;
        [self.adInstlManager adapter:self requestString:@"fail"];
        [self.adInstlManager adapter:self didGetEvent:InstlEventType_FailLoadAd error:nil];
    }
}

/*
 广告弹出时回调
 */
- (void)dianruDidViewOpenView:(UIView *)view
{
    if (nil != view)
    {
        self.adView = view;
    }
}

/*
 点击广告关闭按钮的回调，不代表广告从内存中释放
 */
- (void)dianruDidMainCloseView:(UIView *)view
{
    [self.adInstlManager adapter:self didGetEvent:InstlEventType_DidDismissAd error:nil];
}

/*
 广告释放时回调，从内从中释放
 */
- (void)dianruDidViewCloseView:(UIView *)view
{
    [self.adInstlManager adapter:self didGetEvent:InstlEventType_DidDismissAd error:nil];
}

/*
 曝光回调
 */
- (void)dianruDidReportedView:(UIView *)view dianruData:(id)data
{
    
}

/*
 点击广告回调
 */
- (void)dianruDidClickedView:(UIView *)view dianruData:(id)data
{
    [self.adInstlManager adapter:self didGetEvent:InstlEventType_DidClickAd error:nil];
}

/*
 点击跳转回调
 */
- (void)dianruDidJumpedView:(UIView *)view dianruData:(id)data
{
    
}

- (void)stopBeingDelegate
{
//    AdInstlLogInfo(@"DianRu stopBeingDelegate");
    self.adView = nil;
    self.adInstlManager = nil;
    self.rootController = nil;
}


@end
