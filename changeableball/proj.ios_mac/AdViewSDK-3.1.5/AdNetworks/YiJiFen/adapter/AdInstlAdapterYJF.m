//
//  AdInstlAdapterYJF.m
//  AdInstlSDK_iOS
//
//  Created by Ma ming on 13-3-13.
//
//

#import "AdInstlAdapterYJF.h"
#import "AdViewAdNetworkConfig.h"
#import "AdInstlManagerDelegate.h"
#import "adViewLog.h"
#import "AdViewAdNetworkRegistry.h"
#import "AdInstlManagerImpl.h"

#import <Eadver/HMInitServer.h>
#import <Eadver/HMUserMessage.h>

@interface AdInstlYJFAutorotate : UIViewController
{
    BOOL isAutoRotate;
    BOOL isFirst;
}

@property (assign, nonatomic) BOOL isAutoRotate;
@property (assign, nonatomic) BOOL isFirst;

@end

@implementation AdInstlYJFAutorotate

@synthesize isAutoRotate;
@synthesize isFirst;

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation {
    if (isFirst) {
        isFirst = NO;
        return YES;
    }
    return NO;//(toInterfaceOrientation == UIInterfaceOrientationLandscapeLeft || toInterfaceOrientation == UIInterfaceOrientationLandscapeRight);
}

- (BOOL)shouldAutorotate {
    return self.isAutoRotate;
}

@end

@interface AdInstlAdapterYJF ()
@end

@implementation AdInstlAdapterYJF

+ (AdInstlAdNetworkType)networkType{
    return AdInstlAdNetworkTypeYiJiFen;
}

+ (void)load {
	if(NSClassFromString(@"HMInterstitial") != nil) {
		[[AdViewAdNetworkRegistry sharedInstlRegistry] registerClass:self];
	}
}

- (void)initFailed{

}

- (void)initSuccess{

}

-(void)willAnimateRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration {
    //横竖屏切换的时候，插屏最好是关闭掉，以免显示效果不佳
    //或者将屏幕固定，不旋转
    [[HMInterstitial shareInstance] cancle_Interstitial];
}

- (void)dismissAdInstl
{
    if ([[[UIDevice currentDevice] systemVersion] floatValue] >= 5.0) {
        [self.adInstlController dismissViewControllerAnimated:YES completion:^{}];
    }else{
        [self.adInstlController dismissViewControllerAnimated:YES completion:^{}];
    }
    [adInstlManager adapter:self didGetEvent:InstlEventType_DidDismissAd error:nil];
}

- (BOOL)loadAdInstl:(UIViewController*)controller
{
    Class HMAdInterstitialClass = NSClassFromString(@"HMInterstitial");
    if (nil == HMAdInterstitialClass) return NO;
    Class HMAdUserMessageClass = NSClassFromString(@"HMUserMessage");
	if (nil == HMAdUserMessageClass) return NO;
    Class HMInitServerClass = NSClassFromString(@"HMInitServer");
    if (nil == HMInitServerClass) return NO;
    
    controller.modalPresentationStyle = UIModalPresentationCurrentContext;
    NSString *appID = self.networkConfig.pubId;
    NSString *userID = self.networkConfig.pubId2;
    NSString *appKey = self.networkConfig.pubId3;
    
    //开发者
    [HMUserMessage shareInstance].hmUserAppId = appID;
    [HMUserMessage shareInstance].hmUserDevId = userID;
    [HMUserMessage shareInstance].hmAppKey = appKey;
    [HMUserMessage shareInstance].hmChannel = @"IOS3.0";
    [HMUserMessage shareInstance].hmCoop_info =@"coopInfo";
    //此参数是服务器端回调必须使用的参数。值为用户id（用户指的是开发者app的用户），默认是coopinfo
    
    HMInitServer * initServer = [[HMInitServerClass alloc] init];
    [initServer getInitEscoreData:self];
    
//    CGSize adSize = CGSizeMake(270, 300);
//    CGRect appFrm = [[UIScreen mainScreen] applicationFrame];
    CGRect appFrm = [[UIScreen mainScreen] bounds];
    
//    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
//        adSize.width *= 2.0f;
//        adSize.height *= 2.0f;
//    }
    
    UIDeviceOrientation orientation = (UIDeviceOrientation)[UIApplication sharedApplication].statusBarOrientation;
    BOOL bIsLand = UIDeviceOrientationIsLandscape(orientation);
    CGFloat aWidth = bIsLand?appFrm.size.height:appFrm.size.width;
    CGFloat aHeight = bIsLand?appFrm.size.width:appFrm.size.height;
//    CGFloat sizeWidth = bIsLand?adSize.height:adSize.width;
//    CGFloat sizeHeight = bIsLand?adSize.width:adSize.height;
    
//    CGPoint adOrigin = CGPointMake((aWidth - sizeWidth)/2,
//                                   (aHeight - sizeHeight)/2);
//    
//    CGFloat labelY = ([[[UIDevice currentDevice] systemVersion] floatValue] >= 7.0)?adOrigin.y + 15: adOrigin.y;
//    
//    CGRect rect1 = CGRectMake(adOrigin.x, labelY, sizeWidth, sizeHeight);
    
//    CGRect boundRect = [[UIScreen mainScreen] bounds];
//    if (bIsLand) {
//        CGFloat tmp = boundRect.size.height;
//        boundRect.size.height = boundRect.size.width;
//        boundRect.size.width = tmp;
//    }
    AdInstlYJFAutorotate *uvc = [[AdInstlYJFAutorotate alloc] init];
    uvc.isAutoRotate  = NO;
    uvc.isFirst  = YES;
    uvc.view.backgroundColor = [UIColor clearColor];
    CGRect frame = CGRectMake(0, 0, aWidth, aHeight);
    uvc.modalTransitionStyle = UIModalTransitionStyleCoverVertical;
    uvc.view.frame = frame;
    self.adInstlController = uvc;
    
    @try {
        
        double version = [[UIDevice currentDevice].systemVersion doubleValue];
        if(version >= 7.0){
            [HMInterstitial shareInstance].uiFrame = CGRectMake(0, 20, uvc.view.frame.size.width , uvc.view.frame.size.height);
        }else{
            [HMInterstitial shareInstance].uiFrame = CGRectMake(0, 0, uvc.view.frame.size.width, uvc.view.frame.size.height);
        }
        [self.adInstlManager adapter:self requestString:@"req"];
        //  if ([initEscore isEqualToString:@"ok"]){
        
        //interstitial = [[HMAdInterstitialClass alloc]initWithFrame:boundRect andPicFrame:rect1 andOrientation:@"Landscape" andDelegate:self];
        //横屏：Landscape  竖屏：Portrait
        [[HMInterstitial shareInstance]initWithFrame:uvc.view.frame andDelegate:self];
        //将controller传入进来
        [HMInterstitial shareInstance].viewController = uvc;
    }
    @catch (NSException *exception) {
        return NO;
    }
	return YES;
}

- (BOOL)showAdInstl:(UIViewController *)controller{
    if (nil == self.adInstlController) {
        AWLogInfo(@"No YiJiFen instl exist!");
        return NO;
    }
    
    if (nil == controller) {
        AWLogInfo(@"parameter controller is nil, can not show!");
        return NO;
    }
    
    AWLogInfo(@"Start show YiJiFen instl");
    [[HMInterstitial shareInstance] show];
        
//        [interstitial release];
//        interstitial = nil;
    
    
    if ([[[UIDevice currentDevice] systemVersion] floatValue] >= 5.0) {
        [controller presentViewController:self.adInstlController animated:YES completion:^(){}];
    }else{
        [controller presentViewController:self.adInstlController animated:YES completion:^{}];
    }
    
    return YES;
}

- (void)dealloc {
    AWLogInfo(@"AdInstlAdapterYJF dealloc");
}

#pragma mark delegate

-(void)openInterstitial:(int)_value
{
    if (1 == _value) {
        [self.adInstlManager adapter:self didGetEvent:InstlEventType_WillPresentAd error:nil];
        [self.adInstlManager adapter:self requestString:@"show"];
    } else {
        [self.adInstlManager adapter:self didGetEvent:InstlEventType_FailLoadAd error:nil];
        [self.adInstlManager adapter:self requestString:@"fail"];
    }
}

-(void)closeInterstitial
{
    [self dismissAdInstl];
}

-(void)getInterstitialDataSuccess//获取数据成功
{
    [self.adInstlManager adapter:self didGetEvent:InstlEventType_DidLoadAd error:nil];
    [self.adInstlManager adapter:self requestString:@"suc"];
    
}

-(void)getInterstitialDataFail//获取数据失败
{
    [self.adInstlManager adapter:self didGetEvent:InstlEventType_FailLoadAd error:nil];
    [self.adInstlManager adapter:self requestString:@"fail"];
}

- (void)stopBeingDelegate {
    AWLogInfo(@"--YiJiFen--stopBeingDelegate");
    [HMInterstitial shareInstance].delegate = nil;
    [HMInterstitial shareInstance].viewController = nil;
    [HMInterstitial destroyDealloc];
    self.adInstlController = nil;
}
@end
