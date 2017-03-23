
/*****************(一)常用的第三方库*******************/
*集成了个推GtSdk

*AFNetWorking        --网络请求--                   https://github.com/AFNetworking/AFNetworking
*MJRefresh           --刷新--                      https://github.com/CoderMJLee/MJRefresh
*MJExtension         --字典模型转换工具--            https://github.com/CoderMJLee/MJExtension
*SDWebImage          --图片加载--                   https://github.com/rs/SDWebImage
*MBProgressHUD       --用于加载的loading和提示框--    https://github.com/jdg/MBProgressHUD
*IQKeyBoardManager   --用于解决输入框被键盘遮挡的问题-- https://github.com/hackiftekhar/IQKeyboardManager
*Masonry             --用于布局约束--                https://github.com/SnapKit/Masonry

/*****************(二)我是第二梯队*******************/

*UITableView+FDTemplateLayoutCell   --用于动态计算cell高度(由于你名字太长被第一梯队挤下边来了)--
                                    -- https://github.com/forkingdog/UITableView-FDTemplateLayoutCell
优化UITableViewCell高度计算的那些事地址  -- http://blog.sunnyxx.com/2015/05/17/cell-height-calculation/

*DDCarouselView                     --添加轮播
*OrderPay                           --(支付工具合集)查看该类,集成苹果支付,支付宝,微信支付,银联支付
*DDSegmentPageView                  --(分页)查看SegmentPageHead.h可查看使用示例
*NullSafe.m                         --加在程序中,解决NUll问题
*SingleTon.h                        --宏定义单例,使用示例:查看DDSingleData.h与DDSingleData.m 直接创建出单例

**Helper.h                          --工具帮助类,将常用方法写在这里方便调用

/*****************(三)常用宏合集提示*******************/

*testProject.pch--程序启动

/*****************(三)(1)*******************/

1.存放一些全局的宏(整个项目中都用得上的宏)

**做项目前先查看.pch文件,一些常用宏,无需自己重新再定义一遍

//*打开或者关闭日志输出功能
#ifdef DEBUG
#define DLLog(...) NSLog(__VA_ARGS__)
#else
#define DLLog(...)
#endif

//解决xcode8打印出一些乱码或者不完整的情况
#define NSLog(FORMAT, ...) printf("%s\n", [[NSString stringWithFormat:FORMAT, ##__VA_ARGS__] UTF8String]);

//获取屏幕宽高
#define KScreenWidth [UIScreen mainScreen].bounds.size.width
#define KScreenHeight [UIScreen mainScreen].bounds.size.height

//适配可能很多人还习惯性的frame比例
#define kw(R)               (R) * (KScreenWidth) / 320.0
#define kh(R)               (R) * (KScreenHeight) / 568.0

//保存个人信息
//为NSUserDefaults 添加object和key
#define Kusersave(object,key) [[NSUserDefaults standardUserDefaults] setObject:object forKey:key]
//读取NSUserDefaults中key的元素
#define Kuserread(key) [[NSUserDefaults standardUserDefaults] objectForKey:key]
//删除NSUserDefaults中key的元素
#define Kuserdelete(key) [[NSUserDefaults standardUserDefaults] removeObjectForKey:key]

//沙盒路径
//获取temp
#define kPathTemp NSTemporaryDirectory()
//获取沙盒 Document
#define kPathDocument [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) firstObject]
//获取沙盒 Cache
#define kPathCache [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) firstObject]

/*****判空******/
//字符串是否为空
#define kStringIsEmpty(str) ([str isKindOfClass:[NSNull class]] || str == nil || [str length] < 1 ? YES : NO )

//数组是否为空
#define kArrayIsEmpty(array) (array == nil || [array isKindOfClass:[NSNull class]] || array.count == 0)

//字典是否为空
#define kDictIsEmpty(dic) (dic == nil || [dic isKindOfClass:[NSNull class]] || dic.allKeys == 0)

//是否是空对象
#define kObjectIsEmpty(_object) (_object == nil \
|| [_object isKindOfClass:[NSNull class]] \
|| ([_object respondsToSelector:@selector(length)] && [(NSData *)_object length] == 0) \
|| ([_object respondsToSelector:@selector(count)] && [(NSArray *)_object count] == 0))

/***************热点问题******************/

// 标准系统状态栏高度
#define SYS_STATUSBAR_HEIGHT                20
// 热点栏高度
#define HOTSPOT_STATUSBAR_HEIGHT            20

// 导航栏（UINavigationController.UINavigationBar）高度
#define NAVIGATIONBAR_HEIGHT                44

// 标签栏（UITabBarController.UITabBar）高度
#define TABBAR_HEIGHT                       48

// APP_STATUSBAR_HEIGHT=SYS_STATUSBAR_HEIGHT+[HOTSPOT_STATUSBAR_HEIGHT]
#define APP_STATUSBAR_HEIGHT                (CGRectGetHeight([UIApplication sharedApplication].statusBarFrame))

// 根据APP_STATUSBAR_HEIGHT判断是否存在热点栏
#define IS_HOTSPOT_CONNECTED                (APP_STATUSBAR_HEIGHT==(SYS_STATUSBAR_HEIGHT+HOTSPOT_STATUSBAR_HEIGHT)?YES:NO)

// 无热点栏时，标准系统状态栏高度+导航栏高度
#define NOSTATUS_NAV_HEIGHT                 (SYS_STATUSBAR_HEIGHT+NAVIGATIONBAR_HEIGHT)

// 实时系统状态栏高度+导航栏高度，如有热点栏，其高度包含在APP_STATUSBAR_HEIGHT中。
#define STATUS_NAV_HEIGHT                   (APP_STATUSBAR_HEIGHT+NAVIGATIONBAR_HEIGHT)

//TableView的高度,减去tabbar和nav的高度
#define TableViewHomeHeight                 (KScreenHeight-APP_STATUSBAR_HEIGHT-NAVIGATIONBAR_HEIGHT-TABBAR_HEIGHT)

//TableView的高度,减去nav的高度
#define TableViewHeight                     (KScreenHeight-APP_STATUSBAR_HEIGHT-NAVIGATIONBAR_HEIGHT)


/*****************(三)(2)*******************/

2.用来包含一些全部的头文件(整个项目中都用得上的头文件,在使用以下类的时候不需要导入头文件)

*HttpDefine--宏定义网络接口
*ColorDefine--宏定义常用色值

#import "UIImageView+WebCache.h"
#import "MJExtension.h"
#import "MJRefresh.h"
#import "Masonry.h"
#import "NetworkTool.h"//网络请求
#import "Helper.h"

#import "DDCategories.h"//各种拓展类别请先查看各个.h文件了解有哪些实用功能代码或者查看(四)(2)
#import "FSTextView.h"//创建textView实用该类,自带类似textfield的提示label功能

#import "LoginViewController.h"


/*****************(四)常用方法合集提示*******************/

/*****************(四)(1)*******************/

1.//显示loading加载中
[Helper showLoadingWithView:self.view];
//隐藏loading
[Helper hiddonLoadingWithView:self.view];

2.//提示语
[Helper showMessageWithHud:@"我只是提示语" addTo:self yOffset:0];

3.//解决键盘遮挡住输入框的问题
[Helper setKeyboardManagerEnable:YES];

/*****************(四)(2)*******************/

//以下为类别各功能,全集请查看该git地址:https://github.com/shaojiankui/JKCategories

1.UIButton+JKImagePosition   -- 用button的titleEdgeInsets和 imageEdgeInsets属性来实现button文字图片上下或者左右排列的
2.UIView+JKScreenshot        -- 截图方法
3.NSString+JKNormalRegex     -- 判断手机邮箱身份证等各种证件的有效性
4.NSString+JKSize            -- 计算宽高
5.NSString+JKTrims           -- 清除html标签
6.
NSDate+JKExtension
NSDate+JKUtilities           -- 时间处理

7.UIColor+JKGradient         -- 渐变色
8.UIDevice+JKHardware        -- 硬件信息

/*****************(四)(3)*******************/

/*请求示例:后台PHP,我这里都是使用post请求*/

    NSMutableDictionary *dic = [[NSMutableDictionary alloc]init];
    [dic setValue:@"" forKey:@"username"];

    [NetworkTool POSTWithURLString:@"URL" parameters:dic isLoading:self.view success:^(id responseObject) {

    NSDictionary * dic = responseObject;

    [self.tempTableView reloadData];

    [self.tempTableView.mj_header endRefreshing];
    [self.tempTableView.mj_footer endRefreshing];

    }

    } faile:^(NSError *error) {

     //当出错时统一打印错误信息,无需再此打印报错信息
    }];

*/

/*****************(五)个人信息提示*******************/

 用户信息在登录、注册时存放在userDefaults，通过key:@"userMsg",获取到用户信息字典中，退出登录删除
    {
        userID = 257480;                                    //用户ID
        userName = AAA;                                     //用户昵称
        userPhoneNo = ;                                     //用户手机号
        userHeadImgUrl = "";                                //用户头像地址
        userAccount = ;                                     //用户账号
        userPassword = ;                                    //用户密码
        userSex = 0;                                        //用户性别
}