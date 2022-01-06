//
//  NSObject+Delegates.h
//  BSProject
//
//  Created by nsm on 2019/7/9.
//  Copyright © 2019 beisheng. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSObject (Delegates)
/**
 启动多代理模式, 默认NO
 self.delegate = delegator1;
 self.delegate = delegator2;
 ...
 !!!当YES时候严禁出现 self.delegate = self; 这种写法,会死循环
 */
@property (nonatomic) BOOL delegatesEnabled;
/**
 默认已注册@selector(delegate),不用字符串做参数就是防止手贱打错
 @param sel     @selector(代理属性名)
 */
- (void)registerDelegateSelector:(SEL)sel;

/**
 移除单个代理
 移除全部 self.delegate = nil;
 */
- (void)removeDelegate:(id)delegate;
@end

NS_ASSUME_NONNULL_END
