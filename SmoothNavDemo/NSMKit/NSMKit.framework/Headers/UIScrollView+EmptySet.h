

#import <UIKit/UIKit.h>

@protocol DZNEmptyDataSetSource;
@protocol DZNEmptyDataSetDelegate;
@interface UIScrollView (EmptySet) <DZNEmptyDataSetSource, DZNEmptyDataSetDelegate>
/** 图片 */
@property (nonatomic, strong) UIImage *imageForEmptySet;
/** 图片tintColor */
@property (nonatomic, copy) UIColor *imageTintColorForEmptySet;
/** 标题 */
@property (nonatomic, copy) NSAttributedString *titleForEmptySet;
/** 副标题 */
@property (nonatomic, copy) NSAttributedString *subtitleForEmptySet;
/** 按钮标题 */
@property (nonatomic, copy) NSAttributedString *buttonTitleForEmptySet;
/** 背景颜色 */
@property (nonatomic, copy) UIColor *backgroundColorForEmptySet;
/** 垂直偏移 */
@property (nonatomic) CGFloat verticalOffsetForEmptySet;
/** 垂直视图间距 */
@property (nonatomic) CGFloat verticalSpaceForEmptySet;
/** 是否支持滚动 */
@property (nonatomic) BOOL emptySetShouldAllowScroll;
/** 是否支持刷新动画 */
@property (nonatomic) BOOL emptySetShouldAnimate;
/** 是否显示 */
@property (nonatomic) BOOL emptySetShouldDisplay;
/** 图片采用原图 默认NO */
@property (nonatomic) BOOL emptySetShouldRenderingImageAlwaysOriginal;
/** 空视图设置是否展示 默认为NO */
@property (nonatomic) BOOL emptySetEnabled;
/** 点击刷新方法 */
@property (nonatomic, copy) void (^emptyRefreshingBlock)(void);

@end
