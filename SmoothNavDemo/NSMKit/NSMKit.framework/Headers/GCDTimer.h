//
//  GCDTimer.h
//  bkshell
//
//  Created by nsm on 2018/3/30.
//  Copyright © 2018年 prin. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface GCDTimer : NSObject

@property (nonatomic, copy, readonly) GCDTimer *(^queue)(dispatch_queue_t queue);
@property (nonatomic, copy, readonly) GCDTimer *(^parameters)(NSTimeInterval delay, NSTimeInterval interval);
@property (nonatomic, copy, readonly) GCDTimer *(^eventHandler)(void(^)(void));

@property (nonatomic, copy, readonly) GCDTimer *(^resume)(void);
@property (nonatomic, copy, readonly) GCDTimer *(^pause)(void);
@property (nonatomic, copy, readonly) GCDTimer *(^cancel)(void);

@end
