//
//  NSMPinterestLayout.h
//  湖北北盛网络科技有限公司
//
//  Created by nsm on 2018/12/31.
//  Copyright © 2019 nani. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, NSMPinterestStyle){
    NSMPinterestStyleVertical,
    NSMPinterestStyleHorizontal
};

@interface NSMPinterestLayout : UICollectionViewLayout

/**
 不同section的布局类型,默认NSMPinterestStyleVertical
 注意:
 1.严禁水平和垂直同时存在,以防contentSize水平无穷大和垂直无穷大(自行脑补)
 2.如果两者非要同时存在,那么将水平瀑布流所在分组内嵌一个水平瀑布流
 */
@property (nonatomic, copy) NSMPinterestStyle (^styleForItemInSection)(NSInteger section);
/** 不同section的cell行数/列数,默认1 */
@property (nonatomic, copy) NSInteger (^numberOfRowsOrColumnsInSection)(NSInteger section);
/** 不同section的分组间距,默认UIEdgeInsetsZero */
@property (nonatomic, copy) UIEdgeInsets (^insetInSection)(NSInteger section);
/** 不同section的行间距,默认0 */
@property (nonatomic, copy) CGFloat (^lineSpacingInSection)(NSInteger section);
/** 不同section的列间距,默认0 */
@property (nonatomic, copy) CGFloat (^interitemSpacingInSection)(NSInteger section);
/** 不同section的header大小,默认CGSizeZero */
@property (nonatomic, copy) CGSize (^headerSizeInSection)(NSInteger section);
/** 不同section的footer大小,默认CGSizeZero */
@property (nonatomic, copy) CGSize (^footerSizeInSection)(NSInteger section);
/** 不同section的header视图是否悬浮,默认NO */
@property (nonatomic, copy) BOOL (^headerPinToVisibleBoundsInSection)(NSInteger section);
/** cell高度 */
@property (nonatomic, copy) CGFloat (^heightForItemAtIndexPath)(NSIndexPath *indexPath);

@end

NS_ASSUME_NONNULL_END
