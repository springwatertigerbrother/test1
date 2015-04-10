//
//  AdInstlManager.h
//  AdInstlSDK_iOS
//
//  Created by zhiwen on 12-12-27.
//  Copyright 2012 www.adview.cn. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AdInstlManagerDelegate.h"

//按比例或者按优先级选择广告平台进行播放。
typedef enum {
    AdInstlRequestMethod_Percentage = 0,
    AdInstlRequestMethod_Priority,
}AdInstlRequestMethod;

@interface AdInstlManager : NSObject {
	id<AdInstlManagerDelegate> __weak delegate;
	
	NSString *adInstlKey;
    NSString *appChannel;
    BOOL autoRoll;
    
    AdInstlRequestMethod   requestMethod;
}

/**
 * 托管对象，注意如果要释放AdInstlManager，先将这个值设为nil。
 * 如果要切换托管对象，请确保切换后的对象有效
 */
@property (nonatomic, weak) id<AdInstlManagerDelegate> delegate;

@property (nonatomic, retain) NSString *adInstlKey;		//same as adviewKey.
@property (nonatomic, retain) NSString *appChannel;   //like appstore, cydia, 91Store, etc.

/**
 * 如果加载插屏广告失败，则是否自动切换到下一个插屏广告平台的标志。显示失败不会自动切换。
 * 缺省为YES
 */
@property (nonatomic, assign) BOOL autoRoll;

/**
 * 选择广告平台的方式，缺省为按比例选择广告平台，可设为按优先级选择，则比例不起任何作用。
 */
@property (nonatomic, assign) AdInstlRequestMethod   requestMethod;

+ (id)managerWithAdInstlKey:(NSString*)key
		   WithDelegate:(id<AdInstlManagerDelegate>)_delegate;

/**
 * 预加载广告
 * 如果要改变delegate，请在调用本函数前设置delegate
 */
- (BOOL)loadAdInstlView:(UIViewController*)parent;

/**
 * 展示广告
 */
- (BOOL)showAdInstlView:(UIViewController*)parent;

/**
 * 单个展示广告平台
 */
- (BOOL)loadSingleAdInstlView:(UIViewController*)parent withIndex:(int)index;

/**
 * 广告是否已经加载完成
 */
- (BOOL)isReady;

/**
 * 当前广告加载状态
 */
- (AdInstlLoadType)loadType;

/**
 * 当前广告平台名称
 */
- (NSString *)currentNetworkName;

/**
 * 获取当前的渠道号
 */
- (NSString *)marketChannel;

@end
