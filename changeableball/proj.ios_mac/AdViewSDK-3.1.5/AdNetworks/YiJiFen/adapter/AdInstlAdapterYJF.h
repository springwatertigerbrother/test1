//
//  AdInstlAdapterYJF.h
//  AdInstlSDK_iOS
//
//  Created by Ma ming on 13-3-13.
//
//

#import "AdInstlAdNetworkAdapter.h"
#import <Eadver/HMInterstitial.h>
#import <Eadver/HMInitServer.h>


@interface AdInstlAdapterYJF : AdInstlAdNetworkAdapter<HMInterstitialDelegate,InitResultDelegate>

{
    HMInterstitial * interstitial;
}

+ (AdInstlAdNetworkType)networkType;

@end
