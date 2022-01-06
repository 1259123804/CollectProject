//
//  XGCodeVerifyViewController.m
//  SmoothNavDemo
//
//  Created by xiaoguang on 2022/1/6.
//  Copyright © 2022 Cloudox. All rights reserved.
//

#import "XGCodeVerifyViewController.h"

@interface XGCodeVerifyViewController ()<UITextFieldDelegate>
@property (nonatomic, strong) UIButton *skipBtn;
@property (nonatomic, assign) CGFloat keyboardHeight;
@property (nonatomic, strong) NSTimer *codeTimer;
@property (nonatomic, strong) NSMutableArray *codeTFArr;
@property (nonatomic, strong) NSMutableArray *codeArr;
@end

@implementation XGCodeVerifyViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self initSubviews];
    // Do any additional setup after loading the view.
}
- (void)dealloc{
    
    [NSNotificationCenter.defaultCenter removeObserver:self];
}

- (NSTimer *)codeTimer{
    
    if (!_codeTimer) {
       
       __block NSInteger time = 60;
        
        _codeTimer = [NSTimer timerWithTimeInterval:1 repeats:YES block:^(NSTimer * _Nonnull timer) {
             
             time --;
             dispatch_async(dispatch_get_main_queue(), ^{
                 
                 [self.skipBtn setTitle:[NSString stringWithFormat:@"重新发送（%ld）", time] forState:UIControlStateNormal];
             });
             if (time <= 0) {
                 [self.skipBtn setTitle:@"重新发送" forState:UIControlStateNormal];
                 self.skipBtn.enabled = YES;
                 [self.codeTimer invalidate];
                 self.codeTimer = nil;
                 return;
             }
         }];
    }
    return _codeTimer;
}

- (void)initSubviews{
    
    self.codeTFArr = [NSMutableArray array];
    self.codeArr = [NSMutableArray arrayWithCapacity:4];
    [[NSRunLoop currentRunLoop] addTimer:self.codeTimer forMode:NSRunLoopCommonModes];
    
    UILabel *desLabel = [UILabel new];
    desLabel.text = @"Please enter the verify code:";
    desLabel.font = [UIFont systemFontOfSize:14];
    desLabel.frame = CGRectMake(30, 60, 200, 30);
    [self.view addSubview:desLabel];
    
    for (int i = 0; i < 4; i++) {
        
        UITextField *codeTF = [UITextField new];
        codeTF.frame = CGRectMake( i * 60 + 30, 130,40, 48);
        codeTF.backgroundColor = [UIColor grayColor];
        codeTF.delegate = self;
        codeTF.keyboardType = UIKeyboardTypeNumberPad;
        codeTF.text = @" ";
        [self.view addSubview:codeTF];
        [self.codeTFArr addObject:codeTF];
    }
    
    [self.view addSubview:self.skipBtn];
    //[self getVerifyCode];
    
    [NSNotificationCenter.defaultCenter addObserver:self selector:@selector(showKeyborad:) name:UIKeyboardWillShowNotification object:nil];

}

- (void)showKeyborad:(NSNotification *)notification{
    
    NSDictionary *userInfo = [notification userInfo];
    NSValue *aValue = [userInfo objectForKey:UIKeyboardFrameEndUserInfoKey];
    CGRect keyboardRect = [aValue CGRectValue];
    self.keyboardHeight = keyboardRect.origin.y;
}
- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string{
    
    //删除
    if (string.length == 0) {
        
        //已经输入过验证码
        if (self.codeArr.count != 0) {
            NSInteger currentIndex = self.codeArr.count >= 1 ? self.codeArr.count - 1 : 0;
            UITextField *codeTF = self.codeTFArr[currentIndex];
            if ([textField.text isEqualToString:@" "]) {
                
                [codeTF becomeFirstResponder];
                codeTF.text = @" ";
            }
            [self.codeArr removeLastObject];
            textField.text = @" ";
        }
        return NO;
    }
    if (self.codeArr.count == 4 && string.length != 0) {
        
        return NO;
    }
    if (![textField.text isEqualToString:@" "] && string.length != 0) {
        
        NSInteger currentIndex = self.codeArr.count >= 4 ? 3 : self.codeArr.count;
        [self.codeArr addObject:string];
        UITextField *codeTF = self.codeTFArr[currentIndex];
        codeTF.text = string;
        [codeTF becomeFirstResponder];
        
    }else{
        
        [self.codeArr addObject:string];
        NSInteger currentIndex = self.codeArr.count >= 4 ? 3 : self.codeArr.count;
        UITextField *codeTF = self.codeTFArr[currentIndex];
        textField.text = string;
        [codeTF becomeFirstResponder];
    }
   
    if (self.codeArr.count == 4) {
        
        //验证验证码是否正确
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 1 * NSEC_PER_SEC), dispatch_get_main_queue(), ^{
           
           //跳转
        });
    }
    return NO;
}

- (BOOL)textFieldShouldBeginEditing:(UITextField *)textField{
    
    return YES;
}

- (UIButton *)skipBtn{
    
    if (!_skipBtn) {
      
        _skipBtn = [UIButton new];
        [_skipBtn setTitle:@"重新发送" forState:UIControlStateNormal];
        _skipBtn.frame = CGRectMake((self.view.frame.size.width - 80)/2, 200, 160, 48);
        _skipBtn.layer.cornerRadius = 5.0;
        _skipBtn.layer.masksToBounds = YES;
        _skipBtn.enabled = NO;
        [_skipBtn addTarget:self action:@selector(resendClick) forControlEvents:UIControlEventTouchUpInside];
    }
    return _skipBtn;
}

- (void)resendClick{
    
    [self getVerifyCode];
}

- (void)getVerifyCode{
    
    //获取验证码，成功后开始计时器
    [[NSRunLoop currentRunLoop] addTimer:self.codeTimer forMode:NSRunLoopCommonModes];
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event{
    
    [self.view endEditing:YES];
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
