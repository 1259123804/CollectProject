

#import "NSMTableViewController.h"

NS_ASSUME_NONNULL_BEGIN

@interface NSMPageView : UIView
// 2个扩展api
@property (nonatomic, copy) void(^viewDidAppear)(NSMPageView *pageView);
@property (nonatomic, copy) void(^viewDidDisappear)(NSMPageView *pageView);
/** !!!内置的滚动视图,必须重载 */
- (UIScrollView *)pageScrollView;
@end

@class NSMPageController;
@protocol NSMPageControllerDelegate <NSObject>
@optional
/**
 顶部视图(由布局决定高度)
 自动布局模式下需在布局完成时调用[pageController reloadData]刷新header;
 */
- (UIView *)viewForHeaderInPageController:(NSMPageController *)pageController;
/** 悬浮高度 */
- (CGFloat)heightForSuspendInPageController:(NSMPageController *)pageController;
/** 悬浮视图 */
- (UIView *)viewForSuspendInPageController:(NSMPageController *)pageController;
/** 垂直方向根视图滚动代理,亦即self.tableView */
- (void)verticalScrollViewDidScroll:(UIScrollView *)scrollView;
/** 水平方向根视图滚动代理,亦即self.containerView */
- (void)horizontalScrollViewDidScroll:(UIScrollView *)scrollView;
@required
/** 分页个数 */
- (NSUInteger)numberOfViewsInPageController:(NSMPageController *)pageController;
/** 分页视图 */
- (NSMPageView *)pageController:(NSMPageController *)pageController viewForIndex:(NSUInteger)index;
@end

@interface NSMPageController : NSMTableViewController
/// 头部自动拉伸的背景图片(比如个人中心头部背景)
@property (nonatomic, strong, readonly) UIImageView *headerImageView;
/// 水平滚动的根容器.属性暴露出来仅仅是为了方便某些特殊情况下设置背景颜色
@property (nonatomic, strong, readonly) UICollectionView *containerView;
/// containerView高度偏移(正:减少)
@property (nonatomic) CGFloat containerHeightOffset;
@property (nonatomic, weak) id <NSMPageControllerDelegate> delegate;
- (void)reloadData;
@end

NS_ASSUME_NONNULL_END
