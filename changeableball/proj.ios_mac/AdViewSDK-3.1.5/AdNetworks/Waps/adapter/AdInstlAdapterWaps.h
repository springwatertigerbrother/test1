//
//  AdInstlAdapterWaps.h
//  AdInstlSDK_iOS
//
//  Created by Ma ming on 13-3-18.
//
//

#import "AdInstlAdNetworkAdapter.h"

@interface AdInstlAdapterWaps : AdInstlAdNetworkAdapter {
}

@property (nonatomic, weak) UIViewController *rootController;

+ (AdInstlAdNetworkType)networkType;

@end
