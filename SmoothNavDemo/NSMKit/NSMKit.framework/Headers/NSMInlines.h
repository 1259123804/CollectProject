

#import <UIKit/UIKit.h>

#ifndef NSMInlines_h
#define NSMInlines_h

#pragma mark - UIColor
static inline UIColor *RGBAColor(CGFloat r, CGFloat g, CGFloat b, CGFloat a) {
    return [UIColor colorWithRed:r/255.0f green:g/255.0f blue:b/255.0f alpha:a/1.0f];
}

static inline UIColor *RGBColor(CGFloat r, CGFloat g, CGFloat b) {
    return RGBAColor(r, g, b, 1);
}

static inline UIColor *WhiteColor(CGFloat w, CGFloat a) {
    return [UIColor colorWithWhite:w/1.0f alpha:a/1.0f];
}

static inline UIColor *RandomAColor(CGFloat a) {
    return RGBAColor(arc4random()%255, arc4random()%255, arc4random()%255, a);
}

static inline UIColor *RandomColor() {
    return RandomAColor(1);
}

#pragma mark - SafeObject
static inline BOOL SafeObject(id obj) {
    return obj && ![obj isEqual:NSNull.null];
}

static inline NSString *SafeString(id obj) {
    if (SafeObject(obj)) {
        if ([obj isKindOfClass:NSString.class]) {
            return obj;
        } else if ([obj isKindOfClass:NSNumber.class]) {
            return ((NSNumber *)obj).stringValue;
        }
    }
    return @"";
}

static inline NSArray *SafeArray(id obj) {
    BOOL isValid = SafeObject(obj) && [obj isKindOfClass:NSArray.class];
    return isValid? (NSArray *)obj: @[];
}

static inline NSDictionary *SafeDictionary(id obj) {
    BOOL isValid = SafeObject(obj) && [obj isKindOfClass:NSDictionary.class];
    return isValid? (NSDictionary *)obj: @{};
}

static inline NSArray *SafeArrayForKey(id obj, id key) {
    return SafeArray([SafeDictionary(obj) objectForKey:key]);
}

static inline NSDictionary *SafeDictionaryForKey(id obj, id key) {
    return SafeDictionary([SafeDictionary(obj) objectForKey:key]);
}

#pragma mark - NSString
static inline NSString *IntegerString(NSInteger v) {
    return [NSString stringWithFormat:@"%@", @(v)];
}

static inline NSString *ReplaceString(id obj, NSString *str) {
    NSString *str1 = SafeString(obj);
    NSString *str2 = SafeString(str);
    return str1.length? str1: str2;
}

#pragma mark - UIImage
static inline UIImage *NameImage(NSString *name) {
    return [UIImage imageNamed:name];
}

static inline UIImage *FileImage(NSString *name, NSString *type) {
    return [UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:name ofType:type]];
}

static inline UIImage *OriginalImage(NSString *name) {
    return [NameImage(name) imageWithRenderingMode:UIImageRenderingModeAlwaysOriginal];
}

static inline UIImage *TemplateImage(NSString *name) {
    return [NameImage(name) imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
}

static inline UIFont *CustomFont(CGFloat fontSize) {
    return [UIFont fontWithName:@"STHeitiSC-Light" size:fontSize];
}

static inline UIFont *NumericFontBlack(CGFloat fontSize) {
    return [UIFont fontWithName:@"HelveticaNeue-CondensedBlack" size:fontSize];
}

static inline UIFont *NumericFontBold(CGFloat fontSize) {
    return [UIFont fontWithName:@"HelveticaNeue-CondensedBold" size:fontSize];
}

static inline UIFont *PhoneFontBlack(CGFloat fontSize) {
    return [UIFont fontWithName:@"Optima-ExtraBlack" size:fontSize];
}

static inline UIFont *PhoneFontBold(CGFloat fontSize) {
    return [UIFont fontWithName:@"Optima-Bold" size:fontSize];
}

static inline UIFont *SystemFont(CGFloat fontSize) {
    return [UIFont systemFontOfSize:fontSize];
}

static inline UIFont *BoldSystemFont(CGFloat fontSize) {
    return [UIFont boldSystemFontOfSize:fontSize];
}

#pragma mark - CG
static inline BOOL CGSizeIsEmpty(CGSize size) {
    CGRect rect = CGRectMake(0, 0, size.width, size.height);
    return CGRectIsEmpty(rect);
}

static inline CGPoint CGSizeCenter(CGSize size) {
    return CGPointMake(size.width/2, size.height/2);
}

static inline CGPoint CGSizeGetCenterPoint(CGSize size) {
    return CGPointMake(size.width/2, size.height/2);
}

static inline CGFloat CGFloatGetMid(CGFloat f1, CGFloat f2) {
    return (f1 - f2) / 2.0;
}

static inline CGFloat UIEdgeInsetsGetWidth(UIEdgeInsets insets) {
    return insets.left + insets.right;
}

static inline CGFloat UIEdgeInsetsGetHeight(UIEdgeInsets insets) {
    return insets.top + insets.bottom;
}

static inline CGRect CGRectIntersectsEdgeInsets(CGRect rect, UIEdgeInsets insets) {
    rect.origin.x += insets.left;
    rect.origin.y += insets.top;
    rect.size.width -= UIEdgeInsetsGetWidth(insets);
    rect.size.height -= UIEdgeInsetsGetHeight(insets);
    return rect;
}

#pragma mark - bar
static inline CGFloat StatusBarHeight() {
    return UIApplication.sharedApplication.statusBarFrame.size.height;
}

static inline CGFloat NavBarHeight() {
    return  44.0 + StatusBarHeight();
}

static inline CGFloat TabBarHeight() {
    return  StatusBarHeight()>20? 83: 49;
}

#pragma mark - bundle
static inline NSDictionary *MainBundleDictionary() {
    return SafeDictionary(NSBundle.mainBundle.infoDictionary);
}

static inline NSString *AppDisplayName() {
    return MainBundleDictionary()[@"CFBundleDisplayName"];
}

static inline NSString *AppBundleName() {
    return MainBundleDictionary()[@"CFBundleName"];
}

static inline NSString *AppBundleID() {
    return MainBundleDictionary()[@"CFBundleIdentifier"];
}
static inline NSString *AppBuild() {
    return MainBundleDictionary()[@"CFBundleVersion"];
}

static inline NSString *AppVersion() {
    return MainBundleDictionary()[@"CFBundleShortVersionString"];
}

static inline NSString *AppIconName() {
    return [[MainBundleDictionary() valueForKeyPath:@"CFBundleIcons.CFBundlePrimaryIcon.CFBundleIconFiles"] lastObject];
}

static inline UIImage *AppIcon() {
    return [UIImage imageNamed:AppIconName()];
}

static inline id InfoPlistValueForKey(NSString *key) {
    return MainBundleDictionary()[SafeString(key)];
}

static inline NSMutableAttributedString *AttributedString(NSString *preStr,
                                                          UIFont *preFont,
                                                          UIColor *preColor,
                                                          NSString *sufStr,
                                                          UIFont *sufFont,
                                                          UIColor *sufColor,
                                                          NSTextAlignment alignment,
                                                          CGFloat lineSpacing) {
    NSString *prefix = SafeString(preStr);
    NSString *suffix = SafeString(sufStr);
    NSString *str = [NSString stringWithFormat:@"%@%@", prefix, suffix];
    NSMutableAttributedString *attrM = [[NSMutableAttributedString alloc] initWithString:str];
    NSMutableParagraphStyle *paragraph = [NSMutableParagraphStyle new];
    paragraph.lineSpacing = lineSpacing;
    paragraph.alignment = alignment;
    [attrM addAttribute:NSParagraphStyleAttributeName
                  value:paragraph
                  range:NSMakeRange(0, str.length)];
    [attrM addAttributes:@{NSFontAttributeName: preFont,
                           NSForegroundColorAttributeName: preColor}
                   range:NSMakeRange(0, prefix.length)];
    [attrM addAttributes:@{NSFontAttributeName: sufFont,
                           NSForegroundColorAttributeName: sufColor}
                   range:NSMakeRange(prefix.length, suffix.length)];
    return attrM;
}

static inline NSMutableAttributedString *AttributedStringFL(NSString *str,
                                                            UIFont *font,
                                                            UIColor *color) {
    NSMutableAttributedString *attrM = [[NSMutableAttributedString alloc] initWithString:SafeString(str)];
    NSMutableParagraphStyle *paragraph = [NSMutableParagraphStyle new];
    paragraph.lineSpacing = 0;
    paragraph.alignment = NSTextAlignmentLeft;
    [attrM addAttributes:@{NSParagraphStyleAttributeName: paragraph,
                           NSFontAttributeName: font,
                           NSForegroundColorAttributeName: color}
                   range:NSMakeRange(0, str.length)] ;
    return attrM;
}

static inline NSMutableAttributedString *AttributedStringFR(NSString *str,
                                                            UIFont *font,
                                                            UIColor *color) {
    NSMutableAttributedString *attrM = [[NSMutableAttributedString alloc] initWithString:SafeString(str)];
    NSMutableParagraphStyle *paragraph = [NSMutableParagraphStyle new];
    paragraph.lineSpacing = 0;
    paragraph.alignment = NSTextAlignmentRight;
    [attrM addAttributes:@{NSParagraphStyleAttributeName: paragraph,
                           NSFontAttributeName: font,
                           NSForegroundColorAttributeName: color}
                   range:NSMakeRange(0, str.length)] ;
    return attrM;
}


static inline NSMutableAttributedString *AttributedStringFC(NSString *str,
                                                            UIFont *font,
                                                            UIColor *color) {
    NSMutableAttributedString *attrM = [[NSMutableAttributedString alloc] initWithString:SafeString(str)];
    NSMutableParagraphStyle *paragraph = [NSMutableParagraphStyle new];
    paragraph.lineSpacing = 0;
    paragraph.alignment = NSTextAlignmentCenter;
    [attrM addAttributes:@{NSParagraphStyleAttributeName: paragraph,
                           NSFontAttributeName: font,
                           NSForegroundColorAttributeName: color}
                   range:NSMakeRange(0, str.length)] ;
    return attrM;
}

static inline UIImage *NilImage() {
    static UIImage *image;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        image = [[UIImage alloc] init];
    });
    return image;
}

static inline UIImage *BundleImage(NSString *name) {
    NSString *fileName = [NSString stringWithFormat:@"NSMBundle.bundle/%@", name];
    return NameImage(fileName);
}

static inline UIImage *BundleTemplateImage(NSString *name) {
    return [BundleImage(name) imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
}

static inline UIImageView *ArrowImageView(UIColor *tintColor, CGFloat scale) {
    CGRect frame = CGRectMake(0, 0, 8*scale, 14*scale);
    UIImageView *imageView = [[UIImageView alloc] initWithFrame:frame];
    imageView.contentMode = UIViewContentModeScaleAspectFit;
    if (tintColor) {
        imageView.tintColor = tintColor;
        imageView.image = BundleTemplateImage(@"nsm_cell_indicator");
    } else {
        imageView.image = BundleImage(@"nsm_cell_indicator");
    }
    return imageView;
}

#pragma mark - UIView
static inline void ViewBorder(UIView *view,
                              CGFloat borderWidth,
                              UIColor *borderColor) {
    view.layer.borderWidth = borderWidth;
    view.layer.borderColor = borderColor.CGColor;
}

static inline void ViewCorner(UIView *view,
                              CGFloat cornerRadius) {
    view.layer.masksToBounds = YES;
    view.layer.cornerRadius = cornerRadius;
}

#endif /* NSMInlines_h */
