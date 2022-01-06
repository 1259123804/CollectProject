//
//  NSObject+NSMKit.h
//  NSMKit
//
//  Created by nsm on 2019/3/12.
//  Copyright © 2019 nani. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSObject (NSMKit)
@property (nonatomic) NSUInteger maskCode;
@property (nonatomic, copy) NSString *identifierEx;
@property (nonatomic, strong) id mark;
@property (nonatomic, strong) NSDictionary *constDic;
@property (nonatomic, strong) NSMutableDictionary *mutableDic;
- (void)showAlert:(NSString *)message;
#pragma mark - 格式转换
/// NSString、NSData、JSONObject 转 NSData
- (nullable NSData *)nsm_JSONData;
/// 转NSString
- (nullable NSString *)nsm_JSONString;
/// 转JSONObject
- (nullable id)nsm_JSONObject;
#pragma mark - KVO
- (void)addNotification:(NSString *)name handler:(void(^ _Nullable)(id _Nullable obj))handler;
@end

@interface UIImage (NSMCompress)
// 设置图片的透明度，返回一张新图片
- (UIImage *)nsm_imageWithAlpha:(CGFloat)alpha;
// 压缩到指定大小以内
- (NSData *)nsm_compressWithMaxLength:(NSUInteger)maxLength;
// 整张图片平均值
- (UIColor *)nsm_averageColor;
// 获取顶部1像素色值出现最多的颜色
- (UIColor *)nsm_mainColorWithSinglePixHeight;
@end

@protocol BackBarButtonItemProtocol <NSObject>
@optional
- (BOOL)backBarButtonItemShouldPopBack;
@end

@interface UIViewController (exchange) <BackBarButtonItemProtocol>
- (UIAlertController *)showAlert:(NSString *)message action:(void (^_Nullable)(UIAlertAction *action))handler completion:(void(^_Nullable)(void))completion;
- (UIAlertController *)showAlert:(NSString *)message action:(void (^_Nullable)(UIAlertAction *action))handler;
- (UIAlertController *)showAlert:(NSString *)message cancel:(void (^_Nullable)(UIAlertAction *action))cancel done:(void (^_Nullable)(UIAlertAction *action))done;
- (UIAlertController *)showAlert:(NSString *)title message:(NSString *)message action:(void (^_Nullable)(UIAlertAction *action))done;
- (UIAlertController *)showAlert:(NSString *)title message:(NSString *)message cancel:(void (^_Nullable)(UIAlertAction *action))cancel done:(void(^_Nullable)(UIAlertAction *action))done;
@end

@interface NSDictionary (Log)
- (NSString *)printString;
@end

@interface NSString (NSMTrimSpace)
+ (NSString *)stringWithDouble:(double)value;
- (NSString *)compactString;
@end

NS_ASSUME_NONNULL_END
