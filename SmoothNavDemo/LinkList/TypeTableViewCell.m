//
//  TypeTableViewCell.m
//  SmoothNavDemo
//
//  Created by xiaoguang on 2022/1/12.
//  Copyright © 2022 Cloudox. All rights reserved.
//

#import "TypeTableViewCell.h"

@implementation TypeTableViewCell

- (void)awakeFromNib {
    [super awakeFromNib];
    // Initialization code
}

- (instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier{
    
    if (self = [super initWithStyle:style reuseIdentifier:reuseIdentifier]) {
        
        [self.contentView addSubview:self.typeLabel];
        [self.typeLabel mas_makeConstraints:^(MASConstraintMaker *make) {
           
            make.left.equalTo(self.contentView).offset(10);
            make.centerY.equalTo(self.contentView);
            make.right.equalTo(self.contentView).offset(-10);
        }];
    }
    return self;
}

- (UILabel *)typeLabel{
    
    if (!_typeLabel) {
        
        _typeLabel = [UILabel new];
        _typeLabel.numberOfLines = 0;
        _typeLabel.textColor = UIColorHex(333333);
    }
    return _typeLabel;
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];
   
    self.typeLabel.textColor = selected ? [UIColor yellowColor] : UIColorHex(333333);
    // Configure the view for the selected state
}

@end
