

#import <UIKit/UIKit.h>

@interface UIView (Loading)
@property (nonatomic) BOOL isLoading;
/// 缩放 默认1.0
@property (nonatomic) CGFloat loadingIndicatorScale DEPRECATED_ATTRIBUTE;
/// 默认 UIActivityIndicatorViewStyleWhite
@property (nonatomic) UIActivityIndicatorViewStyle loadingIndicatorStyle;
@end
