//
//  AdInstlAdapterGuoHe.h
//  AdInstlSDK_iOS
//
//  Created by Ma ming on 13-5-16.
//
//

#import "AdInstlAdNetworkAdapter.h"
#import "MIXViewDelegate.h"
#import "MIXView.h"
#import "adViewLog.h"

//@interface MixViewShare : MIXView
//
//@end
//
//static NSString * oldAppId = nil;
//static MixViewShare *mixshare = nil;
//static BOOL testMode = NO;
//@implementation MixViewShare
//
//+(MixViewShare*)shareInit:(NSString *)appId andTest:(BOOL)isTest
//{
//    if (mixshare == nil ||![oldAppId isEqualToString:appId]||testMode != isTest) {
//        mixshare = nil;
//        AWLogInfo(@"+++++====+++==%@,==++%d",oldAppId,testMode);
//        oldAppId = appId;
//        testMode = isTest;
//        mixshare = (MixViewShare *)[MIXView initWithID:appId];
//        
//    }
//    return mixshare;
//}
//
//@end

@interface AdInstlAdapterGuoHe : AdInstlAdNetworkAdapter<MIXViewDelegate> {
    
}

+ (AdInstlAdNetworkType)networkType;

@property (nonatomic, retain) MIXView * mixView;
//@property (nonatomic, weak) UIViewController * parent;

@end
