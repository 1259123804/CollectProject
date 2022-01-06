//
//  NSMNetworkHelper.h
//  NSMKit
//
//  Created by nsm on 2019/3/1.
//  Copyright © 2019 nani. All rights reserved.
//

#import <Foundation/Foundation.h>

#define _networker      ([NSMNetworkHelper sharedInstance])

typedef NS_ENUM(NSUInteger, NSMNetworkResponseState) {
    NSMNetworkResponseSuccess,
    NSMNetworkResponseEmpty,
    NSMNetworkResponseFailure,
};

typedef NS_ENUM(NSUInteger, NSMHttpMethod) {
    NSMHttpMethodPOST,  ///< 默认
    NSMHttpMethodGET,
};

@interface NSMResponseObject : NSObject
@property (nonatomic)         NSInteger code;
@property (nonatomic, copy)   NSString *desc;
@property (nonatomic, copy)   NSString *url;
@property (nonatomic, strong) id data;
@property (nonatomic, strong) NSDictionary *parameters;
@property (nonatomic)         NSMNetworkResponseState state;
@end

@class AFHTTPSessionManager;
@protocol AFMultipartFormData;
// 若根目录下server.cer文件存在则代表启用Https证书验证
@interface NSMNetworkHelper : NSObject

#pragma mark - 请求结果字段
/**
 不同的项目写的接口标准或规范不一致，但是json最外层必须得是这种格式
 这些字段最终会映射到NSMResponseObject中形成统一的字段
 {
    "code": 服务器返回状态码，数字、字符串均可,
    "desc": 服务器返回的信息,
    "data": 服务器返回数据 []或{}
    比如:
    "data": {
        "list": 列表数据 []
        "page": 当前页数，数字、字符串均可,
        "count": 总页数，数字、字符串均可,
    }
 }
 */
/// 请求结果状态码字段名，默认"code"
@property (nonatomic, copy) NSString *codeName;
/// 请求结果描述字段名，默认"desc"
@property (nonatomic, copy) NSString *descName;
/// 请求结果数据字段名，默认"data"
@property (nonatomic, copy) NSString *dataName;
/// 请求结果列表字段名，默认"list"
@property (nonatomic, copy) NSString *listName;
/// 请求结果分页字段名，默认"page"
@property (nonatomic, copy) NSString *pageName;
/// 请求结果总页数段名，默认"count"
@property (nonatomic, copy) NSString *countName;

#pragma mark - AFNetworking
/** AFHTTPSessionManager对象 */
@property (nonatomic, strong, readonly) AFHTTPSessionManager *manager;
/** AFHTTPSessionManager的baseURL */
@property (nonatomic, copy) NSString *(^baseURL)(void);

#pragma mark - 打印输出
/** 是否打印输出网络请求相关参数以及地址,默认NO */
@property (nonatomic, copy) BOOL (^shouldPrintRequest)(void);

/** 是否打印输出网络返回数据,默认NO */
@property (nonatomic, copy) BOOL (^shouldPrintResponse)(void);

/** 接口超时，默认15s */
@property (nonatomic, copy) NSTimeInterval(^timeoutInterval)(NSString *URLString, NSDictionary *parameters);

#pragma mark - 代理控制
/**
 是否允许网络被代理,默认允许YES
 @param     URLString       原始URLString
 @param     parameters      原始parameters
 若返回YES,则过滤网络请求,触发failure(error_code=600)和didFailLoad(nil, error_code=600)回调
 */
@property (nonatomic, copy) BOOL(^proxyEnabled)(NSString *URLString, NSDictionary *parameters);

#pragma mark - URL及参数处理
/**
 最终网络请求的url,可在此block中拼接完整URL
 !!如果URLString是http开头不做任何处理
 @param     URLString       原始URLString
 */
@property (nonatomic, copy) NSString *(^finalURLString)(NSString *URLString);

/**
 最终网络请求的参数,可在此block中添加默认参数,接口加密
 @param     parameters      原始parameters
 */
@property (nonatomic, copy) NSDictionary *(^finalParameters)(NSDictionary *parameters);

#pragma mark - 自定义请求结果
/**
 !!!每个项目返回数据格式都不一样，更有嵌套2层的，比如data里又返回带code码的
 如果不实现这个block则按标准走(200, 300那一套)
 @param     responseObject  接口返回的原始json数据
 @param     URLString       原始URLString
 @param     parameters      原始parameters
 @return    转换后NSMResponseObject类型数据(url, parameters不需要赋值)
 */
@property (nonatomic, copy) NSMResponseObject *(^customResponseInterceptor)(NSString *URLString, NSDictionary *parameters, id responseObject);

#pragma mark - 网络请求过程回调
/**
 对网络failure回调统一处理
 error 为nil代表接口返回的错误,比如code:40x,50x等,根据responseObject处理
 error 非nil代表系统错误,比如无网络,代理被拒绝,请求失败,此时responseObject为nil
 @param     responseObject  转换后的数据
 @param     error           错误
 */
@property (nonatomic, copy) void(^didFailLoad)(NSMResponseObject *responseObject, NSError *error);
/** 准备网路请求的时候,自行进行加载动画显示 */
@property (nonatomic, copy) void(^willStartLoad)(BOOL isShowHud);
/** 结束网路请求的时候,自行进行加载动画隐藏 */
@property (nonatomic, copy) void(^didFinishLoad)(BOOL isShowHud);

+ (instancetype)sharedInstance;

// MARK:POST
- (NSURLSessionDataTask *)POST:(NSString *)URLString
                    parameters:(NSDictionary *)parameters
                       success:(void (^)(NSMResponseObject *responseObject))success
                         empty:(void (^)(NSMResponseObject *responseObject))empty
                       failure:(void (^)(NSError *error))failure;

- (NSURLSessionDataTask *)POST:(NSString *)URLString
                    parameters:(NSDictionary *)parameters
                       success:(void (^)(NSMResponseObject *responseObject))success
                         empty:(void (^)(NSMResponseObject *responseObject))empty
                       failure:(void (^)(NSError *error))failure
                           hud:(BOOL)isShowHud;

- (NSURLSessionDataTask *)POST:(NSString *)URLString
                    parameters:(NSDictionary *)parameters
                 formDataBlock:(void (^)(id <AFMultipartFormData> formData))block
                       success:(void (^)(NSMResponseObject *responseObject))success
                         empty:(void (^)(NSMResponseObject *responseObject))empty
                       failure:(void (^)(NSError *error))failure;

- (NSURLSessionDataTask *)POST:(NSString *)URLString
                    parameters:(NSDictionary *)parameters
                 formDataBlock:(void (^)(id <AFMultipartFormData> formData))block
                       success:(void (^)(NSMResponseObject *responseObject))success
                         empty:(void (^)(NSMResponseObject *responseObject))empty
                       failure:(void (^)(NSError *error))failure
                           hud:(BOOL)isShowHud;

- (NSURLSessionDataTask *)POST:(NSString *)URLString
                    parameters:(NSDictionary *)parameters
                 formDataBlock:(void (^)(id <AFMultipartFormData> formData))block
                      progress:(void (^)(NSProgress *uploadProgress))uploadProgress
                       success:(void (^)(NSMResponseObject *responseObject))success
                         empty:(void (^)(NSMResponseObject *responseObject))empty
                       failure:(void (^)(NSError *error))failure
                           hud:(BOOL)isShowHud;

// MARK:GET
- (NSURLSessionDataTask *)GET:(NSString *)URLString
                    parameters:(NSDictionary *)parameters
                       success:(void (^)(NSMResponseObject *responseObject))success
                         empty:(void (^)(NSMResponseObject *responseObject))empty
                       failure:(void (^)(NSError *error))failure;

- (NSURLSessionDataTask *)GET:(NSString *)URLString
                    parameters:(NSDictionary *)parameters
                       success:(void (^)(NSMResponseObject *responseObject))success
                         empty:(void (^)(NSMResponseObject *responseObject))empty
                       failure:(void (^)(NSError *error))failure
                           hud:(BOOL)isShowHud;
@end
