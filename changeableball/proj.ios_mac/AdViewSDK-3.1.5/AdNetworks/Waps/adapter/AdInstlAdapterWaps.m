//
//  AdInstlAdapterWaps.m
//  AdInstlSDK_iOS
//
//  Created by Ma ming on 13-3-18.
//
//

#import "AdInstlAdapterWaps.h"
#import "AdViewAdNetworkConfig.h"
#import "AdInstlManagerDelegate.h"
#import "adViewLog.h"
#import "AdViewAdNetworkRegistry.h"
#import "AdInstlManagerImpl.h"
#import <WPLib/AppConnect.h>

@implementation AdInstlAdapterWaps

@synthesize rootController;

+ (AdInstlAdNetworkType)networkType {
    return AdInstlAdNetworkTypeWaps;
}

+ (void)load {
	if(NSClassFromString(@"AppConnect") != nil) {
		[[AdViewAdNetworkRegistry sharedInstlRegistry] registerClass:self];
	}
}

- (BOOL)loadAdInstl:(UIViewController *)controller {
    Class WapsInstlClass = NSClassFromString(@"AppConnect");
    Class WapsLogClass = NSClassFromString(@"WPLog");
	if(nil == WapsInstlClass) return NO;
    if(nil == WapsLogClass) return NO;
    if (controller == nil) return NO;
    
    self.rootController = controller;
    
    NSString *appID = self.networkConfig.pubId;
    
    [WapsLogClass setLogThreshold:LOG_DEBUG];
    
    [WapsInstlClass getConnect:appID pid:[self.adInstlManager marketChannel]];
    [self.adInstlManager adapter:self requestString:@"req"];
    //初始化插屏广告
    [WapsInstlClass initPop];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onConnectSuccess:) name:WP_CONNECT_SUCCESS object:nil];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onConnectFailed:) name:WP_CONNECT_FAILED object:nil];
    
    //获取插屏关闭的回调方法
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onPopAdClosed:)
                                                 name:WP_POPAD_CLOSED
                                               object:nil];
    
    //获取插屏显示成功的回调方法
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onPopAdShow:)
                                                 name:WP_POPAD_SHOW_SUCESS
                                               object:nil];
    
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
        [self.adInstlManager adapter:self requestString:@"fail"];
        [self.adInstlManager adapter:self didGetEvent:InstlEventType_FailLoadAd error:nil];
        return NO;
    }
#endif
    
    [NSClassFromString(@"AppConnect") showPop:self.rootController];
    
    return YES;
}

#pragma mark Notification

-(void)onConnectSuccess:(NSNotification*)notifyObj
{
    AWLogInfo(@"Wap's Instl did load success");
    [self.adInstlManager adapter:self requestString:@"suc"];
    [adInstlManager adapter:self didGetEvent:InstlEventType_DidLoadAd error:nil];
}

-(void)onConnectFailed:(NSNotification*)notifyObj
{
	AWLogInfo(@"Wap's Instl did load failed");
 
    NSError *errorMessage = [NSError errorWithDomain:notifyObj.name code:0 userInfo:nil];
    [self.adInstlManager adapter:self requestString:@"fail"];
    [adInstlManager adapter:self didGetEvent:InstlEventType_FailLoadAd error:errorMessage];
}

- (void)onPopAdClosed:(NSNotification*)notifyObj {
    AWLogInfo(@"Wap's Instl did closed");
    [adInstlManager adapter:self didGetEvent:InstlEventType_DidDismissAd error:nil];
}

- (void)onPopAdShow:(NSNotification*)notifyObj {
    AWLogInfo(@"Wap's Instl did show");
    [self.adInstlManager adapter:self requestString:@"show"];
    [adInstlManager adapter:self didGetEvent:InstlEventType_WillPresentAd error:nil];
    [adInstlManager adapter:self didGetEvent:InstlEventType_DidShowAd error:nil];
}

- (void)stopBeingDelegate {
    AWLogInfo(@"--Waps--stopBeingDelegate");
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    self.rootController = nil;
}

@end
