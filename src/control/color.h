
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

QColor selectedColor;  //item在选中或者编辑状态下的小矩形和边框的颜色
QColor borderColor;   //绘制的item的边框颜色  未选中或者非编辑的颜色
QColor brushColor;   //填充的颜色
QColor regionColor;  //生成区域的颜色

#endif // COLOR_H
