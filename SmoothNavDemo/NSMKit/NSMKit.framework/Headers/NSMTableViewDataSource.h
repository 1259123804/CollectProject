

#import <Foundation/Foundation.h>
#import "NSMTableViewCell.h"

@interface NSMTableViewDataSource : NSObject <UITableViewDataSource>
/** 不同indexPath下cell类型 */
@property (nonatomic, copy) Class (^classForCellAtIndexPath)(NSIndexPath *indexPath);
/** 不同section下最后一个cell分割线是否隐藏,默认YES */
@property (nonatomic, copy) BOOL (^lastSeparatorLineHiddenAtSection)(NSInteger section);
/** 不同indexPath下cell事件 */
@property (nonatomic, copy) CellActionBlock (^actionForCellAtIndexPath)(NSIndexPath *indexPath);
/** 列表数据 */
@property (nonatomic, strong) NSMutableArray *dataArray;
@end


@interface UITableView (DataSource)
@property (nonatomic, strong) NSMTableViewDataSource *sourceManager;
@end
