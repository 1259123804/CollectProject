

#import <NSMKit/NSMKit.h>
#import <MyLayout/MyLayout.h>

/** 模式,默认NSMAddPictureModeAll */
typedef NS_OPTIONS(NSInteger, NSMAddPictureMode) {
    NSMAddPictureModeLibrary    = 1 << 0,   // 相册
    NSMAddPictureModeCamara     = 1 << 1,   // 相机
    NSMAddPictureModeAll = (NSMAddPictureModeLibrary |
                            NSMAddPictureModeCamara), // 相册＋相机
};

/** 图片质量 */
typedef NS_ENUM(NSInteger, NSMPictureQualityMode) {
    NSMPictureQualityModeTS = 0,        // 抢先版(模糊)
    NSMPictureQualityModeSD = 1,        // 标清(流畅standard)
    NSMPictureQualityModeHD = 2,        // 高清(high)
    NSMPictureQualityModeBD = 3,        // 超清(蓝光best)
    NSMPictureQualityModePD = 4,        // 原画(pure)
};

@interface NSMPhotoImageView : NSMImageView
@property (nonatomic) BOOL isOrigin;
@end

@interface NSMPhotosView : MyFlowLayout

/** 有多少张photo视图 */
@property (nonatomic, copy) NSMutableArray <NSMPhotoImageView *> *photoViews;
/** !!默认图片,需要放在originPhotos之前赋值 */
@property (nonatomic, strong) UIImage *placeholderImage;
/** 添加按钮上的图片 */
@property (nonatomic, strong) UIImage *addImage;
@property (nonatomic, strong, readonly) NSMButton *addBtn;
/** 初始图片数组（URL/NSData/UIImage） */
@property (nonatomic, copy) NSArray <id<NSObject>> *originPhotos;
/** 图片来源类型 */
@property (nonatomic) NSMAddPictureMode addPictureMode;
/** 图片质量 */
@property (nonatomic) NSMPictureQualityMode pictureQualityMode;
/** 最多可添加图片个数,默认3张 */
@property (nonatomic) NSInteger maximumNumberOfPhotos;
/** YES:编辑模式, NO:预览模式, 默认NO */
@property (nonatomic) BOOL editEnabled;
/** 是否允许删除, 默认NO */
@property (nonatomic) BOOL deleteEnabled;
/** 是否允许排序, 默认NO */
@property (nonatomic) BOOL sortEnabled;
/** 高宽比,默认1正方形 */
@property (nonatomic) CGFloat aspectRatio;
/** 相册数据发生变化,(包含新增、删除、编辑) */
@property (nonatomic, copy) void(^photosDidChanged)(void);
/** 当删除某个图片 */
@property (nonatomic, copy) void(^didDeletePhoto)(NSMPhotoImageView *iv);

+ (instancetype)photoView;

@end
