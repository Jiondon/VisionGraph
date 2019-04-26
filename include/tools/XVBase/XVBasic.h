#ifndef XVBASIC_H
#define XVBASIC_H

#include "XVOptional.h"

//二维点
typedef struct XVLocation
{
    XVOptionalType  optional = NUL;
    int x = 0;
    int y = 0;
}XVPoint2DInt;

//Box
struct XVBox
{
    XVOptionalType  optional = NUL;
    XVPoint2DInt    origin = XVPoint2DInt(); //顶点(左上点，不是中心)
    int             width  = 0;  //宽度
    int             height = 0; //高度
};

//像素
struct XVPixel
{
    XVOptionalType  optional = NUL;
    float           x = 0.0f;
    float           y = 0.0f;
    float           z = 0.0f;
    float           w = 0.0f;
};

//Size
struct XVSize
{
    XVOptionalType  optional = NUL;
    int             width  = 0;
    int             height = 0;
};

#endif // XVBASIC_H
