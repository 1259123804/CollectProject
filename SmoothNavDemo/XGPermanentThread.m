//
//  XGPermanentThread.m
//  SmoothNavDemo
//
//  Created by xiaoguang on 2022/1/5.
//  Copyright © 2022 Cloudox. All rights reserved.
//

#import "XGPermanentThread.h"

@interface XGPermanentThread ()

@property (nonatomic, strong) NSThread *perThread;
@property (nonatomic, assign) BOOL isStop;
@end
@implementation XGPermanentThread

+ (instancetype)sharedPermanentThread{
    
    static XGPermanentThread *sharedThread = nil;
    static dispatch_once_t once;
    dispatch_once(&once, ^{
       
        sharedThread = [[XGPermanentThread alloc] init];
    });
    return sharedThread;
}

- (instancetype)init{
    
    if (self = [super init]) {
        
        __weak typeof(self) weakSelf = self;
        self.perThread = [[NSThread alloc] initWithBlock:^{
           
            [[NSRunLoop currentRunLoop] addPort:[[NSPort alloc] init] forMode:NSDefaultRunLoopMode];
            while (!weakSelf.isStop) {
                
                [[NSRunLoop currentRunLoop] runMode:NSDefaultRunLoopMode beforeDate:[NSDate distantFuture]];
            }
        }];
        [self.perThread start];
    }
    return self;
}

- (void)handleTask:(void(^)(void))threadTask{

    if (!self.perThread || !threadTask) {
        
        return;
    }
    [self performSelector:@selector(__handleTask:) onThread:self.perThread withObject:threadTask waitUntilDone:NO];
}

- (void)cancelTask{
    
    if (!self.perThread) {
        
        return;
    }
    [self performSelector:@selector(stop) onThread:self.perThread withObject:nil waitUntilDone:YES];
}

- (void)stop{
    
    self.isStop = YES;
    CFRunLoopStop(CFRunLoopGetCurrent());
    self.perThread = nil;
}

- (void)__handleTask:(void(^)(void))task{
    
    task();
}
@end


