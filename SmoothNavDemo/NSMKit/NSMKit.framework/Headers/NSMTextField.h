//
//  NSMTextField.h
//  BSProject
//
//  Created by nsm on 2019/8/29.
//  Copyright © 2019 beisheng. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/*
 解决痛点:
 1.系统的setText:和setAttributedText:不会触发UIControlEventEditingChanged事件
 2.系统的UIControlEventEditingChanged在中文输入时候回调多次
 3.系统的font如果更新会同步placeholder的font
 4.避免采用kvc设置placeholder
 5.支持文本长度输入限制
 */
@interface NSMTextField : UITextField
/** 内容边距, 默认UIEdgeInsetsMake(0, 8, 0, 8) */
@property (nonatomic) UIEdgeInsets contentEdgeInsets;
/** 最大字数限制, 默认NSUIntegerMax */
@property (nonatomic) NSUInteger maximumLength;
/** placeholder颜色, 默认系统颜色, 置nil可恢复默认 */
@property(nullable, nonatomic, strong) UIColor *placeholderColor;
/** placeholder字体, 默认自身font, 置nil可恢复默认 */
@property(nullable, nonatomic, strong) UIFont *placeholderFont;
/// 是否允许数字0开头, 默认YES
@property (nonatomic) BOOL canStart0;
/**
 文字变化回调, 只有len <= maximumLength才会回调
 包含setText:和setAttributedText:
*/
@property (nonatomic, copy) void(^textDidChange)(NSMTextField *textField);
/**
 文字过长被拦截回调, 只有len > maximumLength才会回调
 包含setText:和setAttributedText:
 */
@property (nonatomic, copy) void(^textDidIntercept)(NSMTextField *textField);
@end

NS_ASSUME_NONNULL_END
