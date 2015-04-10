/*
 adview.
 */

#import "AdViewAdNetworkConfig.h"
#import "AdInstlManagerDelegate.h"
#import "adViewLog.h"
#import "AdViewAdNetworkRegistry.h"
#import "AdInstlAdapterInMobi.h"
#import "AdInstlManagerImpl.h"

static BOOL isLoad;
static IMInterstitial *imadInstl;

@interface AdInstlAdapterInMobi ()
@end

@implementation AdInstlAdapterInMobi

+ (AdInstlAdNetworkType)networkType {
	return AdInstlAdNetworkTypeInMobi;
}

+ (void)load {
	if(NSClassFromString(@"IMInterstitial") != nil) {
		[[AdViewAdNetworkRegistry sharedInstlRegistry] registerClass:self];
	}
}

- (BOOL)loadAdInstl:(UIViewController*)controller
{
	Class IMAdInterstitialClass = NSClassFromString(@"IMInterstitial");
    Class InMobiClass = NSClassFromString(@"InMobi");
	if(nil == IMAdInterstitialClass) return NO;
    if (nil == InMobiClass) return NO;
    
    NSString *appID = self.networkConfig.pubId;
    
    if (imadInstl == nil)
    {
        [InMobi initialize:appID];
        imadInstl = [[IMInterstitial alloc] initWithAppId:appID];
        isLoad = YES;
    }
    
    imadInstl.delegate = self;
  
    [InMobi setLogLevel:IMLogLevelNone];
    
    self.adInstlController = (UIViewController*)imadInstl;

    [self.adInstlManager adapter:self requestString:@"req"];
    
    [imadInstl loadInterstitial];
    	
	return YES;
}

- (BOOL)showAdInstl:(UIViewController*)controller
{
    if (nil == self.adInstlController) {
        AWLogInfo(@"No inmobi instl exist!");
        return NO;
    }
    IMInterstitial *imadInstl = (IMInterstitial*)self.adInstlController;

    if (kIMInterstitialStateReady != imadInstl.state) {
        AWLogInfo(@"Inmobi instl not ready!");
        return NO;
    }
    
#if (__IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_5_0)
    if (nil == controller || ![controller isViewLoaded] || [controller isBeingDismissed]) {
        [self.adInstlManager adapter:self requestString:@"fail"];
        [self.adInstlManager adapter:self didGetEvent:InstlEventType_FailLoadAd error:nil];
        return NO;
    }
#else
    if (nil == controller || ![controller isViewLoaded]) {
        [self.adInstlManager adapter:self requestString:@"fail"];
        [self.adInstlManager adapter:self didGetEvent:InstlEventType_FailLoadAd error:nil];
        return NO;
    }
#endif
    
     [imadInstl presentInterstitialAnimated:YES];
    
    return YES;
}

#pragma mark delegate

- (BOOL)judgeInstlController:(IMInterstitial*)instl
{
    if ((IMInterstitial*)self.adInstlController != instl) {//stale instl.
        AWLogInfo(@"stale instl controller!");
        return NO;
    }
    return YES;
}

//当插屏广告被成功加载后，回调该方法
- (void)interstitialDidReceiveAd:(IMInterstitial *)ad
{
    if (![self judgeInstlController:ad]) return;
   
    [self.adInstlManager adapter:self requestString:@"suc"];
    [adInstlManager adapter:self didGetEvent:InstlEventType_DidLoadAd error:nil];
    
}

//当插屏广告加载失败后，回调该方法
- (void)interstitial:(IMInterstitial *)ad didFailToReceiveAdWithError:(IMError *)error
{
    if (![self judgeInstlController:ad]) return;
    [self.adInstlManager adapter:self requestString:@"fail"];
    [adInstlManager adapter:self didGetEvent:InstlEventType_FailLoadAd error:error];
    AWLogInfo(@"error is %@",error);
}

// 当插屏广告要被呈现出来前，回调该方法
- (void)interstitialWillPresentScreen:(IMInterstitial *)ad
{
    if (![self judgeInstlController:ad]) return;
    [self.adInstlManager adapter:self requestString:@"show"];
    [adInstlManager adapter:self didGetEvent:InstlEventType_WillPresentAd error:nil];
}

// 当插屏广告被关闭后，回调该方法
- (void)interstitialWillDismissScreen:(IMInterstitial *)ad
{
    if (![self judgeInstlController:ad]) return;
    
    [adInstlManager adapter:self didGetEvent:InstlEventType_DidDismissAd error:nil];
}

- (void)stopBeingDelegate {
    AWLogInfo(@"--Inmobi--stopBeingDelegate");    

    IMInterstitial *imadInstl = (IMInterstitial *)self.adInstlController;
    imadInstl.delegate = nil;
    self.adInstlController = nil;
}

@end
