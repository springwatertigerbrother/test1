/*

adview.
 
*/

#import "AdInstlAdNetworkAdapter.h"
#import "IMInterstitial.h"
#import "InMobi.h"

@interface AdInstlAdapterInMobi : AdInstlAdNetworkAdapter<IMInterstitialDelegate> {
   
}

+ (AdInstlAdNetworkType)networkType;

@end
