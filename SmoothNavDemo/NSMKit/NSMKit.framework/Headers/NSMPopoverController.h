

#import "NSMViewController.h"

@interface NSMPresentationController : UIPresentationController
@end

@interface NSMPopoverController : NSMViewController
/** 动画持续时间, 默认0.3s */
@property (nonatomic) NSTimeInterval popoverTransitionDuration;
/** 点击背景是否自动消失, 默认YES */
@property (nonatomic) BOOL autoDismission;
/** 转场控制器 */
@property (nonatomic, copy) Class presentationClass;
@property (nonatomic, copy) void(^containerViewWillLayoutSubviews)(NSMPresentationController *presentationController);

/** 显示动画, 完成后必须执行 [context completeTransition:YES], 否则视图无法点击 */
@property (nonatomic, copy) void(^presentationAnimation)(NSTimeInterval duration, UIView *view, id<UIViewControllerContextTransitioning> context);
/** 消失动画, 完成后必须执行 [context completeTransition:YES], 否则视图无法点击 */
@property (nonatomic, copy) void(^dismissalAnimation)(NSTimeInterval duration, UIView *view, id<UIViewControllerContextTransitioning> context);
@end


@interface UIViewController (NSMPopoverController)
/**
 弹出一个带导航的控制器
 为了方便扩展内部会包装一个NSMNavigationController导航
 
 @param controller  视图控制器
 @param animated    是否动画
 @param completion  弹出回调
 */
- (void)presentPopoverController:(NSMPopoverController *)controller
                        animated:(BOOL)animated
                      completion:(void (^)(void))completion;

/**
 和显示成对调用
 效果相当于
 [self.presentedViewController dismissViewControllerAnimated:YES completion:completion];

 @param animated    是否动画
 @param completion  消失回调
 */
- (void)dismissPopoverControllerAnimated:(BOOL)animated
                              completion:(void (^)(void))completion;
@end
