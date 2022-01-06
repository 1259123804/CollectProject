

#import <UIKit/UIKit.h>
#import "NSMNetworkHelper.h"

typedef NS_ENUM(NSInteger, RefreshHud) {
    RefreshHudNone      = 0,    // 无加载指示
    RefreshHudDefault   = 1,    // 默认mj
    RefreshHudCustom    = 2     // 自定义菊花
};

@interface UIScrollView (Refresh)
/// 请求方式
@property (nonatomic) NSMHttpMethod httpMethod;
/// 接口
@property (nonatomic, copy) NSString *urlString;
/// 参数
@property (nonatomic, strong) NSDictionary *parameters;
/// 加载分页类型 YES:id NO:page
@property (nonatomic) BOOL pagingWithID;
/// 分页id字符串(仅在pagingWithID==YES下有效)
@property (nonatomic, copy) NSString *idName;
/// 请求结果列表字段名，默认 _networker.listName
@property (nonatomic, copy) NSString *listName;
/// 请求结果分页字段名，默认 _networker.pageName
@property (nonatomic, copy) NSString *pageName;
/// 请求结果总页数段名，默认 _networker.countName
@property (nonatomic, copy) NSString *countName;
/// 是否开启下拉刷新
@property (nonatomic) BOOL headerRefreshEnabled;
/// 是否开启上提加载
@property (nonatomic) BOOL footerRefreshEnabled;
/// 是否自动隐藏footer,当无数据的时候,默认NO
@property (nonatomic) BOOL autoFooterHidden;

@property (nonatomic, copy) void(^willRefreshingHeader)(void);
@property (nonatomic, copy) void(^willRefreshingFooter)(void);
@property (nonatomic, copy) void(^didRefreshingHeaderSuccess)(id responseObject);
@property (nonatomic, copy) void(^didRefreshingHeaderEmpty)(id responseObject);
@property (nonatomic, copy) void(^didRefreshingHeaderFailure)(NSError *error);
@property (nonatomic, copy) void(^didRefreshingHeaderCompleted)(void);
@property (nonatomic, copy) void(^didRefreshingFooterSuccess)(id responseObject);
@property (nonatomic, copy) void(^didRefreshingFooterEmpty)(id responseObject);
@property (nonatomic, copy) void(^didRefreshingFooterFailure)(NSError *error);
@property (nonatomic, copy) void(^didRefreshingFooterCompleted)(void);

/**
 自定义上下拉事件
 由于某些原因，个别UI需要自己实现网络请求比如队列、其他请求框架等等
 此时就相当于写原生上下拉，需要在回调里取消加载动画 [mj_header/mj_footer endRefreshing]
 */
- (void)addHeaderRefreshingBlock:(void (^)(void))headerBlock;
- (void)addFooterRefreshingBlock:(void (^)(void))footerBlock;

// 开始下拉刷新
- (void)beginRefreshing:(RefreshHud)hud;
// 开始加载更多
- (void)beginRefreshingFooter:(RefreshHud)hud;

@end
