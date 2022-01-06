//
//  UIView+NSMKit.h
//  NSMKit
//
//  Created by nsm on 2019/2/28.
//  Copyright © 2019 nani. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, NSMBorderMask) {
    NSMBorderMaskNone           = 0,
    NSMBorderMaskTop            = 1 << 0,
    NSMBorderMaskLeft           = 1 << 1,
    NSMBorderMaskBottom         = 1 << 2,
    NSMBorderMaskRight          = 1 << 3,
    NSMBorderMaskAll            = (1 << 4) - 1,
};

typedef NS_ENUM(NSUInteger, NSMBorderMode) {
    NSMBorderModeInside         = 0,
    NSMBorderModeCenter         = 1,
    NSMBorderModeOutside        = 2
};

typedef NS_OPTIONS(NSUInteger, NSMCornerMask) {
    NSMCornerMaskNone           = 0,
    NSMCornerMaskUpperLeft      = 1 << 0,
    NSMCornerMaskUpperRight     = 1 << 1,
    NSMCornerMaskLowerLeft      = 1 << 2,
    NSMCornerMaskLowerRight     = 1 << 3,
    NSMCornerMaskAll            = (1 << 4) - 1,
};

@interface UIView (NSMKit)
/// 安全区域
@property (nonatomic, readonly) UIEdgeInsets nsm_safeAreaInsets;
/// 改变响应区域（负:向外扩大，正:向内缩小）
@property (nonatomic) UIEdgeInsets nsm_outsideEdgeInsets;
/**
 布局刷新之后，此时frame已经确定
 - (void)layoutSubviews {
     [super layoutSubviews];
     self.nsm_endLayoutSubviews(self);
 }
 */
@property (nonatomic, copy) void(^nsm_endLayoutSubviews)(UIView *view);
@end

@interface UIView (NSMCorner)
/// 为每个角设置不同的圆角
/// @param corners      圆角位置
/// @param radius       圆角半径
- (void)setCorners:(NSMCornerMask)corners radius:(CGFloat)radius;
@end

@interface UIView (NSMBorder)
/// 边框类型, 默认NSMBorderMaskNone
// @property (nonatomic) NSMBorderMask nsm_maskedBorders;
/// 边框位置, 默认NSMBorderModeInside
// @property (nonatomic) NSMBorderMode nsm_borderMode;
/**
 边框, 详细的设置边框属性调用系统实现, 大小、颜色为下面的默认值
 大小 self.nsm_borderLayer.lineWidth = kSinglePixel;
 颜色 self.nsm_borderLayer.strokeColor = THEME_COLOR.CGColor;
 虚线 self.nsm_borderLayer.lineDashPattern、lineDashPhase
 */
// @property (nonatomic, strong, readonly) CAShapeLayer *nsm_borderLayer;
@end

@interface UIView (NSMHitTest)
/// hitTest:withEvent:是否返回自身 YES:nil
@property (nonatomic) BOOL ignoreHitTest;
@end

NS_ASSUME_NONNULL_END
