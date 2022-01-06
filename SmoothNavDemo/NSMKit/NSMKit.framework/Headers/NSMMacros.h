//
//  NSMMacros.h
//  NSMKit
//
//  Created by nsm on 2019/2/26.
//  Copyright © 2019 nani. All rights reserved.
//

#ifndef NSMMacros_h
#define NSMMacros_h

#import "NSMInlines.h"
#import "NSMConfiguration.h"
#import "NSMUtilities.h"

#pragma mark - 全局变量
#define _noteCenter             ([NSNotificationCenter defaultCenter])
#define _keyWindow              (UIApplication.sharedApplication.delegate.window)

#pragma mark - 颜色
#define COLOR_0                 ([UIColor blackColor])
#define COLOR_1                 ([UIColor darkGrayColor])
#define COLOR_2                 ([UIColor grayColor])
#define COLOR_3                 ([UIColor lightGrayColor])
#define COLOR_4                 ([UIColor whiteColor])
#define COLOR_5                 ([UIColor clearColor])
#define COLOR_THEME             ([UIColor colorWithRed:150/255.0 green:88/255.0 blue:255/255.0 alpha:1])

#define THEME_COLOR             (_nsmConfig.themeColor)
#define NAVBAR_COLOR            (_nsmConfig.navBarColor)
#define MAIN_TEXT_COLOR         (_nsmConfig.mainTextColor)
#define SUB_TEXT_COLOR          (_nsmConfig.subTextColor)
#define SEPARATOR_COLOR         (_nsmConfig.separatorColor)
#define GROUP_TABLECOLOR        (_nsmConfig.tableViewBackgroundColor)
#define PLACEHOLDER_TEXT_COLOR  (_nsmConfig.placeholderColor)
// 浅蓝色(类支付宝)
#define LIGHT_BLUE_COLOR        HexColor(@"#A357F4")

#pragma mark - Info.plist
#define kAppDisplayName         AppDisplayName()
#define kAppBundleName          AppBundleName()
#define kAppBundleID            AppBundleID()
#define kAppBuild               AppBuild()
#define kAppVersion             AppVersion()
#define kAppIconName            AppIconName()
#define kAppIcon                AppIcon()

#pragma mark - 系统UI高度
#define kStatusBarHeight        StatusBarHeight()
#define kNavBarHeight           NavBarHeight()
#define kTabBarHeight           TabBarHeight()
#define kScreenBounds           (UIScreen.mainScreen.bounds)
#define kSafeAreaBottom         (_keyWindow.nsm_safeAreaInsets.bottom)
#define WIDTH [[UIScreen mainScreen] bounds].size.width
#define HEIGHT [[UIScreen mainScreen] bounds].size.height

#define kAutoWidth              (MyLayoutSize.wrap)
#define kAutoHeight             (MyLayoutSize.wrap)
#define kAutoSize               CGSizeMake(MyLayoutSize.wrap, MyLayoutSize.wrap)

#define kNullObject             ([NSNull null])
#define kNilImage               (NilImage())
#define kPlaceholderImage       (_nsmConfig.placeholderImage)
#define kPlaceholderAvatar      (_nsmConfig.placeholderAvatar)
#define kEmptyDataImage         (_nsmConfig.emptyDataImage)
#define kEmptyDataDesc(s)       AttributedStringFC((s), CustomFont(14), COLOR_3)

#define FormatString(fmt, ...)  [NSString stringWithFormat:fmt, ##__VA_ARGS__]

#pragma mark - 表单
#define SetBit(n, i)            ((n)|=(0x01<<(i)))
#define GetBit(n, i)            (((n)&(0x01<<(i)))?1:0)
#define ClearBit(n, i)          ((n)&=(~(0x01<<(i))))

#define nsm_weak(obj)           autoreleasepool{} __weak typeof(obj) weak##obj = obj;
#define nsm_strong(obj)         autoreleasepool{} __strong typeof(weak##obj) obj = weak##obj;

#ifndef NSM_DYNAMIC_PROPERTY_OBJECT
#define NSM_DYNAMIC_PROPERTY_OBJECT(_type_, _getter_, _setter_, _policy_) \
- (_type_)_getter_ { \
    return objc_getAssociatedObject(self, _cmd); \
} \
- (void)_setter_:(_type_)obj { \
    [self willChangeValueForKey:@#_getter_]; \
    objc_setAssociatedObject(self, @selector(_getter_), obj, OBJC_ASSOCIATION_##_policy_); \
    [self didChangeValueForKey:@#_getter_]; \
}

#define NSM_DYNAMIC_PROPERTY_ASSIGN(_type_, _value_type_, _getter_, _setter_) \
- (_type_)_getter_ { \
    NSNumber *temp = objc_getAssociatedObject(self, _cmd); \
    return temp._value_type_; \
} \
- (void)_setter_:(_type_)obj { \
    [self willChangeValueForKey:@#_getter_]; \
    objc_setAssociatedObject(self, @selector(_getter_), @(obj), OBJC_ASSOCIATION_RETAIN_NONATOMIC); \
    [self didChangeValueForKey:@#_getter_]; \
}
#endif

#endif /* NSMMacros_h */
