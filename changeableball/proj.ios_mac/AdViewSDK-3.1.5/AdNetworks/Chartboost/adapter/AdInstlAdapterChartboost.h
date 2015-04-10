/*

adview.
 
*/

#import "AdInstlAdNetworkAdapter.h"
#import <Chartboost/Chartboost.h>

@interface AdInstlAdapterChartboost : AdInstlAdNetworkAdapter <ChartboostDelegate> {
    
    BOOL        bLoadedCache;
    BOOL        didShow;
}

+ (AdInstlAdNetworkType)networkType;

@end
