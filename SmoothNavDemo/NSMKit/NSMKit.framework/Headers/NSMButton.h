

#import <UIKit/UIKit.h>

/**
 !!!重要冲突
 
 1.NSMButtonImagePositionLeft | NSMButtonImagePositionRight
 水平布局不允许设置UIControlContentHorizontalAlignmentFill
 2.NSMButtonImagePositionTop | NSMButtonImagePositionBottom
 垂直布局不允许设置UIControlContentVerticalAlignmentFill
 */
typedef NS_ENUM(NSUInteger, NSMButtonImagePosition) {
    NSMButtonImagePositionTop,
    NSMButtonImagePositionLeft,     ///< 默认值
    NSMButtonImagePositionBottom,
    NSMButtonImagePositionRight,
};

@interface NSMButton : UIButton

#pragma mark - image位置
/** image大小, 默认CGSizeZero */
@property (nonatomic) CGSize imageSize;
/** image和title间距, 默认.0f */
@property (nonatomic) CGFloat spacing;
/** title 相当于:[self setTitle:title forState:UIControlStateNormal] */
@property (nonatomic, copy) NSString *title;
/** image 相当于:[self setImage:image forState:UIControlStateNormal] */
@property (nonatomic, strong) UIImage *image;
/** image位置, 默认NSMButtonImagePositionLeft */
@property (nonatomic) NSMButtonImagePosition imagePosition;

#pragma mark - title/image颜色
/** title颜色是否跟随tintColor变化, 默认NO */
@property (nonatomic) BOOL adjustsTitleTintColorAutomatically;
/** image颜色是否跟随tintColor变化, 默认NO */
@property (nonatomic) BOOL adjustsImageTintColorAutomatically;

#pragma mark - 高亮/禁用效果
/** 高亮时背景颜色, 默认nil */
@property (nonatomic, strong) UIColor *highlightedBackgroundColor;
/** 高亮时边框颜色, 默认nil */
@property (nonatomic, strong) UIColor *highlightedBorderColor;
/** 禁用时背景颜色, 默认nil */
@property (nonatomic, strong) UIColor *disabledBackgroundColor;
/** 禁用时边框颜色, 默认nil */
@property (nonatomic, strong) UIColor *disabledBorderColor;

/** 高亮时候是否改变image和title, 默认YES */
@property (nonatomic) BOOL adjustsWhenHighlighted;
/** 禁用时候是否改变image和title, 默认YES */
@property (nonatomic) BOOL adjustsWhenDisabled;

#pragma mark - 扩展功能
/** 无效的点击时间间隔(单位:秒), 默认0s */
@property (nonatomic) NSTimeInterval invalidTouchInterval;

- (void)didInitialize NS_REQUIRES_SUPER;

@end


