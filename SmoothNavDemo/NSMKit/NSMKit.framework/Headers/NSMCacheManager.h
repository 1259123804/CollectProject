

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#ifndef _cacheManager
#define _cacheManager   ([NSMCacheManager sharedInstance])
#endif

@class YYCache;
@interface NSMCacheManager : NSObject
/**
 验证码缓存
 NSMSMSButton相关缓存
 */
@property (nonatomic, strong, readonly) YYCache *smsCache;
/**
 搜索缓存
 NSMSearchController相关缓存
 */
@property (nonatomic, strong, readonly) YYCache *searchCache;
/**
 城市缓存
 NSMCitySelectorController相关缓存
 */
@property (nonatomic, strong, readonly) YYCache *csCache;

/// 默认缓存
@property (nonatomic, strong, readonly) YYCache *defaultCache;

/** 自定义的缓存 */
- (YYCache *)cacheWithName:(NSString *)name;

+ (instancetype)sharedInstance;

@end

NS_ASSUME_NONNULL_END
