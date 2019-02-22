
/****************************************************************************
** @brief       全景变量
** @note        存放颜色相关的数据
** @author      xiaodongLi
** @date        create:2018-10-27
** @example
****************************************************************************/

#ifndef COLOR_H
#define COLOR_H

#include <QColor>
#include <QCursor>

/**
 * @brief       枚举VisionGraph的几种版本，
 * @note        graphRegion --- region版本（绘制item后，item失焦后，会通过算法生成区域，此过程不可逆）,需要用户交互（绘制需要用户进行操作）
 * @note        graphItem_self --- item版本（绘制item后，在整个过程中都是可调节的）,不要用户交互，主要是代码中直接调用放开的api来进行绘制
 * @note        graphItem_unSelf --- item版本，需要用户交互（绘制需要用户进行操作）
 * @note        graphChain --- Chain版本，需要用户交互
 * @note        graphItem_Fitting --- Fitting版本，需要用户交互，绘制item后，会根据鼠标拖动形成一个区域

 */
enum GraphType{
    graphRegion,
    graphItem_self,
    graphItem_unSelf,
    graphChain,
    graphItem_Fitting
};

/**
 * @brief       枚举颜色主题
 * @note        red_black_white 默认
 */
enum ThemeColor{
    lightBlue,
    dark
};

extern QColor selectedColor;  //item在选中或者编辑状态下的小矩形和边框的颜色
extern QColor borderColor;   //绘制的item的边框颜色  未选中或者非编辑的颜色
extern QColor brushColor;   //填充的颜色
extern QColor regionColor;  //生成区域的颜色

extern QColor viewMouseInfo_TextColor;  //鼠标信息的颜色
extern QColor viewMouseInfo_BackgroundColor;  //鼠标信息显示的背景颜色

extern QString iconPath;  //图标的路径

extern QCursor viewCursor; //view中的鼠标样式，方便在item中变化了样式后，再次恢复

extern GraphType g_graphType;

#endif // COLOR_H
