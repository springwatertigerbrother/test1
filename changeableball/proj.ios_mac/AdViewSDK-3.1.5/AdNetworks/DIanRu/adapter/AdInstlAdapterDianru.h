//
//  AdInstlAdapterDianru.h
//  AdInstlSDK_iOS
//
//  Created by adview on 14-2-25.
//
//

#import "AdInstlAdNetworkAdapter.h"
#import "TalkingDataAdAntiFraud.h"
#import "TalkingDataSDK.h"
#import "label_set.h"

@interface AdInstlAdapterDianru : AdInstlAdNetworkAdapter<YQLDelegate>

+ (AdInstlAdNetworkType)networkType;

@property (nonatomic, retain) UIView * adView;
@property (nonatomic, assign) UIViewController *rootController;

@end
