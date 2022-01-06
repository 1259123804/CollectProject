

#import <Foundation/Foundation.h>
#import <objc/message.h>

NS_ASSUME_NONNULL_BEGIN

typedef id OverrideIMPBlock;
typedef IMP _Nonnull (^OriginalIMPBlock)(void);
typedef OverrideIMPBlock _Nonnull (^IMPHandler)(OriginalIMPBlock oriImpBlock);

CF_EXTERN_C_BEGIN

/**
 是否重写了某个类的实例方法
 1.如果方法不存在,返回NO
 2.如果方法存在但是父类中不存在,返回YES
 */
BOOL HasOverrideInstanceMethod(Class cls, SEL sel);

/**
 重写某个类实例方法,如果用runtime方法交换容易出现问题
 !!重点:
 内部会调用imp_implementationWithBlock(id block)函数来实现方法重写
 handler的返回值OverrideIMPBlock将作为block参数,所以其返回值和参数必须与sel保持一致
 sel的返回值类型(^)(Class实例, sel的参数1, sel的参数2, ...),sel没有参数不传
 例如:
 static dispatch_once_t onceToken;
 dispatch_once(&onceToken, ^{
    SEL sel = @selector(viewWillAppear:);
    OverrideInstanceMethod(UIViewController.class, sel, ^OverrideIMPBlock(OriginalIMPBlock oriImpBlock) {
        return ^(UIViewController *objc, BOOL animated){
            // 代码块...
            // 调用父类 [super xxx]; 调用父类方法可前可后,不写就是不调用
            void(*oriImp)(id, SEL, BOOL);
            oriImp = (void(*)(id, SEL, BOOL))oriImpBlock();
            oriImp(objc, sel, animated);
        };
    });
 });
 */
void OverrideInstanceMethod(Class cls, SEL sel, IMPHandler handler);

/**
 重写某个类实例方法，返回值为void，无参数
 内部会先调用[super xxx]，再调用implementationBlock(self)
 */
void OverrideInstanceMethod_Void_0(Class cls, SEL sel, void(^implementationBlock)(__kindof NSObject *objc));

/// 交换class中实例方法
/// @param cls      被替换的Class
/// @param sel      被替换的SEL
/// @param newSel   替换的SEL
BOOL ExchangeImplementations(Class cls, SEL sel, SEL newSel);

CF_EXTERN_C_END

@interface NSMRuntime : NSObject
@end

NS_ASSUME_NONNULL_END
