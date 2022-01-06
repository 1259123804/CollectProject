

#import <UIKit/UIKit.h>

/** 验证码倒计时策略模式 */
typedef NS_ENUM(NSUInteger, NSMSMSCountdownPolicy) {
    NSMSMSCountdownDoneElseBack,    //!< 倒计时结束或返回
    NSMSMSCountdownDoneElseRestart, //!< 倒计时结束或重启APP
    NSMSMSCountdownUntilDone,       //!< 直到倒计时结束(默认)
};

@interface NSMSMSButton : UIButton

/** 倒计时(单位:s),默认60s */
@property (nonatomic) NSTimeInterval countdownInterval;

/** 倒计时策略,默认NSMSMSCountdownUntilDone */
@property (nonatomic) NSMSMSCountdownPolicy countdownPolicy;

/**
 分组tag, 默认为0
 相同groupTag下的按钮共享倒计时时间
 eg:同一策略模式下注册和忘记密码倒计时分开
 */
@property (nonatomic) NSInteger groupTag;

/**
 点击按钮事件
 @param completion  网络请求成功或失败回调
 
 NSMSMSButton *smsBtn = NSMSMSButton.new;
 ...
 smsBtn.onActionHandler = ^(void (^completion)(BOOL)) {
    发起网络请求
    [self requestCode:completion];
 };
 */
@property (nonatomic, copy) void(^onActionHandler)(void(^completion)(BOOL));

// 默认正常:白底黑字 | 倒计时:灰底深灰字 圆角3 87*27 字体13
@property (nonatomic, copy) UIColor *normalBackgroundColor;
@property (nonatomic, copy) UIColor *disabledBackgroundColor;
@property (nonatomic, copy) UIColor *normalTitleColor;
@property (nonatomic, copy) UIColor *disabledTitleColor;
@property (nonatomic) CGFloat cornerRadius;

- (void)reloadAndUpdate;

@end
