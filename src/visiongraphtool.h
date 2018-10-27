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

#endif // VISIONGRAPHTOOL_H
