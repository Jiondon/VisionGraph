#ifndef XVFIELD_H
#define XVFIELD_H

#include "XVGeometry.h"
#include "XVPath.h"


///ScanField
struct XVSegmentScanField //与XVSegmentFittingField取扫描线的方式不同
{
    XVOptionalType  optional = NUL;
    XVSegment2D     axis     ;
    float           width    = 20.0f;
};

///FittingField
struct XVCircleFittingField             //圆环域
{
    XVOptionalType  optional = NUL;
    XVCircle2D      axis     ;        //扫描中心轴
    float           width    = 20.0f; //扫描宽度
};

struct XVArcFittingField                //圆弧域
{
    XVOptionalType  optional = NUL;
    XVArc2D         axis     ;
    float           width    = 20.0f;
};

struct XVSegmentFittingField
{
    XVOptionalType  optional = NUL;
    XVSegment2D     axis     ;
    float           width    = 20.0f;
};

struct XVPathFittingField
{
    XVOptionalType  optional = NUL;
    XVPath          axis     ;
    float           width    = 20.0f;
};


#endif // XVFIELD_H
