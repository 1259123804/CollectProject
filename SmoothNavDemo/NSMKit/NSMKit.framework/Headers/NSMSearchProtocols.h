//
//	NSMSearchProtocols.h
//
//	,-. ,-. ,-,-.
//	| | `-. | | |
//	' ' `-' ' ' '
//	Created on 2021/1/8.
//  Copyright © 2021 nani. All rights reserved.
//
    

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/** 搜索状态 */
typedef NS_ENUM(NSInteger, NSMSearchStatus) {
    NSMSearchStatusHome = 0,    //!< 搜索主页
    NSMSearchStatusAssociate,   //!< 搜索联想
    NSMSearchStatusResult,      //!< 搜索结果
};

@protocol NSMSearchHomeProtocol <NSObject>
/**
 选中了推荐或者选中了历史记录都调用这个
 如果主页接口推荐的数据类型是dic,标题字段需为"title"
 !!!重写set方法可用于特殊场景 eg:菲度客户端的vip地址搜索.选中即确定并返回
 */
@property (nonatomic, copy) void(^didSelectSearchItem)(id obj);
/** 插入一条历史搜索记录,目前只记录文字 */
- (void)insertLocal:(id)obj;
@end

@protocol NSMSearchAssociateProtocol <NSObject>
@property (nonatomic, copy) NSString *associateURL;
/**
 选中联想记录调用
 !!!重写set方法可用于特殊场景 eg:菲度客户端的vip地址搜索.选中即确定并返回
 */
@property (nonatomic, copy) void(^didSelectAssociateItem)(id obj);
/** 自定义联想扩展 */
- (void)associateWithKeywords:(NSString *)keywords;
@end

@protocol NSMSearchResultProtocol <NSObject>
/**
 选中结果后回调,内部会通知NSMSearchHomeProtocol调用insertLocal:
 !!!重写set方法将以重写方法实现为主
 */
@property (nonatomic, copy) void(^didSelectResultItem)(id obj);
/**
 在这里进行业务搜索
 obj来源
 1.主页控制器的推荐(类型不确定dic|string) 或 历史记录(string)
 2.联想控制器的联想(string)
 3.searchBar的搜索按钮(string)
 */
- (void)searchWithObject:(id)obj;
@end

NS_ASSUME_NONNULL_END
