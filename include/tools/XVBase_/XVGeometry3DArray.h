#ifndef XVGEOMETRY3DARRAY_H
#define XVGEOMETRY3DARRAY_H

#include "XVGeometry3D.h"
#include "XVGlobal.h"


struct XVArray_XVPoint3D
{
    XVOptionalType          optional = NUL;
    vector<XVPoint3D>       array;
};

struct XVArray_XVSegment3D
{
    XVOptionalType          optional = NUL;
    vector<XVSegment3D>     array;
};

struct XVArray_XVVector3D
{
    XVOptionalType          optional = NUL;
    vector<XVVector3D>      array;
};


#endif // XVGEOMETRY3DARRAY_H
