#ifndef XVOBJECT2D_H
#define XVOBJECT2D_H

#include "XVGeometry.h"

struct XVObject2D
{
    XVOptionalType          optional = NUL;
    XVRectangle2D           match;     //一个矩形框
    XVCoordinateSystem2D    alignment; //（即定义一个局部的参考坐标系，在模板匹配中是模板之间的相互变换）
    XVPoint2D               point;     //目标在图像中的位置
    float                   angle = 0.0f;     //angle和scale跟alignment中的值相同
    float                   scale = 1.0f;
    float                   score = 0.0f;
};

#endif // XVOBJECT2D_H
