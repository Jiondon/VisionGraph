#ifndef XVBASIC_H
#define XVBASIC_H

#include "XVOptional.h"

//二维点
typedef struct XVLocation
{
    XVOptionalType  optional = NUL;
    int x;
    int y;
}XVPoint2DInt;

//Box
struct XVBox
{
    XVOptionalType  optional = NUL;
    XVPoint2DInt    origin; //顶点(左上点，不是中心)
    int             width;  //宽度
    int             height; //高度
};

//像素
struct XVPixel
{
    XVOptionalType  optional = NUL;
    float           x;
    float           y;
    float           z;
    float           w;
};

//Size
struct XVSize
{
    XVOptionalType  optional = NUL;
    int             width;
    int             height;
};

#endif // XVBASIC_H
