//
//  AdSpreadScreenManager.h
//  AdSpreadScreenSDK_iOS
//
//  Created by zhiwen on 12-12-27.
//  Copyright 2012 www.adview.cn. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AdSpreadScreenManagerDelegate.h"

//按比例或者按优先级选择广告平台进行播放。
typedef enum {
    AdSpreadScreenRequestMethod_Percentage = 0,
    AdSpreadScreenRequestMethod_Priority,
}AdSpreadScreenRequestMethod;

@interface AdSpreadScreenManager : NSObject {
	id<AdSpreadScreenManagerDelegate> __weak delegate;
	
	NSString *adSpreadScreenKey;
    NSString *appChannel;
    BOOL autoRoll;
    
    AdSpreadScreenRequestMethod   requestMethod;
}

/**
 * 托管对象，注意如果要释放AdSpreadScreenManager，先将这个值设为nil。
 * 如果要切换托管对象，请确保切换后的对象有效
 */
@property (nonatomic, weak) id<AdSpreadScreenManagerDelegate> delegate;

@property (nonatomic, retain) NSString *adSpreadScreenKey;		//same as adviewKey.
@property (nonatomic, retain) NSString *appChannel;   //like appstore, cydia, 91Store, etc.

/**
 * 如果加载插屏广告失败，则是否自动切换到下一个插屏广告平台的标志。显示失败不会自动切换。
 * 缺省为YES
 */
@property (nonatomic, assign) BOOL autoRoll;

/**
 * 选择广告平台的方式，缺省为按比例选择广告平台，可设为按优先级选择，则比例不起任何作用。
 */
@property (nonatomic, assign) AdSpreadScreenRequestMethod   requestMethod;

+ (id)managerWithAdSpreadScreenKey:(NSString*)key
		   WithDelegate:(id<AdSpreadScreenManagerDelegate>)aDelegate;

/**
 * 请求开屏广告;parent为开屏广告所放的controller（一般为window的rootViewController）
 */
- (BOOL)requestAdSpreadScreenView:(UIViewController*)parent;

///**
// * 单个展示广告平台
// */
//- (BOOL)requestSingleAdSpreadScreenView:(UIViewController*)parent withIndex:(int)index;

/**
 * 当前广告加载状态
 */
- (AdSpreadScreenLoadType)loadType;

/**
 * 当前广告平台名称
 */
- (NSString *)currentNetworkName;

/**
 * 获取当前的渠道号
 */
- (NSString *)marketChannel;

@end
