#ifndef XVREGION_H
#define XVREGION_H

#include "XVGeometry.h"

namespace XVRectangularRoiMask{
enum Type
{
    Rectangle,
    Ellipse
};
}

//行程
struct XVPointRun
{
    int    x;
    int    y;  // PointRun begin location 起始点的x,y像素位置
    int    length;//行程
};

struct XVRegion
{
    XVOptionalType      optional = NUL; //ROI是否起作用
    int                 frameWidth;
    int                 frameHeight;
    vector<XVPointRun>  arrayPointRun;
};

struct XVShapeRegion{
    XVOptionalType              optional = NUL;
    XVRectangle2D               frame;
    XVRectangularRoiMask::Type  mask;
};

static void CopyXVRegion(const XVRegion& src, XVRegion& dest)
{
    dest.optional      = src.optional     ;
    dest.frameWidth    = src.frameWidth   ;
    dest.frameHeight   = src.frameHeight  ;
    dest.arrayPointRun.clear();
    for(auto c:src.arrayPointRun)
        dest.arrayPointRun.push_back(c);
}

#endif // XVENUM_H
