//
//	NSMCollectionViewCell.h
//
//	,-. ,-. ,-,-.
//	| | `-. | | |
//	' ' `-' ' ' '
//	Created on 2021/7/3.
//  Copyright © 2021 nani. All rights reserved.
//
    

#import <UIKit/UIKit.h>
#import "NSMTableViewCell.h"

NS_ASSUME_NONNULL_BEGIN

@interface NSMCollectionViewCell : UICollectionViewCell
@property (nonatomic, copy) void(^actionBlock)(id obj);

- (void)setupSubviews;
- (void)setObject:(id)obj;

@end

NS_ASSUME_NONNULL_END
