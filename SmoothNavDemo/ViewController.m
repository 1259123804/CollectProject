//
//  ViewController.m
//  SmoothNavDemo
//
//  Created by Cloudox on 2017/3/15.
//  Copyright © 2017年 Cloudox. All rights reserved.
//

#import "ViewController.h"
#import "NextViewController.h"
#import "UINavigationController+Cloudox.h"
#import "UIViewController+Cloudox.h"
#import "XGPermanentThread.h"
#import <objc/runtime.h>
#import "UIButton+count.h"
#import "XGPerson.h"
static char *blockKey = "blockKey";

@interface ViewController ()

@property (nonatomic, assign) BOOL needRun;
@property (nonatomic, strong) XGPermanentThread *tmpThread;
@property (nonatomic, strong) NSMutableArray *stateArr;
@property (nonatomic, assign) NSInteger totalTask;
@property (nonatomic, strong) NSMutableArray *testArr;
@end

@implementation ViewController

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary<NSKeyValueChangeKey,id> *)change context:(void *)context{
    
    NSArray *newArr = change[NSKeyValueChangeNewKey];
    NSLog(@"%@", newArr);
    
}
- (void)viewDidLoad {
    [super viewDidLoad];

    XGPerson *p = [[XGPerson alloc] init];
    [p singSong:@"123"];
    [XGPerson haveMeal:@"456"];
    [self addObserver:self forKeyPath:@"testArr" options:NSKeyValueObservingOptionNew context:nil];
    
    self.testArr = [NSMutableArray arrayWithObject:@"123"];
    
    self.title = @"First View";
//    self.view.backgroundColor = [UIColor whiteColor];
    self.view.backgroundColor = [UIColor colorWithRed:0x32/255.0f green:0xAB/255.0f blue:0x64/255.0f alpha:1.0f];
//    self.navigationController.delegate = self.navigationController;
    
    UIButton *btn = [[UIButton alloc] initWithFrame:CGRectMake(100, 100, 200, 50)];
    [btn setTitle:@"Next View" forState:UIControlStateNormal];
    [btn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
   // [btn sendAction:@selector(toNextView) to:self forEvent:UIControlEventTouchUpInside];
    [btn addTarget:self action:@selector(toNextView) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:btn];
    
    self.navigationController.cloudox = @"hey，this is category!";
    NSLog(@"%@", self.navigationController.cloudox);
    
    [self getSub:self.navigationController.navigationBar andLevel:1];
   
    self.stateArr = [@[@(0), @(0), @(0)] mutableCopy];
    self.totalTask = 15;
    self.tmpThread = [[XGPermanentThread alloc] init];
    
    unsigned int count;
    objc_property_t *propertyList = class_copyPropertyList([self class], &count);
    for (unsigned int i = 0; i < count; i++) {
        
        const char *proName = property_getName(propertyList[i]);
        NSLog(@"property ---> %@", [NSString stringWithUTF8String:proName]);
    }
    
    Method *methodList = class_copyMethodList(self.class, &count);
    for (unsigned int i = 0; i < count; i++) {
        
        Method method = methodList[i];
        NSLog(@"method ---> %@", NSStringFromSelector(method_getName(method)));
    }
    
    Ivar *ivarList = class_copyIvarList(self.class, &count);
    for (unsigned int i = 0; i < count; i++) {
        
        Ivar aIvar = ivarList[i];
        const char *varName = ivar_getName(aIvar);
        NSLog(@"ivar ---> %@", [NSString stringWithUTF8String:varName]);
    }
    
    //动态添加方法
    //addNewSelector 是c语言的方法，必须有两个指定的参数id self，SEL _cmd
    Method addMethod = class_getInstanceMethod(self.class, @selector(newAddSelector));
    class_addMethod(self.class, @selector(addSelector), method_getImplementation(addMethod), method_getTypeEncoding(addMethod));

    if ([self respondsToSelector:@selector(addSelector)]) {
        
        [self performSelector:@selector(addSelector)];
    }else{
        
        NSLog(@"没有这个方法");
    }
    
    //动态添加属性
    static char *newName = "newName";
    unsigned int attCount = 1;
    objc_property_attribute_t attribute;
    attribute.name = "newName";
    class_addProperty(self.class, newName, &attribute, attCount);
    
    objc_property_t *newProList = class_copyPropertyList(self.class, &count);
    for (unsigned int i = 0; i < count; i++) {
        
        objc_property_t newPro = newProList[i];
        NSLog(@"newPro --->%@", [NSString stringWithUTF8String:property_getName(newPro)]);
    }
}

- (void)newAddSelector{
    
    NSLog(@"动态添加的方法2");
}

void addNewSelector (id self, SEL _cmd){
    
    NSLog(@"动态添加的方法1");
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    self.navBarBgAlpha = @"1.0";
}

// 获取子视图
- (void)getSub:(UIView *)view andLevel:(int)level {
    NSArray *subviews = [view subviews];
    if ([subviews count] == 0) return;
    for (UIView *subview in subviews) {
        
        NSString *blank = @"";
        for (int i = 1; i < level; i++) {
            blank = [NSString stringWithFormat:@"  %@", blank];
        }
        NSLog(@"%@%d: %@", blank, level, subview.class);
        [self getSub:subview andLevel:(level+1)];
        
    }
}

// 按钮响应

- (void)toNextView {
    
    void(^block)(void) = ^{
      
        NSLog(@"Click");
    };
    
    [[self mutableArrayValueForKey:@"testArr"] replaceObjectAtIndex:0 withObject:@"456"];
    return;
    objc_setAssociatedObject(self, blockKey, block, OBJC_ASSOCIATION_COPY);
    NextViewController *nextVC = [[NextViewController alloc] init];
    [self.navigationController pushViewController:nextVC animated:YES];
    return;
    
    NSLock *lock = [NSLock new];
    [self.tmpThread handleTask:^{
       
        dispatch_async(dispatch_get_global_queue(0, 0), ^{
            @synchronized (self) {
                
                for (int i = 0; i< 5; i++) {
                    
                    [self excuteTask];
                }
            }
        });
    }];
    [self.tmpThread handleTask:^{
       
        dispatch_async(dispatch_get_global_queue(0, 0), ^{
            
            @synchronized (self) {
            
                for (int i = 0; i< 5; i++) {
                    
                    [self excuteTask];
                }
            }
        });
    }];
    [self.tmpThread handleTask:^{
       
        dispatch_async(dispatch_get_global_queue(0, 0), ^{
            
            @synchronized (self) {
                for (int i = 0; i< 5; i++) {
                    
                    [self excuteTask];
                }
            }
        });
    }];
    return;
}

- (void)excuteTask{
    
    sleep(0.1);
    self.totalTask --;
    NSLog(@"还剩%ld个任务 - %@", self.totalTask, [NSThread currentThread]);
    
}

- (void)stopThread{
    
    CFRunLoopStop(CFRunLoopGetCurrent());
    NSThread *thread = [NSThread currentThread];
    [thread cancel];
}

- (void)runThread{
    
    NSLog(@"current thread is = %@", [NSThread currentThread]);
    NSRunLoop *loop = [NSRunLoop currentRunLoop];
    [loop addPort:[NSMachPort port] forMode:NSDefaultRunLoopMode];
    
    _needRun = YES;
    
    while (_needRun && [loop runMode:NSDefaultRunLoopMode beforeDate:[NSDate distantFuture]]) {
        
        NSLog(@"I will be stay in here.");
    }
    
    NSLog(@"-----");
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
