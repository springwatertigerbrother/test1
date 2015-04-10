//
//  AdInstlAdapterMobiSage.h
//  AdInstlSDK_iOS
//
//  Created by Ma ming on 13-5-31.
//
//

#import "AdInstlAdNetworkAdapter.h"
#import "MobiSageSDK.h"
#import "MobiSageNative.h"

@interface AdInstlAdapterMobiSage : AdInstlAdNetworkAdapter <MobiSageFloatWindowDelegate> {
    BOOL isStatusHidden;
}

@property (retain, nonatomic) MobiSageFloatWindow * mobiSageView;
@property (weak, nonatomic) UIViewController *parent;
@property (nonatomic, assign) BOOL isStatusHidden;

+ (AdInstlAdNetworkType)networkType;

@end
