//
//  NSMSearchAssociateController.h
//  NSMKit
//
//  Created by nsm on 2019/5/30.
//  Copyright © 2019 nani. All rights reserved.
//

#import "NSMTableViewController.h"

NS_ASSUME_NONNULL_BEGIN

CF_EXTERN_C_BEGIN
/**
 根据words匹配text
 @param text    待匹配的字符串
 eg:e路狂飙
 @param words   高亮的字符串数组
 eg:
 [{
 "text": "e路",
 "color": "#3882FF"
 }]
 */
NSMutableAttributedString *AttributedText(NSString *text, NSArray *words);
CF_EXTERN_C_END

@protocol NSMSearchAssociateProtocol;
@interface NSMSearchAssociateController : NSMTableViewController <NSMSearchAssociateProtocol>

@end

NS_ASSUME_NONNULL_END
