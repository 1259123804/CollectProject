

#import <UIKit/UIKit.h>

@interface NSMTextView : UITextView

@property (nonatomic, copy) NSString *placeholder;
@property (nonatomic, copy) UIColor *placeholderTextColor;
@property (nonatomic, copy) void (^textDidChanged)(NSMTextView *textView);

@end
