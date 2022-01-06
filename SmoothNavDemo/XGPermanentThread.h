//
//  XGPermanentThread.h
//  SmoothNavDemo
//
//  Created by xiaoguang on 2022/1/5.
//  Copyright © 2022 Cloudox. All rights reserved.
//

#import <Foundation/Foundation.h>
#define XGPerThread [XGPermanentThread sharedPermanentThread]
NS_ASSUME_NONNULL_BEGIN

///常驻线程，线程保活
@interface XGPermanentThread : NSObject

+ (instancetype)sharedPermanentThread;

- (void)handleTask:(void(^)(void))threadTask;
- (void)cancelTask;
@end

NS_ASSUME_NONNULL_END
