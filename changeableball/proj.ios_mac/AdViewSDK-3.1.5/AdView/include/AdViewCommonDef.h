//
//  AdCommonDef.h
//  AdViewDevelop
//
//  Created by laizhiwen on 14-11-5.
//  Copyright (c) 2014年 maming. All rights reserved.
//

#ifndef AdViewDevelop_AdCommonDef_h
#define AdViewDevelop_AdCommonDef_h

#define ADVIEW_VERSION_STR @"315"

#import "AdCommonNetworkType.h"

//和SDKTYPE匹配
typedef enum tagAdViewSDKType {
    AdViewSDKType_Banner = 0,
    AdViewSDKType_Instl = 1,
    AdViewSDKType_SpreadScreen = 4,
}AdViewSDKType;


BOOL isForeignAd(AdViewSDKType sdkType, int networkType);

#endif