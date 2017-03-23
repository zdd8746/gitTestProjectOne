//
//  UIColor+Gradient.h
//  JKCategories
//
//  Created by Jakey on 14/12/15.
//  Copyright (c) 2014年 www. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIColor (JKGradient)
/**
 *  @brief  渐变颜色
 *
 *  @param c1     开始颜色
 *  @param c2     结束颜色
 *  @param height 渐变高度
 *
 *  @return 渐变颜色
 */
+ (UIColor*)jk_gradientFromColor:(UIColor*)c1 toColor:(UIColor*)c2 withHeight:(int)height;
@end
