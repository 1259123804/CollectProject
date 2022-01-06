//
//  NSMTableViewController.h
//  NSMKit
//
//  Created by nsm on 2019/2/27.
//  Copyright © 2019 nani. All rights reserved.
//

#import "NSMViewController.h"

NS_ASSUME_NONNULL_BEGIN

@class NSMTableView;
@interface NSMTableViewController : NSMViewController <UITableViewDelegate, UITableViewDataSource>

@property (nonatomic, strong, readonly) NSMTableView *tableView;
/**
 是否忽略viewDidLayoutSubviews默认实现
 self.tableView.frame = self.view.bounds
 若YES则self.tableView.frame为CGRectZero,需自行适配frame
 */
@property (nonatomic) BOOL ignoreViewDidLayoutSubviews;

/** 默认UITableViewStylePlain */
- (UITableViewStyle)preferredTableViewStyle;

@end

NS_ASSUME_NONNULL_END
