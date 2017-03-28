//
//  UIView+HYBImageCliped.h
//  HYBImageCliped
//
//  Created by huangyibiao on 16/3/31.
//  Copyright © 2016年 huangyibiao. All rights reserved.
//

#import <UIKit/UIKit.h>


/**
 *	裁剪后的图片
 *  默认所有backgroundColor直取最顶层父视图的backgroundColor，通常已经满足条件了。如果不能满，请手动指定背景颜色
 *
 *	@param clipedImage 裁剪后的图片
 */
typedef void(^HYBClipedCallback)(UIImage *clipedImage);

/**
 * 一、扩展控件通过mask来实现添加任意圆角
 * 二、给所有继承于UIView的控件都可以使用
 *
 * isEqualScale参数：当图片的宽高比比指定的targetSize的宽高比要大得多时，建议使用NO。
 * 下面的所有API都只适用于加载本地图片。对于异步下载图片处理，可以在下载完成后，再异步去
 * 剪裁。下面是使用SDWebImage的一个例子：
 if (model.clipedImage) {
   self.imageView.image = model.clipedImage;
 } else {
   __weak __typeof(self) weakSelf = self;
   UIImage *image = [UIImage imageNamed:@"img5.jpg"];
   [self.imageView sd_setImageWithURL:[NSURL URLWithString:model.url] placeholderImage:image options:SDWebImageRetryFailed completed:^(UIImage *image, NSError *error, SDImageCacheType cacheType, NSURL *imageURL) {
     dispatch_async(dispatch_get_global_queue(0, 0), ^{
     
       // 将剪裁后的图片记录下来，下次直接使用
       model.clipedImage = [image hyb_clipToSize:weakSelf.imageView.bounds.size
       cornerRadius:12
       backgroundColor:[UIColor blackColor]
       isEqualScale:NO];
     
       dispatch_async(dispatch_get_main_queue(), ^{
         weakSelf.imageView.image = model.clipedImage;
       });
     });
   }];
 }
 *
 *	@Note 所裁剪的图片的背景颜色取的是UIImageView的backgroundColor，以解决图层混合问题。
 *        所以，若生成的图片有黑圈之类的，请修改背景颜色！
 */
@interface UIView (HYBImageCliped)

#pragma mark - 边框相关属属性，仅对生成圆形图片和矩形图片有效
/**
 *	默认为0.0，当小于0时，不会添加边框，仅对生成圆形图片和矩形图片有效
 */
@property (nonatomic, assign) CGFloat hyb_borderWidth;
/**
 *	当小于0时，不会添加边框。默认为0.仅对生成圆形图片和矩形图片有效
 */
@property (nonatomic, assign) CGFloat hyb_pathWidth;
/**
 *	边框线的颜色，默认为[UIColor lightGrayColor]，仅对生成圆形图片和矩形图片有效
 */
@property (nonatomic, strong) UIColor *hyb_borderColor;
/**
 *	Path颜色，默认为白色。仅对生成圆形图片和矩形图片有效
 */
@property (nonatomic, strong) UIColor *hyb_pathColor;

/**
 *	内部默认是会缓存corner所生成的圆角或者添加曲线之类的，如果view需要动态地调整，则
 *  每次复用时，应该设置它为YES,则不会缓存。
 *  默认为NO
 */
@property (nonatomic, assign) BOOL hyb_shouldRefreshCache;

#pragma mark - 给任意UIView添加圆角（非图片，性能不如直接使用cornerRadius，但是下面的API支持任意圆角）
/**
 *	给控件本身添加圆角，不是通过图片实现的。要求控件本身的frame是确定的，非自动布局才行。
 *
 *	@param corner			  多个圆角可通过UIRectCornerTopLeft | UIRectCornerTopRight这样来使用
 *	@param cornerRadius	圆角大小
 *
 *  @Example             
 *  [cornerView3 hyb_setImage:@"bimg8.jpg" cornerRadius:10 rectCorner:UIRectCornerTopLeft |UIRectCornerBottomRight isEqualScale:NO onCliped:^(UIImage *clipedImage) {
      // 如果需要复用，可在异步剪裁后，得到已剪裁后的图片，可另行他用
   }];
 */
- (void)hyb_addCorner:(UIRectCorner)corner cornerRadius:(CGFloat)cornerRadius;

// 圆角颜色不应该与背景色相同时，传过来
- (void)hyb_addCorner:(UIRectCorner)corner cornerRadius:(CGFloat)cornerRadius backgroundColor:(UIColor *)backgroundColor;

/**
 * corner为UIRectCornerAllCorners，bounds大小已经有才能使用
 *
 * @Example   
 * 添加一个圆角：[view1 hyb_addCorner:UIRectCornerTopLeft cornerRadius:10];
 */
- (void)hyb_addCornerRadius:(CGFloat)cornerRadius;

/**
 *  corner为UIRectCornerAllCorners，bounds要外部指定
 *
 *	@param cornerRadius	加钱大小
 *	@param targetSize		指frame.size
 */
- (void)hyb_addCornerRadius:(CGFloat)cornerRadius size:(CGSize)targetSize;

/**
 *  给控件本身添加圆角，不是通过图片实现的。
 *
 *	@param corner       添加哪些圆角
 *	@param cornerRadius	圆角大小
 *	@param targetSize		目标大小，即控件的frame.size
 *  @param backgroundColor 控件的背景色与剪裁后的背景色是一样的时候，若需要指定为不一样，传此参数。
 *                         若没有传此参数，默认取最顶层父视图的背景色，若为透明，则取本身背景色，若也为透明，则取白色
 */
- (void)hyb_addCorner:(UIRectCorner)corner
         cornerRadius:(CGFloat)cornerRadius
                 size:(CGSize)targetSize
      backgroundColor:(UIColor *)backgroundColor;


#pragma mark - 生成适应大小的图片显示
/**
 *	使用指定的图片来填充，充当UIImageView。
 *  对于自动布局的控件，如果在设置图片时，没有指定大小，就无法得到正确的图片大小。
 *
 *	@param image	图片名称或者图片对象，甚至支持NSData
 *	@param isEqualScale 是否是等比例缩放
 *  @param targetSize 图片大小。如果没有此参数，表示使用控件本身的大小。
 *  @parma callback   只有当图片真正被裁剪成功后，才会回调，返回裁剪后的图片
 *
 *	@return 裁剪前的图片
 */
- (UIImage *)hyb_setImage:(id)image size:(CGSize)targetSize isEqualScale:(BOOL)isEqualScale onCliped:(HYBClipedCallback)callback;
/**
 * 使用指定的图片来填充图片。对于在填充图片之前，肯定有控件大小的，可以直接使用些API。
 */
- (UIImage *)hyb_setImage:(id)image isEqualScale:(BOOL)isEqualScale onCliped:(HYBClipedCallback)callback;

#pragma mark - 生成圆形图片显示
/**
 *	使用指定的图片来填充，但是生成的是圆形图片，背景颜色为白色。
 *
 *	@param image			图片名称或者图片对象，甚至支持NSData
 *	@param targetSize	生成指定大小的图片
 *	@param isEqualScale	是否等比例缩放图片
 *  @param backgroundColor 默认取最顶层父视图的背景色，若为透明，则取本身背景色，若也为透明，则取白色
 *  @parma callback   只有当图片真正被裁剪成功后，才会回调，返回裁剪后的图片
 *
 *	@return 裁剪前的图片
 */
- (UIImage *)hyb_setCircleImage:(id)image
                           size:(CGSize)targetSize
                   isEqualScale:(BOOL)isEqualScale
                 backgrounColor:(UIColor *)backgroundColor
                       onCliped:(HYBClipedCallback)callback;
/// 使用指定的图片来填充，但是生成的是圆形图片，背景颜色为白色。
- (UIImage *)hyb_setCircleImage:(id)image
                           size:(CGSize)targetSize
                   isEqualScale:(BOOL)isEqualScale
                       onCliped:(HYBClipedCallback)callback;
/**
 *  使用指定的图片来填充，但是生成的是圆形图片，默认背景颜色为白色。当调用此API时，若控件本身
 *  已经有确定的大小，则可以直接使用此API
 */
- (UIImage *)hyb_setCircleImage:(id)image
                   isEqualScale:(BOOL)isEqualScale
                       onCliped:(HYBClipedCallback)callback;

#pragma mark - 生成四个带圆角图片来填充
/**
 *	使用指定图片来填充，生成带四个圆角的图片来填充。生成的图片带有圆角后，为了解决图层混合，需要指定
 *  背景颜色，以便在生成的图片颜色与控件背景颜色一致，可提高性能。
 *
 *	@param image						图片名称或者图片对象，甚至支持NSData
 *	@param targetSize			  生成的图片目标大小
 *	@param cornerRaidus		  圆角大小
 *	@param backgroundColor	背景颜色，用于解决图层混合。默认取最顶层父视图的背景色，若为透明，则取本身背景色，若也为透明，则取白色
 *	@param isEqualScale			是否等比例缩放图片
 *  @parma callback   只有当图片真正被裁剪成功后，才会回调，返回裁剪后的图片
 *
 *	@return 裁剪前的图片
 */
- (UIImage *)hyb_setImage:(id)image
                     size:(CGSize)targetSize
             cornerRadius:(CGFloat)cornerRaidus
          backgroundColor:(UIColor *)backgroundColor
             isEqualScale:(BOOL)isEqualScale
                 onCliped:(HYBClipedCallback)callback;
/**
 * 生成带四个圆角的图片，默认使用白色背景、isEqualScale=YES
 */
- (UIImage *)hyb_setImage:(id)image
                     size:(CGSize)targetSize
             cornerRadius:(CGFloat)cornerRaidus
                 onCliped:(HYBClipedCallback)callback;

/**
 * 生成带四个圆角的图片，默认使用白色背景、isEqualScale=YES。当调用此API时，若控件本身大小是确定的，才能起效！
 */
- (UIImage *)hyb_setImage:(id)image
             cornerRadius:(CGFloat)cornerRaidus
                 onCliped:(HYBClipedCallback)callback;

#pragma mark - 生成任意圆角图片来填充
/**
 *	生成任意圆角的图片来填充控件。
 *
 *	@param image						图片名称或者图片对象，甚至支持NSData
 *	@param targetSize			  生成图片大小
 *	@param cornerRaidus		  圆角大小
 *	@param rectCorner			  指定哪些添加圆角。如果有多个圆角，可以这样UIRectCornerTopRight|UIRectCornerTopLeft
 *	@param backgroundColor	当带有圆角时，背景颜色可用于解决图层混合问题。默认取最顶层父视图的背景色，若为透明，则取本身背景色，若也为透明，则取白色
 *	@param isEqualScale			是否等比例缩放图片
 *  @parma callback   只有当图片真正被裁剪成功后，才会回调，返回裁剪后的图片
 *
 *	@return 裁剪前的图片
 */
- (UIImage *)hyb_setImage:(id)image
                     size:(CGSize)targetSize
             cornerRadius:(CGFloat)cornerRaidus
               rectCorner:(UIRectCorner)rectCorner
          backgroundColor:(UIColor *)backgroundColor
             isEqualScale:(BOOL)isEqualScale
                 onCliped:(HYBClipedCallback)callback;
/**
 * 生成任意圆角的图片来填充控件。默认取最顶层父视图的背景色，若为透明，则取本身背景色，若也为透明，则取白色、isEqualScale=YES
 */
- (UIImage *)hyb_setImage:(id)image
                     size:(CGSize)targetSize
             cornerRadius:(CGFloat)cornerRaidus
               rectCorner:(UIRectCorner)rectCorner
                 onCliped:(HYBClipedCallback)callback;
/**
 * 生成任意圆角的图片来填充控件。默认取最顶层父视图的背景色，若为透明，则取本身背景色，若也为透明，则取白色。如果控件本身大小确定，
 * 可以直接使用此API来生成与控件大小相同的图片来填充。
 */
- (UIImage *)hyb_setImage:(id)image
             cornerRadius:(CGFloat)cornerRaidus
               rectCorner:(UIRectCorner)rectCorner
             isEqualScale:(BOOL)isEqualScale
                 onCliped:(HYBClipedCallback)callback;
/**
 * 生成任意圆角的图片来填充控件。默认取最顶层父视图的背景色，若为透明，则取本身背景色，若也为透明，则取白色、isEqualScale=YES。如果控件本身大小确定，
 * 可以直接使用此API来生成与控件大小相同的图片来填充。
 */
- (UIImage *)hyb_setImage:(id)image
             cornerRadius:(CGFloat)cornerRaidus
               rectCorner:(UIRectCorner)rectCorner
                 onCliped:(HYBClipedCallback)callback;
@end
