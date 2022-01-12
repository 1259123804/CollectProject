//
//  ListTableViewCell.m
//  SmoothNavDemo
//
//  Created by xiaoguang on 2022/1/12.
//  Copyright © 2022 Cloudox. All rights reserved.
//

#import "ListTableViewCell.h"

@implementation ListTableViewCell

- (void)awakeFromNib {
    [super awakeFromNib];
    // Initialization code
}

- (instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier{
    
    if (self = [super initWithStyle:style reuseIdentifier:reuseIdentifier]) {
        
        [self.contentView addSubview:self.foodImageView];
        [self.contentView addSubview:self.foodNameLabel];
        [self.contentView addSubview:self.foodPriceLabel];
        
        [self.foodImageView mas_makeConstraints:^(MASConstraintMaker *make) {
           
            make.left.equalTo(self.contentView).offset(15);
            make.centerY.equalTo(self.contentView);
            make.width.height.mas_equalTo(66);
        }];
        
        [self.foodNameLabel mas_makeConstraints:^(MASConstraintMaker *make) {
           
            make.left.equalTo(self.foodImageView.mas_right).offset(15);
            make.top.equalTo(self.foodImageView.mas_top);
        }];
        
        [self.foodPriceLabel mas_makeConstraints:^(MASConstraintMaker *make) {
           
            make.left.equalTo(self.foodImageView.mas_right).offset(15);
            make.bottom.equalTo(self.foodImageView.mas_bottom);
        }];
    }
    return self;
}

- (UIImageView *)foodImageView{
    
    if (!_foodImageView) {
        
        _foodImageView = [UIImageView new];
        _foodImageView.backgroundColor = [UIColor grayColor];
    }
    return _foodImageView;
}

- (UILabel *)foodNameLabel{
    
    if (!_foodNameLabel) {
     
        _foodNameLabel = [UILabel new];
    }
    return _foodNameLabel;
}

- (UILabel *)foodPriceLabel{
    
    if (!_foodPriceLabel) {
        
        _foodPriceLabel = [UILabel new];
    }
    return _foodPriceLabel;
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

@end
