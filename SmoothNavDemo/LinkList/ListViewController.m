//
//  ListViewController.m
//  SmoothNavDemo
//
//  Created by xiaoguang on 2022/1/12.
//  Copyright © 2022 Cloudox. All rights reserved.
//

#import "ListViewController.h"
#import "TypeModel.h"
#import "ListModel.h"
#import "TypeTableViewCell.h"
#import "ListTableViewCell.h"
@interface ListViewController ()<UITableViewDataSource, UITableViewDelegate>

@property (nonatomic, strong) UITableView *typeTableView;
@property (nonatomic, strong) UITableView *listTableView;
@property (nonatomic, strong) NSMutableArray *typeArr;
@property (nonatomic, strong) NSMutableArray *listArr;
@property (nonatomic, assign) NSInteger currentIndex;
@end

@implementation ListViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self hidesBottomBarWhenPushed];
    self.view.backgroundColor = [UIColor whiteColor];
    self.typeArr = [NSMutableArray array];
    self.listArr = [NSMutableArray array];
    [self.view addSubview:self.typeTableView];
    [self.view addSubview:self.listTableView];
    [self getProductSource];
    [self.typeTableView reloadData];
    [self.listTableView reloadData];
    [self.typeTableView selectRowAtIndexPath:[NSIndexPath indexPathForRow:0 inSection:0] animated:NO scrollPosition:UITableViewScrollPositionNone];
    
    // Do any additional setup after loading the view.
}

- (void)getProductSource{
    
    NSString *path = [[NSBundle mainBundle] pathForResource:@"meituan" ofType:@"json"];
    NSError *error = [NSError errorWithDomain:NSCocoaErrorDomain code:1 userInfo:nil];
    NSDictionary *dic = [NSJSONSerialization JSONObjectWithData:[NSData dataWithContentsOfFile:path] options:0 error:&error];

    if ([dic[@"code"] intValue] == 0){
        
        NSArray *tags = dic[@"data"][@"food_spu_tags"];
        for (NSDictionary *tagDic in tags) {
            
            TypeModel *model = [TypeModel modelWithJSON:tagDic];
            NSMutableArray *spusArr = [NSMutableArray array];
            for (NSDictionary *spuDic in model.spus) {
                
                ListModel *model = [ListModel modelWithJSON:spuDic];
                [spusArr addObject:model];
            }
            model.spus = spusArr;
            [self.typeArr addObject:model];
        }
    }
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView{
    
    if (tableView == self.typeTableView) {
        
        return 1;
    }
    return self.typeArr.count * 3;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    
    if (tableView == self.typeTableView) {
        
        return self.typeArr.count;
    }
    TypeModel *model = self.typeArr[section % self.typeArr.count];
    return model.spus.count;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section{
    
    TypeModel *model = self.typeArr[section % self.typeArr.count];
    return model.name;
}

//- (NSString *)tableView:(UITableView *)tableView titleForFooterInSection:(NSInteger)section{
//    TypeModel *model = self.typeArr[section];
//    return model.name;
//
//}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath{
    
    return 70;
}

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section{
    
    
    if (tableView == self.typeTableView) {
        
        return 0;
    }
    return 20;
}

- (CGFloat)tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section{
    
    return 0;
}

- (void)scrollViewDidScroll:(UIScrollView *)scrollView{
    
    if (scrollView == self.listTableView) {
        
        CGPoint offset = scrollView.contentOffset;
        if (offset.y < 0) {
            
            offset.y = self.listTableView.contentSize.height/3;
            
        }else if (offset.y >= self.listTableView.contentSize.height - self.listTableView.height){
            
            offset.y = self.listTableView.contentSize.height/3 - self.listTableView.height;
        }
        [self.listTableView setContentOffset:offset];
    }
}

- (void)tableView:(UITableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath{
    
    if (tableView == self.listTableView) {
        
        if (self.currentIndex != (indexPath.section % self.typeArr.count)) {

            self.currentIndex = indexPath.section % self.typeArr.count;
            [self.typeTableView selectRowAtIndexPath:[NSIndexPath indexPathForRow:self.currentIndex inSection:0] animated:YES scrollPosition:UITableViewScrollPositionTop];
        }
    }
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    
    if (tableView == self.typeTableView) {
        
        TypeTableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:NSStringFromClass(TypeTableViewCell.class) forIndexPath:indexPath];
        TypeModel *model = self.typeArr[indexPath.row];
        cell.typeLabel.text = model.name;
        return cell;
    }
    ListTableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:NSStringFromClass(ListTableViewCell.class) forIndexPath:indexPath];
    TypeModel *model = self.typeArr[indexPath.section % self.typeArr.count];
    ListModel *model1 = model.spus[indexPath.row];
    cell.foodNameLabel.text = model1.name;
    cell.foodPriceLabel.text = FormatString(@"¥ %ld", model1.min_price);
    cell.foodImageView.imageURL = URL(model1.picture);
    return cell;
}
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    
    if (tableView == self.typeTableView) {
        
        self.currentIndex = indexPath.row;
        [self.listTableView scrollToRow:0 inSection:self.currentIndex atScrollPosition:UITableViewScrollPositionTop animated: YES];
    }
}

- (UITableView *)listTableView{
    
    if (!_listTableView) {
        
        _listTableView = [[UITableView alloc] initWithFrame:CGRectMake(88, 0, kScreenWidth - 88, kScreenHeight) style:UITableViewStylePlain];
        _listTableView.backgroundColor = [UIColor whiteColor];
        _listTableView.separatorStyle = UITableViewCellSeparatorStyleSingleLine;
        _listTableView.delegate = self;
        _listTableView.dataSource = self;
        _listTableView.showsVerticalScrollIndicator = NO;
        _listTableView.separatorInset = UIEdgeInsetsMake(0, 15, 0, 0);
        _listTableView.bounces = NO;
        [_listTableView registerClass:ListTableViewCell.class forCellReuseIdentifier:NSStringFromClass(ListTableViewCell.class)];
    }
    return _listTableView;
}



- (UITableView *)typeTableView{
    
    if (!_typeTableView) {
        
        _typeTableView = [[UITableView alloc] initWithFrame:CGRectMake(0, 0, 88, kScreenHeight) style:UITableViewStylePlain];
        _typeTableView.backgroundColor = [UIColor whiteColor];
        _typeTableView.separatorStyle = UITableViewCellSeparatorStyleNone;
        _typeTableView.delegate = self;
        _typeTableView.dataSource = self;
        _typeTableView.showsVerticalScrollIndicator = NO;
        [_typeTableView registerClass:TypeTableViewCell.class forCellReuseIdentifier:NSStringFromClass(TypeTableViewCell.class)];
    }
    return _typeTableView;
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
