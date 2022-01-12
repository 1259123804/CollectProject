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
    NSLog(@"----%@", p.name);
    
    [p setValue:@"1111111" forKey:@"name"];
    
    /*runtime应用：
     1.动态方法交换，包括交换两个方法的实现，和拦截并替换系统方法
     2.类目添加新属性
     3.获取类详细的属性，包括属性列表，成员变量列表，方法列表，协议列表
     4.解决同一方法高频率调用的效率问题
     5.动态方法解析和消息转发，包括动态添加方法，解决方法无响应崩溃的问题
     6.动态操作属性，包括修改私有属性，改进iOS归档与解档，实现字典与模型的转换
     */
    
    //实现方法动态交换Method Swizzling原理是通过RunTime获取到方法实现的地址，进而动态的交换两个方法的功能。
    
    //类目catory为已知的类拓展功能，虽然继承也能为类增加方法，而且比类目更加具有增加属性的优势，但继承是一个重量级的操作，添加不必要的继承关系无疑增加了代码的复杂度。类目不支持直接添加属性，如果在分类的声明中写入property属性，只能为其生成set和get方法声明，但不能生成成员变量。直接调用这些属性会崩溃
    
    //给分类添加属性需要借助runtime的关联对象Associated Objects特性，能帮我们正在运行阶段将任意的属性关联到一个对象上
    
    //oc调用方法，编译后就走objc_msgSend的逻辑，最终是为了找到该方法对应的函数指针（IMP），再调用函数指针，找到IMP后保存起来，下次执行可以直接调用IMP。不需要走消息查找逻辑了，效率就可以提高了。
    
    //互斥锁：如果共享的数据已经有其他的线程加锁了，线程会进入休眠状态，等待被访问的资源解锁，当资源解锁时，线程就会被唤醒
    //自旋锁：如果共享的数据已经有其他的线程加锁了，线程会以死循环的的方式等待，当资源解锁时，线程会立即执行
    
    //自旋锁性能高于互斥锁，自旋锁虽然会一直自旋等待，但不会一直占用CPU，超过了操作系统分配的时间片会被强制挂起，自旋锁如果不能保证所有线程都是同一优先级，则可能造成死锁
    
    
    
    unsigned int count = 0;
    Ivar *varList = class_copyIvarList(p.class, &count);
    for (unsigned int i = 0; i < count; i++) {
        
        NSString *varName = [NSString stringWithUTF8String: ivar_getName(varList[i])];
        NSLog(@"++++%@", varName);
        if ([varName isEqualToString:@"_name"]) {
            NSLog(@"ivar ---> %@", object_getIvar(p, varList[i]));
            object_setIvar(p, varList[i], @"ys");
            NSLog(@"ivar ---> %@", object_getIvar(p, varList[i]));
        }
    }
    
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
        NSString *varName1 = [NSString stringWithUTF8String:varName];
        NSLog(@"ivar ---> %@", varName1);
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
