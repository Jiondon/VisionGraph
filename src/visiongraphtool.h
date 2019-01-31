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
#include "./item/visionchainitem.h"
#include "./item/visionarrow.h"
#include "./item/visionarcitem.h"

#include "./item/visionlineitemfitting.h"
#include "./item/visionarcitemfitting.h"
#include "./item/visionpolygonitemfitting.h"

#include "./control/color.h"

/**
 * @brief       枚举工具栏的摆放方式和位置，
 */
enum ToolButtonDirection{
    leftDirection,
    topDirection,
    rightDirection,
    bottomDirection
};

/**
 * @brief       枚举view中绘制控件的限制
 * @note        可随意搭配
 */
enum ViewType{
    freeItem,  //随意搭配，不限制
    _singleItem,  //单一item (绘制的时候会删除view中其他的item)
    singleItem,  //单一item
    multiItem,  //多个item
    singleRegion,  //单一区域
    multiRegion  //多个区域
};

enum ToolButtonType
{
    //左侧工具栏 -- 绘制类（操作类）
    ToolButtonSys_selected, //选中
    ToolButtonSys_drag, //拖动
    ToolButtonSys_zoom, //缩放
    ToolButtonSys_Fit,
    ToolButtonSys_save, //保存

    //右侧工具栏 -- 功能类
    ToolButtonSys_open_project,  //打开工程
    ToolButtonSys_front,  //撤销
    ToolButtonSys_next,   //取消撤销
    ToolButtonSys_clear,  //清空绘图区域
    ToolButtonSys_remove_item,  //删除当前选中的item


    ToolButtonSys_mousePainter, //鼠标绘制
    ToolButtonSys_mouseClear, //鼠标清除

    ToolButtonSys_rect, //绘制矩形
    ToolButtonSys_ellipse, //绘制椭圆或者圆
    ToolButtonSys_Arc,//绘制圆弧
    ToolButtonSys_poly, //绘制多边形
    ToolButtonSys_poly_elli, //绘制任意区域
    ToolButtonSys_point, //绘制点
    ToolButtonSys_line, //绘制线
    ToolButtonSys_polyLine, //绘制折线
};

#endif // VISIONGRAPHTOOL_H
