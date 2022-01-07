//
//  XGPerson.h
//  SmoothNavDemo
//
//  Created by xiaoguang on 2022/1/7.
//  Copyright © 2022 Cloudox. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface XGPerson : NSObject

@property (nonatomic, copy) NSString *name;

+ (void)haveMeal:(NSString *)food;
- (void)singSong:(NSString *)song;

@end

NS_ASSUME_NONNULL_END
