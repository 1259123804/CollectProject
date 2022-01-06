//
//  NSMViewController.h
//  NSMKit
//
//  Created by nsm on 2019/2/25.
//  Copyright © 2019 nani. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSMViewController : UIViewController
/// 默认NO,显示导航栏
@property (nonatomic) BOOL navBarHiddenWhenAppear;
/**
 是否忽略导航栏设置,默认NO
 现在各个顶部导航栏颜色千奇百怪
 preferredNavBarBackgroundImage
 preferredNavBarTintColor
 这2个基友可以满足不同VC下导航颜色不一致
 [xx addChildViewController:self];
 !!!当作为childController时,因为公用导航栏,为了不影响parentViewController的设置需要设置为YES
 YES的时候,上面2个基友不生效
 */
@property (nonatomic) BOOL ignoreNavBarSetting;
/**
 方便在父类的viewDidLoad中做一些修改
 !!!所以强烈建议将代码在initSubviews中,以防有属性或者组件未初始化
 - (void)viewDidLoad {
     [super viewDidLoad];
     
     !self.beforeViewDidLoad?:self.beforeViewDidLoad(self);
     [self initSubviews];
     !self.afterViewDidLoad?:self.afterViewDidLoad(self);
 }
 */
@property (nonatomic, copy) void(^beforeViewDidLoad)(__kindof NSMViewController *nsmVc);
@property (nonatomic, copy) void(^afterViewDidLoad)(__kindof NSMViewController *nsmVc);
/**
 刷新导航栏
 当navBarHiddenWhenAppear为YES,然后又用代码显示了导航栏,需要刷新
 因为每个控制器的导航栏颜色不一致,隐藏状态下不会刷新,如果从其他颜色控制器返回不刷新可能显示异常
 */
- (void)setNeedsNavBarUpdate;
@end


@interface NSMViewController (NSMSubclassOverride)
/** init中执行 */
- (void)didInitialize NS_REQUIRES_SUPER;
/** viewDidLoad中执行 */
- (void)initSubviews NS_REQUIRES_SUPER;
/** viewWillAppear:中执行 */
- (void)setupNavigationItems NS_REQUIRES_SUPER;
/** viewWillAppear:中执行 */
- (void)setupToolbarItems NS_REQUIRES_SUPER;
/** 收到UIContentSizeCategoryDidChangeNotification通知 */
- (void)contentSizeCategoryDidChange:(NSNotification *)note;
/**
 仅当_nsmConfig.viewControllerBasedStatusBarAppearance = NO生效
 因为此时StatusBarStyle不受preferredStatusBarStyle影响,所以需要模拟YES时候的效果
 默认_nsmConfig.statusBarStyle
 如果不采用这种方式的话.状态栏会闪一下
 比如:默认黑 A白 B白 A->B 时候
 B的viewWillAppear判断当前白不等于默认黑会先变黑,然后由于B又设置了白所以会闪一下
 */
- (UIStatusBarStyle)preferredStatusBarStyleWhenBasedOnAppDelegate;

/// 导航背景图片,默认[UIImage imageWithColor:_nsmConfig.navBarColor]
- (UIImage *)preferredNavBarBackgroundImage;
/// 导航栏目底部黑线,默认[UIImage new],功能未实现
// - (UIImage *)preferredNavBarShadowImage;
/// 导航栏items的tintColor,默认_nsmConfig.navItemsColor
- (UIColor *)preferredNavBarTintColor;
/// 导航栏items的tintColor,默认NO
- (BOOL)preferredNavBarTranslucent;

@end

NS_ASSUME_NONNULL_END

