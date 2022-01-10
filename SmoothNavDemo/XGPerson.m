//
//  XGPerson.m
//  SmoothNavDemo
//
//  Created by xiaoguang on 2022/1/7.
//  Copyright © 2022 Cloudox. All rights reserved.
//

#import "XGPerson.h"
#import "XGSonPerson.h"

@interface XGPerson ()

@property (nonatomic, strong) XGSonPerson *son;
@end
@implementation XGPerson

//添加类方法
+ (BOOL)resolveClassMethod:(SEL)sel{
    
    if (sel == @selector(haveMeal:)) {
        
        //获取实现的类方法
        Method newMethod = class_getClassMethod(object_getClass(self), @selector(newMealMethod:));
        //添加方法
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

- (void)sayHao{
    
    NSLog(@"Son -- %s", __func__);
}

- (void)sonStudy{
    
    NSLog(@"Son -- %s", __func__);
}

- (void)newSingMethod:(NSString *)song{
    
    NSLog(@"%s", __func__);
    self.son = [XGSonPerson new];
    Method m1 = class_getInstanceMethod(self.son.class, @selector(sayHello));
    Method m2 = class_getInstanceMethod(self.son.class, @selector(sayHi));
    method_exchangeImplementations(m1, m2);
    [self.son sayHi];
    [self.son sayHello];
    
    //替换方法
    class_replaceMethod(self.son.class, @selector(sayHi), class_getMethodImplementation(self.class, @selector(sayHao)), method_getTypeEncoding(class_getInstanceMethod(self.class, @selector(sayHao))));
    [self.son sayHi];
    
    //添加方法
    class_addMethod(self.son.class, @selector(study), class_getMethodImplementation(self.class, @selector(sonStudy)), method_getTypeEncoding(class_getInstanceMethod(self.class, @selector(sonStudy))));
    
    [self.son performSelector:@selector(study)];
    
    //添加属性
    
    //获取属性列表
    unsigned int count = 0;
    objc_property_t *proList = class_copyPropertyList(self.class, &count);
    for (unsigned int i = 0; i < count; i++) {
        
        NSLog(@"Property(%d): %@", i, [NSString stringWithUTF8String:property_getName(proList[i])]);
    }
    
    //获取方法列表
    Method *methodList = class_copyMethodList(self.class, &count);
    for (unsigned int i = 0; i < count; i++) {
        
        NSLog(@"Method(%d): %@", i, NSStringFromSelector(method_getName(methodList[i])));
    }
    
    //获取成员变量列表
    Ivar *varList = class_copyIvarList(self.class, &count);
    for (unsigned int i = 0; i < count; i++) {
        
        NSLog(@"Ivar(%d): %@", i, [NSString stringWithUTF8String:ivar_getName(varList[i])]);
    }
    
    [self performSelector:@selector(sayHello) withObject:nil];
    [XGPerson performSelector:@selector(run) withObject:nil];
}

- (id)forwardingTargetForSelector:(SEL)aSelector{
    
    if (aSelector == @selector(sayHello)) {
        
        return self.son;
    }
    return [super forwardingTargetForSelector:aSelector];
}

+ (id)forwardingTargetForSelector:(SEL)aSelector{
    
    if (aSelector == @selector(run)) {
        
        return [XGSonPerson class];
    }
    return [super forwardingTargetForSelector:aSelector];
}
@end
