//
//  NSMImageView.h
//  Belt
//
//  Created by nsm on 2017/12/11.
//  Copyright © 2017年 beisheng. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface NSMImageView : UIImageView
@property (nonatomic, strong) NSData *imageData;
/** 单击 */
@property (nonatomic, copy) void(^tapActionBlock)(NSMImageView *sender);
/** 长按 */
@property (nonatomic, copy) void(^longPressActionBlock)(NSMImageView *sender);
/** 拖拽 */
@property (nonatomic, copy) void(^panActionBlock)(NSMImageView *sender, UIPanGestureRecognizer *pan);
@end
