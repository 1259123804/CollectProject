

#import <UIKit/UIKit.h>

@interface NSMPhotoBrowser : UIViewController

/**
 启动图片浏览器
 
 @param photos 将要显示的图片信息集合(NSDictionary素)
 例如: 
 {
    photo: (网络URL 或 ImageView.image 或 本地Image 或 imageData),
    title: @"主标题",
    subtitle: @"副标题(一般表示图片详情介绍)"
 }
 @param thumbs 缩略图集合 (ImageView.image 或 本地Image)
 @param index  当前浏览的图片所处下标索引
 */
+ (instancetype)showPhotos:(NSArray *)photos
                    thumbs:(NSArray *)thumbs
                   atIndex:(NSInteger)index;
@end
