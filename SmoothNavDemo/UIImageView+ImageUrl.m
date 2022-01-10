//
//  UIImageView+ImageUrl.m
//  SmoothNavDemo
//
//  Created by xiaoguang on 2022/1/7.
//  Copyright © 2022 Cloudox. All rights reserved.
//

#import "UIImageView+ImageUrl.h"

@implementation UIImageView (ImageUrl)

- (void)setUrlString:(NSString *)urlString{
    
    objc_setAssociatedObject(self, @selector(urlString), urlString, OBJC_ASSOCIATION_COPY_NONATOMIC);
}

- (NSString *)urlString{
    
    return objc_getAssociatedObject(self, @selector(urlString));
}

- (void)clearAssociateObject{
    
    objc_removeAssociatedObjects(self);
}
@end
