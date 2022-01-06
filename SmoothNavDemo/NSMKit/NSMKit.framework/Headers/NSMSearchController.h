

#import "NSMViewController.h"

@class NSMButton;
@class NSMNavSearchBar;
@protocol NSMSearchHomeProtocol;
@protocol NSMSearchAssociateProtocol;
@protocol NSMSearchResultProtocol;
@interface NSMSearchController : NSMViewController
/** 搜索框 */
@property (nonatomic, strong, readonly) NSMNavSearchBar *searchBar;
/** 取消按钮 */
@property (nonatomic, strong, readonly) NSMButton *cancelBtn;
/**
 是否忽略搜索框键盘上"搜索"按钮事件,默认NO
 YES:什么也不干,比如城市筛选点了联想界面的搜索搜索还是当前
 NO:切换至搜索结果控制器
 */
@property (nonatomic) BOOL ignoreSearchBtnAction;

/**
 搜索根控制器
 请自行处理控制器内的本地缓存(增、删、改、查)
 eg:历史记录的获取、删除(单条/全部)、新增
 */
@property (nonatomic, strong) UIViewController<NSMSearchHomeProtocol> *homeController;
/** 搜索联想控制器 */
@property (nonatomic, strong) UIViewController<NSMSearchAssociateProtocol> *associateController;
/** 搜索结果控制器 */
@property (nonatomic, strong) UIViewController<NSMSearchResultProtocol> *resultController;
@end

