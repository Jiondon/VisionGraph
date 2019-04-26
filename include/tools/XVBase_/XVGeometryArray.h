#ifndef XVGEOMETRYARRAY_H
#define XVGEOMETRYARRAY_H

#include "XVGeometry.h"

struct XVArray_XVArc2D
{
    XVOptionalType          optional = NUL;
    vector<XVArc2D>         array;
};

struct XVArray_XVSegment2D
{
    XVOptionalType          optional = NUL;
    vector<XVSegment2D>     array;
};

struct XVArray_XVRectangle2D
{
    XVOptionalType          optional = NUL;
    vector<XVRectangle2D>   array;
};

struct XVArray_XVVector2D
{
    XVOptionalType          optional = NUL;
    vector<XVVector2D>      array;
};


#endif // XVGEOMETRYARRAY_H
