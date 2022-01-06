//
//  NSMConfiguration.h
//  NSMKit
//
//  Created by nsm on 2019/2/27.
//  Copyright © 2019 nani. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

#define _nsmConfig  ([NSMConfiguration sharedInstance])

@protocol NSMConfiguration <NSObject>
@end

@interface NSMConfiguration : NSObject
#pragma mark - 全局
/** Info.plist对应 */
@property (nonatomic, readonly) BOOL viewControllerBasedStatusBarAppearance;
/** 默认为Info.plist值,且仅当viewControllerBasedStatusBarAppearance为YES生效 */
@property (nonatomic) UIStatusBarStyle statusBarStyle;

#pragma mark - 通用
@property (nonatomic, strong) UIColor *themeColor;
@property (nonatomic, strong) UIColor *backgroundColor;
@property (nonatomic, strong) UIColor *separatorColor;
@property (nonatomic, strong) UIColor *placeholderColor;
@property (nonatomic, strong) UIColor *mainTextColor;
@property (nonatomic, strong) UIColor *subTextColor;

#pragma mark - 导航栏
/**
 非透明导航栏背景颜色(除非深度了解alpha影响)
 最终实现以图片形式设置背景
 */
@property (nonatomic, strong) UIColor *navBarColor;
/** 中间title的颜色 */
@property (nonatomic, strong) UIColor *navTitleColor;
/** 左右items正常状态的颜色 */
@property (nonatomic, strong) UIColor *navItemsColor;
/** 左右items禁止点击的颜色 */
@property (nonatomic, strong) UIColor *navItemsDisabledColor;
/** 左右items的字体 */
@property (nonatomic, strong) UIFont *navItemsFont;

#pragma mark - UITableView相关
@property (nonatomic, strong) UIColor *tableViewBackgroundColor;

#pragma mark - 图片
/// UIScrollView及子类空视图时候图片
@property (nonatomic, strong) UIImage *emptyDataImage;
/// 默认图片
@property (nonatomic, strong) UIImage *placeholderImage;
/// 默认头像
@property (nonatomic, strong) UIImage *placeholderAvatar;

#pragma mark - 加载loading
/// x.isLoading = YES 菊花缩放，默认1.0（!!!废弃）
@property (nonatomic) CGFloat loadingIndicatorScale DEPRECATED_ATTRIBUTE;
/// x.isLoading = YES 菊花样式，默认UIActivityIndicatorViewStyleGray
@property (nonatomic) CGFloat loadingIndicatorStyle;

+ (instancetype)sharedInstance;

@end

NS_ASSUME_NONNULL_END


