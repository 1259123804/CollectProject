//
//  ListModel.h
//  SmoothNavDemo
//
//  Created by xiaoguang on 2022/1/12.
//  Copyright © 2022 Cloudox. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface ListModel : NSObject

@property (nonatomic, copy) NSString *name;
@property (nonatomic, copy) NSString *picture;
@property (nonatomic, assign) NSInteger min_price;
@end

NS_ASSUME_NONNULL_END
