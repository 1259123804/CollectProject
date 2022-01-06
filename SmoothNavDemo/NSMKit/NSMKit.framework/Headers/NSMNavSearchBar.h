//
//  NSMNavSearchBar.h
//  iShow
//
//  Created by nsm on 2018/7/26.
//  Copyright © 2018年 nani. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface NSMNavSearchBar : UISearchBar
/// 默认-1,代表圆
@property (nonatomic) CGFloat searchFieldCornerRadius;
@property (nonatomic) UIEdgeInsets contentInset;
@property (nonatomic, strong, readonly) UITextField *textField;

- (void)setShowsCancelButton:(BOOL)showsCancelButton NS_UNAVAILABLE;

@end
