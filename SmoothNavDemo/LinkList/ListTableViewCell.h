//
//  ListTableViewCell.h
//  SmoothNavDemo
//
//  Created by xiaoguang on 2022/1/12.
//  Copyright © 2022 Cloudox. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface ListTableViewCell : UITableViewCell

@property (nonatomic, strong) UIImageView *foodImageView;
@property (nonatomic, strong) UILabel *foodNameLabel;
@property (nonatomic, strong) UILabel *foodPriceLabel;
@end

NS_ASSUME_NONNULL_END
