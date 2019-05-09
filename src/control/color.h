
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
    graph_Info,  //单纯显示
    graphRegion,
    graphItem_self,
    graphItem_unSelf,
    graphChain,
    graphItem_Fitting,
    graph_Path,
    graph_Location,
    graph_Rectangle,
    graph_Arc,
    graph_Circle
};

/**
 * @brief       枚举颜色主题
 * @note        red_black_white 默认
 */
enum ThemeColor{
    lightBlue,
    dark
};


extern QColor regionColor;  //生成区域的颜色

extern QString iconPath;  //图标的路径

extern QCursor viewCursor; //view中的鼠标样式，方便在item中变化了样式后，再次恢复

extern qreal g_scale;
extern qreal g_penWidth;

#endif // COLOR_H
