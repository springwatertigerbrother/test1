//
//  AdInstlAdapterChance.m
//  AdInstlSDK_iOS
//
//  Created by adview on 13-7-8.
//
//

#import "AdInstlAdapterChance.h"
#import "AdViewAdNetworkConfig.h"
#import "AdInstlManagerDelegate.h"
#import "adViewLog.h"
#import "AdViewAdNetworkRegistry.h"
#import "AdInstlManagerImpl.h"

@implementation AdInstlAdapterChance

@synthesize parent;

+ (AdInstlAdNetworkType)networkType {
	return AdInstlAdNetworkTypeChance;
}

+ (void)load {
	if(NSClassFromString(@"CSInterstitial") != nil) {
		[[AdViewAdNetworkRegistry sharedInstlRegistry] registerClass:self];
	}
}

- (BOOL)loadAdInstl:(UIViewController*)controller
{
    Class ChanceRAdClass = NSClassFromString(@"ChanceAd");
	Class ChanceViewClass = NSClassFromString(@"CSInterstitial");
    Class ChanceRequestClass = NSClassFromString(@"CSADRequest");
    
	if(nil == ChanceRAdClass) return NO;
    if(nil == ChanceViewClass) return NO;
    if(nil == ChanceRequestClass) return NO;
    if (nil == controller) return NO;

    //100032-4CE817-ABA2-5B48-14D009296720
    NSString *appID = self.networkConfig.pubId;
 
    [ChanceRAdClass startSession:appID];
    
    [ChanceViewClass sharedInterstitial].delegate = self;
    
    
    if (![[ChanceViewClass sharedInterstitial] showInterstitialWithScale:0.9f]) {
        AWLogInfo(@"打开弹出广告失败");
    }
    
//    CSADRequest * adRequest = [ChanceRequestClass request];
//
//    adRequest.placementID = self.networkConfig.pubId2;
//
//    [[ChanceViewClass sharedInterstitial] loadInterstitial:adRequest];
//    [ChanceViewClass sharedInterstitial].delegate = self;
    
    [self.adInstlManager adapter:self requestString:@"req"];

    return YES;
}

- (BOOL)showAdInstl:(UIViewController *)controller
{
    [self performSelector:@selector(chanceShowAdInstl:) withObject:controller afterDelay:0];
    return YES;
}

- (void)chanceShowAdInstl:(UIViewController *)controller
{
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_5_0
    if (nil == controller || ![controller isViewLoaded] || [controller isBeingDismissed]) {
        [self.adInstlManager adapter:self requestString:@"fail"];
        [self.adInstlManager adapter:self didGetEvent:InstlEventType_FailLoadAd error:nil];
        return;
    }
#else
    if (nil == controller || ![controller isViewLoaded]) {
        [self.adInstlManager adapter:self requestString:@"fail"];
        [self.adInstlManager adapter:self didGetEvent:InstlEventType_FailLoadAd error:nil];
        return;
    }
#endif
    
    Class ChanceViewClass = NSClassFromString(@"CSInterstitial");
    if (![[ChanceViewClass sharedInterstitial] showInterstitialWithScale:0.9f]) {
        AWLogInfo(@"打开弹出广告失败");
    }
    [self.adInstlManager adapter:self requestString:@"show"];
    [self.adInstlManager adapter:self didGetEvent:InstlEventType_WillPresentAd error:nil];
}

#pragma mark - PBInterstitialDelegate

// 弹出广告加载完成
- (void)csInterstitialDidLoadAd:(CSInterstitial *)csInterstitial
{
    [self.adInstlManager adapter:self didGetEvent:InstlEventType_DidLoadAd error:nil];
    [self.adInstlManager adapter:self requestString:@"suc"];
}

// 弹出广告加载错误
- (void)csInterstitial:(CSInterstitial *)csInterstitial
loadAdFailureWithError:(CSRequestError *)requestError
{
    [self.adInstlManager adapter:self didGetEvent:InstlEventType_FailLoadAd error:requestError];
    [self.adInstlManager adapter:self requestString:@"fail"];
    
    

    Class ChanceViewClass = NSClassFromString(@"CSInterstitial");
    //[ChanceViewClass sharedInterstitial].loadWhenClose = NO;
    [ChanceViewClass sharedInterstitial].delegate = nil;
}

// 弹出广告打开完成
- (void)csInterstitialDidPresentScreen:(CSInterstitial *)csInterstitial
{
    
}

// 弹出广告将要关闭
- (void)csInterstitialWillDismissScreen:(CSInterstitial *)csInterstitial
{
//    [CSInterstitial sharedInterstitial].loadWhenClose = NO;
}

// 弹出广告关闭完成
- (void)csInterstitialDidDismissScreen:(CSInterstitial *)csInterstitial
{
    Class ChanceViewClass = NSClassFromString(@"CSInterstitial");
    
    [ChanceViewClass sharedInterstitial].delegate = nil;
    [[ChanceViewClass sharedInterstitial] closeInterstitial];
    [self.adInstlManager adapter:self didGetEvent:InstlEventType_DidDismissAd error:nil];
}

- (void)stopBeingDelegate {
//    Class ChanceViewClass = NSClassFromString(@"CSInterstitial");
//    
//    [ChanceViewClass sharedInterstitial].delegate = nil;
//    [[ChanceViewClass sharedInterstitial] closeInterstitial];
    AWLogInfo(@"Chance is delloced");
}

@end