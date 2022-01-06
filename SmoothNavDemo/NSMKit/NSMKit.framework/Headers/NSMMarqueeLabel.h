//
//  NSMMarqueeLabel.h
//  SmartVideo
//
//  Created by nsm on 2019/3/27.
//  Copyright © 2019 nani. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSMMarqueeLabel : UILabel
/// 滚动速度(内部CADisplayLink调用一次滚动距离), 默认0.5
@property (nonatomic) CGFloat speed;
/// 循环滚动次数，0:无限循环
@property (nonatomic) NSUInteger repeatCount;
/// 首尾连接的间距，默认44，仅 repeatCount != 1 生效
@property (nonatomic) CGFloat spacing;
/// 开始滚动延时(单位:秒)，默认2s
@property (nonatomic) NSTimeInterval delayTime;
/// 是否启用首尾渐变效果，默认YES
@property (nonatomic) BOOL fadeEnabled;
/// 首部渐变部分占整个宽度的百分比，默认0.1，仅 fadeEnabled = YES 生效，首尾相加不能>1
@property (nonatomic) CGFloat headFadePercent;
/// 尾部渐变部分占整个宽度的百分比，默认0.1，仅 fadeEnabled = YES 生效，首尾相加不能>1
@property (nonatomic) CGFloat tailFadePercent;
/// 文字是否从渐变后面开始滚动，默认NO
@property (nonatomic) BOOL textStartAfterFade;
/// 文字是否从渐变前面停止滚动，默认NO
@property (nonatomic) BOOL textEndBeforeFade;

/// 开始滚动
- (void)startScroll;
/// 停止滚动
- (void)stopScroll;

@end

NS_ASSUME_NONNULL_END
