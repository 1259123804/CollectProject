//
//  NSMNavigationController.h
//  NSMKit
//
//  Created by nsm on 2019/2/25.
//  Copyright © 2019 nani. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSMNavigationController : UINavigationController

/**
 便捷方法,省的写一大串
 替代initWithRootViewController:
 */
+ (instancetype)controller:(UIViewController *)rootViewController;

@end

NS_ASSUME_NONNULL_END
