

#import <UIKit/UIKit.h>

typedef void(^CellActionBlock)(id obj);

@class MyBaseLayout;
@interface NSMTableViewCell : UITableViewCell
@property (nonatomic, copy) CellActionBlock actionBlock;
@property (nonatomic, strong) MyBaseLayout *rootLayout;

+ (instancetype)cell:(UITableView *)tableView;

- (void)setupSubviews;
- (void)setObject:(id)obj;

@end
