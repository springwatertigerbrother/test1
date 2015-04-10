//
//  AdInstlAdapterMobiSage.m
//  AdInstlSDK_iOS
//
//  Created by Ma ming on 13-5-31.
//
//

#import "AdInstlAdapterMobiSage.h"

#import "AdViewAdNetworkConfig.h"
#import "AdInstlManagerDelegate.h"
#import "adViewLog.h"
#import "AdViewAdNetworkRegistry.h"
#import "AdInstlManagerImpl.h"
#define Entire_screen_is_On  1
#define Entire_screen_is_Off 0

@interface AdInstlAdapterMobiSage ()
@end

@implementation AdInstlAdapterMobiSage

@synthesize mobiSageView;
@synthesize parent;
@synthesize isStatusHidden;

+ (AdInstlAdNetworkType)networkType {
    return AdInstlAdNetworkTypeMobiSage;
}

+ (void)load {
    if(NSClassFromString(@"MobiSageManager") != nil) {
		[[AdViewAdNetworkRegistry sharedInstlRegistry] registerClass:self];
	}
}

- (BOOL)loadAdInstl:(UIViewController *)controller {
//    Class MobiSagePosterClass = NSClassFromString(@"MobiSageAdPoster");
    Class MobiSageManagerClass = NSClassFromString(@"MobiSageManager");
    
//    if (MobiSagePosterClass == nil) return NO;
    if (MobiSageManagerClass ==nil) return NO;
    if (controller == nil) return NO;
    self.parent = controller;
    isStatusHidden = NO;
    
    NSString * appId = self.networkConfig.pubId2;
    NSString * slotToken = self.networkConfig.pubId3;
    
    //[[MobiSageManagerClass getInstance] setPublisherID:appId deployChannel:[self.adInstlManager marketChannel]];
    [[MobiSageManager getInstance] setPublisherID:appId deployChannel:[self.adInstlManager marketChannel] auditFlag:@"IOS_AppStore_v6.4.2"];
    
    Class MobiSageFloatWindowClass = NSClassFromString(@"MobiSageFloatWindow");
    //Float_size_3为全屏；Float_size_0为半屏
        self.mobiSageView = [[MobiSageFloatWindowClass alloc] initWithAdSize:Float_size_0
                                                              delegate:self
                                                             slotToken:slotToken];
    
    [self.adInstlManager adapter:self requestString:@"req"];
   
    if (self.mobiSageView == nil) {
        [self.adInstlManager adapter:self requestString:@"fail"];
        [self.adInstlManager adapter:self didGetEvent:InstlEventType_FailLoadAd error:nil];
        return NO;
    }
      
    return YES;
}

- (BOOL)showAdInstl:(UIViewController *)controller {
   
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_5_0
    if (nil == controller || ![controller isViewLoaded] || [controller isBeingDismissed]) {
        [self.adInstlManager adapter:self requestString:@"fail"];
        [self.adInstlManager adapter:self didGetEvent:InstlEventType_FailLoadAd error:nil];
        return NO;
    }
#else
    if (nil == controller || ![controller isViewLoaded]) {
        [self.adInstlManager adapter:self didGetEvent:InstlEventType_FailLoadAd error:nil];
        return NO;
    }
#endif
    if (![UIApplication sharedApplication].statusBarHidden) {
        //若请求广告尺寸为全屏则需要隐藏statusBar
        [UIApplication sharedApplication].statusBarHidden = YES;
        isStatusHidden = YES;
    }
    
    [self.adInstlManager adapter:self requestString:@"show"];

    [self.adInstlManager adapter:self didGetEvent:InstlEventType_WillPresentAd error:nil];
    [self.mobiSageView showAdvView];

    return YES;
}

#pragma mark -
#pragma mark delegate

- (void)mobiSageFloatSuccessToRequest:(MobiSageFloatWindow*)adFloat
{
    [self.adInstlManager adapter:self requestString:@"suc"];
     [self.adInstlManager adapter:self didGetEvent:InstlEventType_DidLoadAd error:nil];
}

- (void)mobiSageFloatClick:(MobiSageFloatWindow*)adFloat
{
    [self.adInstlManager adapter:self requestString:@"click"];
    [self.adInstlManager adapter:self didGetEvent:InstlEventType_DidClickAd error:nil];
}

- (void)mobiSageFloatClose:(MobiSageFloatWindow*)adFloat
{
    //若请求广告之前有statusBar并且请求的广告为全屏广告，则需要在此处显示statusBar
    if (isStatusHidden) {
        [UIApplication sharedApplication].statusBarHidden = NO;
    }
     [self.adInstlManager adapter:self didGetEvent:InstlEventType_DidDismissAd error:nil];
}

- (void)mobiSageFloatFaildToRequest:(MobiSageFloatWindow*)adFloat
{
    [self.adInstlManager adapter:self requestString:@"fail"];
    [self.adInstlManager adapter:self didGetEvent:InstlEventType_FailLoadAd error:nil];
}

- (UIViewController *)viewControllerToPresent {
    return self.parent;
}

- (void)stopBeingDelegate {
    AWLogInfo(@"MobiSage delloced");
    self.mobiSageView.delegate = nil;
    self.mobiSageView = nil;
    self.parent = nil;
}

@end
