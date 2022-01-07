//
//  XGPerson.m
//  SmoothNavDemo
//
//  Created by xiaoguang on 2022/1/7.
//  Copyright © 2022 Cloudox. All rights reserved.
//

#import "XGPerson.h"
@implementation XGPerson

//添加类方法
+ (BOOL)resolveClassMethod:(SEL)sel{
    
    if (sel == @selector(haveMeal:)) {
        
        Method newMethod = class_getClassMethod(object_getClass(self), @selector(newMealMethod:));
        class_addMethod(object_getClass(self), sel, class_getMethodImplementation(object_getClass(self), @selector(newMealMethod:)), method_getTypeEncoding(newMethod));
        return YES;
    }
    return [class_getSuperclass(self) resolveClassMethod:sel];
}

//添加实例方法
+ (BOOL)resolveInstanceMethod:(SEL)sel{
    
    if (sel == @selector(singSong:)) {
        
        class_addMethod(self.class, sel, class_getMethodImplementation(self.class, @selector(newSingMethod:)), method_getTypeEncoding(class_getInstanceMethod(self.class, @selector(newSingMethod:))));
        return YES;
    }
    return [super resolveInstanceMethod:sel];
}

+ (void)newMealMethod:(NSString *)food{
    
    NSLog(@"%s", __func__);
}

- (void)newSingMethod:(NSString *)song{
    
    NSLog(@"%s", __func__);
}
@end
