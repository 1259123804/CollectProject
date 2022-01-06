//
//  UIButton+count.m
//  SmoothNavDemo
//
//  Created by xiaoguang on 2022/1/6.
//  Copyright © 2022 Cloudox. All rights reserved.
//

#import "UIButton+count.h"
#import <objc/runtime.h>
@implementation UIButton (count)

+ (void)load{
    
    [super load];
    unsigned int count = 0;
    static char *type;
    Method *methodList = class_copyMethodList(self.class, &count);
    for (unsigned int i = 0; i < count; i++) {
        
        Method method = methodList[i];
    }
    
    Method targetMethod = class_getInstanceMethod(self.class, @selector(sendAction:to:forEvent:));
    
    Method newMethod = class_getInstanceMethod(self.class, @selector(newSendAction:to:forEvent:));
    
    BOOL isIncrease = class_addMethod(self.class, @selector(sendAction:to:forEvent:), method_getImplementation(newMethod), method_getTypeEncoding(newMethod));
    
    if (isIncrease) {
        
        class_replaceMethod(self.class, @selector(newSendAction:to:forEvent:), method_getImplementation(targetMethod), method_getTypeEncoding(targetMethod));
    }else{
        
        method_exchangeImplementations(targetMethod, newMethod);
    }
}

- (void)newSendAction:(SEL)action to:(id)target forEvent:(UIEvent *)event{
    
    NSLog(@"New click");
    [self newSendAction:action to:target forEvent:event];
}
@end
