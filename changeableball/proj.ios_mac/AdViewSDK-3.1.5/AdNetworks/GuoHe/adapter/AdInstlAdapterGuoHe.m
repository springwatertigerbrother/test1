//
//  AdInstlAdapterGuoHe.m
//  AdInstlSDK_iOS
//
//  Created by Ma ming on 13-5-16.
//
//

#import "AdInstlAdapterGuoHe.h"
#import "AdViewAdNetworkConfig.h"
#import "AdInstlManagerDelegate.h"
#import "adViewLog.h"
#import "AdViewAdNetworkRegistry.h"
#import "AdInstlManagerImpl.h"

#import "MIXView.h"
@class MixViewShare;

@implementation AdInstlAdapterGuoHe

//@synthesize parent;
@synthesize mixView;

+ (AdInstlAdNetworkType)networkType {
    return AdInstlAdNetworkTypeGuoHe;
}

+ (void)load {
    if(NSClassFromString(@"MIXView") != nil) {
		[[AdViewAdNetworkRegistry sharedInstlRegistry] registerClass:self];
	}
}

- (BOOL)loadAdInstl:(UIViewController *)controller {
    Class MIXViewClass = NSClassFromString(@"MIXView");
    if (MIXViewClass == nil) return NO;
    //self.parent = controller;
    NSString * appID = self.networkConfig.pubId;
    
    //mixView = [MixViewShare shareInit:appID andTest:[self isTestMode]];
   // mixView = [GuoHeClass initWithID:appID setTestMode:[self isTestMode]];
    self.mixView = [MIXViewClass initWithID:appID];
    if (self.mixView) {
        [MIXViewClass preloadAdWithDelegate:self withPlace:@"default"];
    }
    [self performSelector:@selector(didLoadAd) withObject:nil afterDelay:0.2];
    
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
    if ([MIXView canServeAd:@"default"]) {
        [self.adInstlManager adapter:self requestString:@"show"];
        //    [MIXView showAdWithDelegate:self viewController:controller];
        [MIXView showAdWithDelegate:self];
        
    }

    return YES;
}

#pragma mark - 
#pragma mark Delegate

- (void)didLoadAd
{
    [self.adInstlManager adapter:self requestString:@"req"];
    [self.adInstlManager adapter:self didGetEvent:InstlEventType_DidLoadAd error:nil];
}

//加载推广橱窗失败时调用
- (void)mixViewDidFailToShowAd:(MIXView *)view withPlace:(NSString *)place {
     [self.adInstlManager adapter:self requestString:@"fail"];
    [self.adInstlManager adapter:self didGetEvent:InstlEventType_FailLoadAd error:nil];
}

//加载推广橱窗成功时调用
- (void)mixViewDidShowAd:(MIXView *)view withPlace:(NSString *)place {
    [self.adInstlManager adapter:self requestString:@"suc"];
    [self.adInstlManager adapter:self didGetEvent:InstlEventType_WillPresentAd error:nil];
}

//推广橱窗点击出现内容窗口时调用
- (void)mixViewDidClickedAd:(MIXView *)view withPlace:(NSString *)place {
    [self.adInstlManager adapter:self requestString:@"click"];
    [self.adInstlManager adapter:self didGetEvent:InstlEventType_DidClickAd error:nil];
    [self.adInstlManager adapter:self didGetEvent:InstlEventType_DidDismissAd error:nil];

}

//推广橱窗的关闭按钮被点击时调用
- (void)mixViewDidClosed:(MIXView *)view withPlace:(NSString *)place {
    [self.adInstlManager adapter:self didGetEvent:InstlEventType_DidDismissAd error:nil];
    if (self.mixView) {
        self.mixView = nil;
    }
}

//没有推广橱窗返回时调用
- (void)mixViewNoAdWillPresent:(MIXView *)view withPlace:(NSString *)place {
    NSError *errorMessage = [NSError errorWithDomain:place code:0 userInfo:nil];
    [self.adInstlManager adapter:self requestString:@"fail"];
    [self.adInstlManager adapter:self didGetEvent:InstlEventType_FailLoadAd error:errorMessage];
}

- (void)stopBeingDelegate {
    AWLogInfo(@"GuoHe dealloced");
    self.mixView = nil;
    //self.parent = nil;
}

@end
