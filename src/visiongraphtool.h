/****************************************************************************
** @brief       全景变量
** @note        存放全局变量以及部分重复使用率很高的头文件
** @author      xiaodongLi
** @date        create:2018-09-28
** @example
****************************************************************************/


#ifndef VISIONGRAPHTOOL_H
#define VISIONGRAPHTOOL_H


//VisionGraph 的控件的头文件
#include "visiongraph_global.h"

#include "./item/visiongraphscene.h"
#include "./item/visiongraphview.h"
#include "visiongraphwidget.h"
#include "./item/visionrectitem.h"
#include "./item/visionellipseitem.h"
#include "./item/visionlineitem.h"
#include "./item/visionpolygon.h"
#include "./item/visionpoint.h"
#include "./item/visionring.h"
#include "./item/visioncrosspointitem.h"

#include "./control/color.h"

enum ToolButtonDirection{
    leftDirection,
    topDirection,
    rightDirection,
    bottomDirection
};

enum ToolButtonType
{
    //左侧工具栏 -- 绘制类（操作类）
    ToolButtonSys_selected, //选中
    ToolButtonSys_drag, //拖动
    ToolButtonSys_zoom, //缩放

    ToolButtonSys_mousePainter, //鼠标绘制
    ToolButtonSys_mouseClear, //鼠标清除

    ToolButtonSys_save, //保存

    ToolButtonSys_rect, //绘制矩形
    ToolButtonSys_ellipse, //绘制椭圆或者圆
    ToolButtonSys_poly, //绘制多边形
    ToolButtonSys_poly_elli, //绘制任意区域
    ToolButtonSys_point, //绘制点
    ToolButtonSys_line, //绘制线
    ToolButtonSys_polyLine, //绘制折线

    //右侧工具栏 -- 功能类
    ToolButtonSys_open_project,  //打开工程
    ToolButtonSys_front,  //撤销
    ToolButtonSys_next,   //取消撤销
    ToolButtonSys_clear,  //清空绘图区域
    ToolButtonSys_remove_item,  //删除当前选中的item

};

#endif // VISIONGRAPHTOOL_H
