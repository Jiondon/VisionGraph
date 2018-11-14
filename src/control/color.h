
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

extern QColor selectedColor;  //item在选中或者编辑状态下的小矩形和边框的颜色
extern QColor borderColor;   //绘制的item的边框颜色  未选中或者非编辑的颜色
extern QColor brushColor;   //填充的颜色
extern QColor regionColor;  //生成区域的颜色

extern QColor viewMouseInfo_TextColor;  //鼠标信息的颜色
extern QColor viewMouseInfo_BackgroundColor;  //鼠标信息显示的背景颜色

extern QString iconPath;  //图标的路径

extern QCursor viewCursor; //view中的鼠标样式，方便在item中变化了样式后，再次恢复
#endif // COLOR_H
