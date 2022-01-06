//
//  NSMSearchHomeController.h
//  BSProject
//
//  Created by nsm on 2019/7/6.
//  Copyright © 2019 beisheng. All rights reserved.
//

#import "NSMTableViewController.h"

NS_ASSUME_NONNULL_BEGIN

/** 操作类型 */
typedef NS_ENUM(NSInteger, NSMSearchOperate) {
    NSMSearchOperateCreate   = 0,  //!< 增
    NSMSearchOperateDelete   = 1,  //!< 删
    NSMSearchOperateClear    = 2,  //!< 全删
};

@protocol NSMSearchHomeProtocol;
@interface NSMSearchHomeController : NSMTableViewController <NSMSearchHomeProtocol>
/** 热门推荐相关接口,不传或nil只展示历史记录 */
@property (nonatomic, copy) NSString *urlString;
/** !!必须指定,有可能一个项目里有很多个搜索模块,此key则作为区分本地数据标识 */
@property (nonatomic, copy) NSString *historyCacheKey;
/** 最多保存多少条记录,默认10条 */
@property (nonatomic) NSUInteger maximumHistories;

// MARK:自定义热门数据和样式
/**
 每个项目起求的hot关键词不一样，里面格式也不一样
 @param     data    NSMResponseObject中data
 @return    热门数据数组 String|NSDictionary(必须包含"title": "搜索词")
 */
@property (nonatomic, copy) NSArray *(^extractHotFromData)(id data);
/**
 每个项目展示的热门样式也不求一样, 不要加点击跳转事件，内部会处理
 @param     item    热门数组中的单个热门数据
 @return    热门标签view
 */
@property (nonatomic, copy) UIView *(^hotItemView)(id item);

/**
 更新本地数据,外部也可以随时调用更改本地记录
 @param obj     更新的数据(目前仅支持字符串)
 @param operate 更新操作
 */
- (void)updateSearchHistory:(id)obj operate:(NSMSearchOperate)operate;

@end

NS_ASSUME_NONNULL_END
