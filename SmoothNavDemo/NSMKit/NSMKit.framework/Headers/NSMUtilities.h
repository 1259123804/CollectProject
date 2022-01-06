

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSMUtilities : NSObject

/// 获取最上层的UIWindow（全屏、可见)
+ (UIWindow *)topWindow;

/** 获取最上层UIViewController */
+ (UIViewController *)topViewController;

/** 获取当前活跃的UINavigationController */
+ (UINavigationController *)activeNavigationController;

/// 获取当前定位权限授权状态,不会换起调用
/// enabled         定位是否可用(隐私-定位关闭|受限|拒绝均为NO)
/// notDetermined   用户是否还未对APP做出选择，YES根据业务自己唤起授权
/// @param handler  权限状态查询回调
+ (void)locationAuthorization:(void(^)(BOOL enabled, BOOL notDetermined))handler;

/// 检测是否为手机号
/// @param str      字符串
+ (BOOL)isPhoneNumber:(NSString *)str;

+ (void)showToast:(NSString *)message onView:(nullable UIView *)view;

@end

CF_EXTERN_C_BEGIN

/// 读取本地name.json文件
/// @param name 文件名
id JSONObjectOfFile(NSString *name);

/// 复制一个对象
/// @param obj  源对象
id CloneObject(id<NSCoding> obj);
BOOL IsEqual(id obj1, id obj2);

BOOL CanOpenURL(id obj);
void OpenURL(id obj);
void Telprompt(id obj);

/// 国际化字符串(Internationalized String)
/// @param str  原字符
NSString *IStr(NSString *str);

/// NSURL、NSString 转 NSURL
/// @param url  源
NSURL *URL(id url);

/// n个简体中文占据宽度
/// @param words    文字个数
/// @param font     字体
CGFloat WithOfCHS(int words, UIFont *font);
CGFloat SinglePixel(void);
CGSize CGSizeMax(void);

// @"#a8a8a8"
UIColor *HexColor(NSString *hexStr);

CF_EXTERN_C_END

NS_ASSUME_NONNULL_END

#ifndef kSinglePixel
#define kSinglePixel    SinglePixel()
#endif

#ifndef kCGSizeMax
#define kCGSizeMax      CGSizeMax()
#endif


