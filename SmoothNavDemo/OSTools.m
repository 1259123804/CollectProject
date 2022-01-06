//
//  OSTools.m
//  OverseaProject
//
//  Created by xiaoguang on 2021/12/27.
//

#import "OSTools.h"

@implementation ProductModel

- (instancetype)initWithCoder:(NSCoder *)aDecoder {
    self = [super init];
    return [self modelInitWithCoder:aDecoder];
}

- (void)encodeWithCoder:(NSCoder *)aCoder {
    return [self modelEncodeWithCoder:aCoder];
}
@end

@interface OSTools ()<UIImagePickerControllerDelegate, UINavigationControllerDelegate, ZYQAssetPickerControllerDelegate>
@end
@implementation OSTools

+ (instancetype)sharedTools{
    
    static OSTools *tools = NULL;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
       
        tools = [[OSTools alloc] init];
    });
    return tools;
}

- (void)setStatusBarBackgroundColor:(UIColor *)color{
    
    if (@available(iOS 13.0, *)) {
        
    } else {
        UIView *statusBar = [[[UIApplication sharedApplication] valueForKey:@"statusBarWindow"] valueForKey:@"statusBar"];
        if ([statusBar respondsToSelector:@selector(setBackgroundColor:)]) {
            
            statusBar.backgroundColor = color;
        }
    }
}
#pragma mark - 获取所有商品
- (void)getAllProductSuccess:(void(^)(void))success failure:(void(^)(void))failure{
    
    [_networker GET:@"" parameters:nil success:^(NSMResponseObject *responseObject) {
            
        self.diamondProductArr = [NSMutableArray array];
        for (NSDictionary *data in responseObject.data) {
            
            if (IsEqual(@"diamond", data[@"type"])) {
                
                [self.diamondProductArr addObject:data];
                
            }else if (IsEqual(@"vip", data[@"type"])){
                
                self.vipProductModel = [ProductModel new];
                [self.vipProductModel setValuesForKeysWithDictionary:data];
            }
        }
        !success?:success();
        } empty:nil failure:^(NSError *error) {
        
            !failure?:failure();
    }];
}


- (void)aliPayProductWithProductId:(NSString *)productId orderSn:(NSString *)orderSn success:(void(^)(NSMResponseObject *responseObject))success failure:(void(^)(void))failure{
    
    

}

#pragma mark - 生成订单
- (void)createPayOrderWithChargeId:(NSInteger)chargeId productId:(NSString *)productId success:(void(^)(NSMResponseObject *responseObject))success failure:(void(^)(void))failure{
    
    NSDictionary *params = nil;
    
    if (self.isVideoing){
        
         params = @{@"rechargeConfigId": @(chargeId), @"payType": @"apple", @"oppositeId": @(self.oppositeId.integerValue), @"isVideoing": self.isVideoing};
    }else{
        
        params = @{@"rechargeConfigId": @(chargeId), @"payType": @"apple"};
    }

    [_networker POST:@"" parameters:nil success:^(NSMResponseObject *responseObject) {
        NSString *orderSn = SafeString(responseObject.data[@"orderSn"]);
        if (orderSn.length == 0) {
            return;
        }
        [self buyProductWithProductId:productId orderSn:orderSn success:success failure:failure];
        
    } empty:nil failure:^(NSError *error) {

        NSLog(@"生成订单失败");
    }];
}

#pragma mark - 开始支付
- (void)buyProductWithProductId:(NSString *)productId orderSn:(NSString *)orderSn success:(void(^)(NSMResponseObject *responseObject))success failure:(void(^)(void))failure{
    
    if (![SKPaymentQueue canMakePayments]){
        
       NSLog(@"不允许程序内付费");
        return;
    }
    IAPShare *IAP = IAPShare.sharedHelper;
    [IAP.iap clearSavedPurchasedProducts];
    NSSet *dataSet = [[NSSet alloc] initWithObjects:productId, nil];
    IAP.iap = [[IAPHelper alloc] initWithProductIdentifiers:dataSet];
    [IAP.iap requestProductsWithCompletion:^(SKProductsRequest *request, SKProductsResponse *response) {
      
        if (IAP.iap.products.count == 0 || orderSn == nil) {
        NSLog(@"购买失败");
            return;
        }
        
        SKProduct *product = IAP.iap.products.firstObject;
        if (!product) {
            NSLog(@"购买失败");
            return;
        }
        
        [IAP.iap buyProduct:product onCompletion:^(SKPaymentTransaction *trans) {
            if (trans.error) {
                NSLog(trans.error.localizedDescription);
                return;
            }
            
            switch (trans.transactionState) {
                case SKPaymentTransactionStatePurchased: {
                    // 购买成功，向服务器验证
                    NSData *payToken = [NSData dataWithContentsOfURL:[[NSBundle mainBundle] appStoreReceiptURL]];
                    NSString *receiptString = [payToken base64EncodedStringWithOptions:0];
                    if (!receiptString) {
                        NSLog(@"购买失败");
                        return;
                    }
//                    NSDictionary *requestContents = @{@"receipt-data": [payToken base64EncodedStringWithOptions:0]};
//                    NSError *error;
//                    NSData *requestData = [NSJSONSerialization dataWithJSONObject:requestContents options:0 error:&error];
//                    if (!requestData) {
//                        // 交易凭证为空验证失败
//                        ShowToast(@"购买失败");
//                        return;
//                    }
                    NSMutableDictionary *params = @{}.mutableCopy;
                    params[@"payload"] = receiptString;
                    params[@"orderSn"] = orderSn;
                    [_networker POST:@"app/pay/notify/applepay" parameters:params success:^(NSMResponseObject *responseObject) {
                        
                        NSLog(@"校验成功");
                        !success?:success(responseObject);
    
                    } empty:nil failure:^(NSError *error) {
                        
                        NSLog(@"校验失败");
                        
                    } hud:NO];
                }
                    break;
                case SKPaymentTransactionStateFailed:
                    NSLog(@"购买失败");
                    break;
                default:
                    break;
            }
        }];
    }];
}


// MARK: -------------  View切圆角  (CGSize)radii未View的size时，切出圆形 -------------
 -(UIView*)getCutRadiiWithView:(UIView*)view radii:(CGSize)radii{
    UIBezierPath *maskPath = [UIBezierPath bezierPathWithRoundedRect:view.bounds byRoundingCorners:UIRectCornerAllCorners cornerRadii:radii];
    CAShapeLayer *maskLayer = [[CAShapeLayer alloc]init];
    //设置大小
    maskLayer.frame = view.bounds;
    //设置图形样子
    maskLayer.path = maskPath.CGPath;
    view.layer.mask = maskLayer;
    return view;
}


// 获取视频第一帧
- (UIImage*)getVideoPreViewImage:(NSString *)path isInterNetUrl:(BOOL)isInternet{
    AVURLAsset *asset=nil;
    if (isInternet) {
        asset =[[AVURLAsset alloc] initWithURL:[NSURL URLWithString:path] options:nil];
    }else{
        asset =[[AVURLAsset alloc] initWithURL:[NSURL fileURLWithPath:path] options:nil];
    }
    AVAssetImageGenerator *assetGen = [[AVAssetImageGenerator alloc] initWithAsset:asset];
    assetGen.appliesPreferredTrackTransform = YES;
    CMTime time = CMTimeMakeWithSeconds(0.0, 600);
    NSError *error = nil;
    CMTime actualTime;
    CGImageRef image = [assetGen copyCGImageAtTime:time actualTime:&actualTime error:&error];
    UIImage *videoImage = [[UIImage alloc] initWithCGImage:image];
    CGImageRelease(image);
    if (videoImage == nil) {
        
        videoImage = [UIImage imageNamed:@"default_video.png"];
    }
    return videoImage;
}


// MARK: -------------  根据URL获取网络音频时长  -------------
- (CGFloat)audioDurationFromURL:(NSString *)url {
    AVURLAsset *audioAsset = nil;
    NSDictionary *dic = @{AVURLAssetPreferPreciseDurationAndTimingKey:@(YES)};
    if ([url hasPrefix:@"http://"]) {
        audioAsset = [AVURLAsset URLAssetWithURL:[NSURL URLWithString:url] options:dic];
    }
    CMTime audioDuration = audioAsset.duration;
    float audioDurationSeconds = CMTimeGetSeconds(audioDuration);
    return audioDurationSeconds;
}


#pragma mark 自定义导航按钮
- (void)createTextBar:(NSString *)text target:(UIViewController*)targetVC action:(SEL)action isLeft:(BOOL)isLeft{
    
    UIFont *font = [UIFont systemFontOfSize:16];
    CGFloat textWidth = [text boundingRectWithSize:CGSizeMake(MAXFLOAT, MAXFLOAT) options:NSStringDrawingUsesLineFragmentOrigin attributes:@{NSFontAttributeName : font} context:nil].size.width;
    UIButton *customBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    [customBtn setTitle:text forState:UIControlStateNormal];
    customBtn.titleLabel.textColor = [UIColor blackColor];
    [customBtn setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    customBtn.titleLabel.font = font;
    customBtn.frame = CGRectMake(0, 0, textWidth, 40);
    customBtn.backgroundColor= [UIColor clearColor];
    [customBtn addTarget:targetVC action:action forControlEvents:UIControlEventTouchUpInside];
    UIBarButtonItem *customBar = [[UIBarButtonItem alloc] initWithCustomView:customBtn];
    if(isLeft) {
        targetVC.navigationItem.leftBarButtonItem = customBar;
    }else{
        targetVC.navigationItem.rightBarButtonItem = customBar;
    }
}
// MARK: -------------  获取当前时间字符串  -------------
- (NSString*)getNowDateStrWithFormat:(NSString*)format{
    // 获取系统当前时间
    NSDate * date = [NSDate date];
    NSTimeInterval sec = [date timeIntervalSinceNow];
    NSDate * currentDate = [[NSDate alloc] initWithTimeIntervalSinceNow:sec];
    //设置时间输出格式：
    NSDateFormatter * df = [[NSDateFormatter alloc] init ];
    [df setDateFormat:format];
    NSString * na = [df stringFromDate:currentDate];
    return na;
}


#pragma mark - 转位图片
- (UIImage *)convertViewToImage:(UIView *)view{
    
    UIImage *image = [[UIImage alloc] init];
    UIGraphicsBeginImageContextWithOptions(view.size, NO, [UIScreen mainScreen].scale);
    [view.layer renderInContext:UIGraphicsGetCurrentContext()];
    image = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return image;
}

#pragma mark - 打开相机或相册
- (void)alertPhotoSelectorWithController:(UIViewController *)currentController{
    
    self.currentController = currentController;
    UIAlertController *actionSheet = [UIAlertController alertControllerWithTitle:@"Upload photo" message:nil preferredStyle:UIAlertControllerStyleActionSheet];
    actionSheet.modalPresentationStyle = UIModalPresentationCustom;
    UIAlertAction *snap = [UIAlertAction actionWithTitle:@"Camera" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        [self selectImageWithmethod:NO];
    }];
    UIAlertAction *pick = [UIAlertAction actionWithTitle:@"Library" style:0 handler:^(UIAlertAction * _Nonnull action) {
        [self selectImageWithmethod:YES];
    }];
    UIAlertAction *cancel = [UIAlertAction actionWithTitle:@"Cancel" style:UIAlertActionStyleDefault handler:nil];
    
    [actionSheet addAction:snap];
    [actionSheet addAction:pick];
    [actionSheet addAction:cancel];
    [currentController presentViewController:actionSheet animated:YES completion:nil];
}
//打开相册或者开始录制视频
- (void)alertVideoSelectorWithController:(UIViewController *)currentController{
    
    [OSTool setStatusBarBackgroundColor:[UIColor clearColor]];
    self.currentController = currentController;
    UIAlertController *actionSheet = [UIAlertController alertControllerWithTitle:@"Upload Video" message:nil preferredStyle:UIAlertControllerStyleActionSheet];
    actionSheet.modalPresentationStyle = UIModalPresentationCustom;
    UIAlertAction *snap = [UIAlertAction actionWithTitle:@"Camera" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        [self selectVideoWithMethod:NO];
    }];
    UIAlertAction *pick = [UIAlertAction actionWithTitle:@"Library" style:0 handler:^(UIAlertAction * _Nonnull action) {
        [self selectVideoWithMethod:YES];
    }];
    UIAlertAction *cancel = [UIAlertAction actionWithTitle:@"Cancel" style:UIAlertActionStyleDefault handler:nil];
    
    [actionSheet addAction:snap];
    [actionSheet addAction:pick];
    [actionSheet addAction:cancel];
    [currentController presentViewController:actionSheet animated:YES completion:nil];
}

- (void)selectVideoWithMethod:(BOOL)isLib{
    
    //选择视频
    UIImagePickerController * picker = [[UIImagePickerController alloc] init];
    picker.modalPresentationStyle = UIModalPresentationCustom;

    picker.delegate = self;
    picker.mediaTypes = [NSArray arrayWithObjects:@"public.movie", nil];
    picker.sourceType = isLib ? UIImagePickerControllerSourceTypePhotoLibrary : UIImagePickerControllerSourceTypeCamera;
    
    [self.currentController presentViewController:picker animated:YES completion:nil];
}

- (void)selectImageWithmethod:(BOOL)isLib{
    //相册中选择
    if (isLib) {
        
        ZYQAssetPickerController *picker = [ZYQAssetPickerController new];
        picker.modalPresentationStyle = UIModalPresentationCustom;
        picker.maximumNumberOfSelection = 9;
        picker.assetsFilter = [ALAssetsFilter allPhotos];
        picker.showEmptyGroups = NO;
        picker.delegate = self;
        picker.selectionFilter = [NSPredicate predicateWithBlock:^BOOL(id evaluatedObject, NSDictionary *bindings) {
            if ([[(ALAsset*)evaluatedObject valueForProperty:ALAssetPropertyType] isEqual:ALAssetTypeVideo]) {
                NSTimeInterval duration = [[(ALAsset*)evaluatedObject valueForProperty:ALAssetPropertyDuration] doubleValue];
                return duration >= 5;
            } else return YES;
        }];
        [self.currentController presentViewController:picker animated:YES completion:nil];
        return;
    }
    UIImagePickerController *ipc = [UIImagePickerController new];
    ipc.sourceType = UIImagePickerControllerSourceTypeCamera;
    ipc.delegate = self;
    [self.currentController presentViewController:ipc animated:YES completion:nil];
}


- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info {
    
    NSString * mediaType = [info objectForKey:UIImagePickerControllerMediaType];

    if ([mediaType isEqualToString:@"public.movie"]){
        //如果是视频
        NSURL *videoUrl = info[UIImagePickerControllerMediaURL];//获得视频的URL
        NSLog(@"url %@",videoUrl);
        
        NSDictionary *opts = [NSDictionary dictionaryWithObject:[NSNumber numberWithBool:NO]
                                                         forKey:AVURLAssetPreferPreciseDurationAndTimingKey];
        AVURLAsset *urlAsset = [AVURLAsset URLAssetWithURL:videoUrl options:opts];  // 初始化视频媒体文件
        int second = (int)urlAsset.duration.value / urlAsset.duration.timescale; // 获取视频总时长,单位秒
        if (second >= 15) {
            NSLog(@"视频时长需在15秒内");
            [self.currentController dismissViewControllerAnimated:YES completion:^{
            
                [OSTool setStatusBarBackgroundColor:[UIColor whiteColor]];
            }];
            return;
        }
        UIImage *lowImage = [self getVideoPreViewImage:[NSString stringWithFormat:@"%@",videoUrl] isInterNetUrl:NO];//获取本地视频缩略图
        [self.currentController dismissViewControllerAnimated:YES completion:^{
            
            [OSTool setStatusBarBackgroundColor:[UIColor whiteColor]];
            !self.selectedVideo?:self.selectedVideo(lowImage, videoUrl.absoluteString);
        }];
        
        return;
        //上传视频缩略图
//        UploadImage(lowImage, UploadImageMethodPhoto, ^(NSString * _Nonnull url) {
//
//            //上传成功，开始上传视频
//            [_networker POST:@"" parameters:nil formDataBlock:^(id<AFMultipartFormData> formData) {
//
//                NSData *fileData = [NSData dataWithContentsOfURL:videoUrl];
//                [formData appendPartWithFileData:fileData name:@"file" fileName:@"video.mp4" mimeType:@"video/mp4"];
//
//            } success:^(NSMResponseObject *responseObject) {
//
//                !self.selectedVideo?:self.selectedVideo(lowImage, videoUrl.absoluteString);
//                //上传成功
//
//            } empty:nil failure:^(NSError *error) {
//
//                //上传失败
//
//            } hud:YES];
//
//        }, ^{
//            NSLog(@"上传失败");
//        });
        
        return;
    }
    
    UIImage *image = info[UIImagePickerControllerOriginalImage];
    // 如果是拍照,保存到手机相册
    if(picker.sourceType == UIImagePickerControllerSourceTypeCamera) {
        UIImageWriteToSavedPhotosAlbum(image,nil,nil,nil);
    }
    
    @nsm_weak(self)
    [self.currentController dismissViewControllerAnimated:YES completion:^{
        @nsm_strong(self)
        // 照片选取完之后调用编辑
        [OSTool setStatusBarBackgroundColor:[UIColor whiteColor]];
        !self.selectedImage?:self.selectedImage(@[image]);
    }];
}

- (void)assetPickerController:(ZYQAssetPickerController *)picker didFinishPickingAssets:(NSArray *)assets {
    // 只有多选才会到这里
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        NSMutableArray *newImages = @[].mutableCopy;
        for (int i=0; i<assets.count; i++) {
            ALAsset *asset = assets[i];
            UIImage *image = [UIImage imageWithCGImage:asset.aspectRatioThumbnail];
            if (!image) {
                return;
            }
            [newImages addObject:image];
        }
        dispatch_async(dispatch_get_main_queue(), ^{
    
            !self.selectedImage?:self.selectedImage(newImages);
        });
    });
}

@end
