//
//  OSTools.h
//  OverseaProject
//
//  Created by xiaoguang on 2021/12/27.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#define OSTool [OSTools sharedTools]
NS_ASSUME_NONNULL_BEGIN
@interface ProductModel : NSObject <NSCoding>

@property (nonatomic, copy) NSString *platform;
@property (nonatomic, copy) NSString *productId;
@property (nonatomic, copy) NSString *updateTime;
@property (nonatomic, copy) NSString *rechargeConfigId;
@property (nonatomic, copy) NSString *type;
@property (nonatomic, copy) NSString *currency;
@property (nonatomic, copy) NSString *createTime;
@property (nonatomic, copy) NSString *money;
@property (nonatomic, assign) NSInteger vipDay;
@property (nonatomic, assign) NSInteger diamonds;

@end


@interface OSTools : NSObject

+ (instancetype)sharedTools;
@property (nonatomic, strong) ProductModel *vipProductModel;
@property (nonatomic, weak) UIViewController *currentController;
@property (nonatomic, copy) void(^selectedImage)(NSArray *selectImages);
@property (nonatomic, copy) void(^selectedVideo)(UIImage *thumbImage, NSString *videoUrl);
@property (nonatomic, strong) NSMutableArray *diamondProductArr;
@property (nonatomic, copy) NSString *oppositeId; //匹配对象的id
@property (nonatomic, copy) NSString *isVideoing; //是否在视频中

//设置状态栏颜色
- (void)setStatusBarBackgroundColor:(UIColor *)color;
/**
 * View切圆角  (CGSize)radii未View的size时，切出圆形
 */
- (UIView*)getCutRadiiWithView:(UIView*)view radii:(CGSize)radii;

//获取视频的缩略图
- (UIImage*)getVideoPreViewImage:(NSString *)path isInterNetUrl:(BOOL)isInternet;

/**
 * 根据URL获取网络音频时长
 */
- (CGFloat)audioDurationFromURL:(NSString *)url;

/**
 * 自定义导航按钮
 */
- (void)createTextBar:(NSString *)text target:(UIViewController*)targetVC action:(SEL)action isLeft:(BOOL)isLeft;

/**
 * 传入格式获取当前时间
 * @param format 时间格式
 * @return 规定格式的当前时间
 */
- (NSString*)getNowDateStrWithFormat:(NSString*)format;

//打开相机或相册
- (void)alertPhotoSelectorWithController:(UIViewController *)currentController;
//选择视频或者录制视频
- (void)alertVideoSelectorWithController:(UIViewController *)currentController;

//视图转图片
- (UIImage *)convertViewToImage:(UIView *)view;
//获取所有的product
- (void)getAllProductSuccess:(void(^)(void))success failure:(void(^)(void))failure;
//生成订单
- (void)createPayOrderWithChargeId:(NSInteger)chargeId productId:(NSString *)productId success:(void(^)(NSMResponseObject *responseObject))success failure:(void(^)(void))failure;
//开始支付
- (void)buyProductWithProductId:(NSString *)productId orderSn:(NSString *)orderSn success:(void(^)(NSMResponseObject *responseObject))success failure:(void(^)(void))failure;
@end

NS_ASSUME_NONNULL_END
