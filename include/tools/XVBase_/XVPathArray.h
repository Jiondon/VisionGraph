#ifndef XVPATHARRAY_H
#define XVPATHARRAY_H

#include "XVPath.h"


struct XVArray_XVPath
{
//    enum Type{
//        Array_closed,
//        ArrayArray_XVPoint2D
//    };

    XVOptionalType          optional = NUL;
    vector<XVPath>          array;
};

struct XVArrayArray_XVPath
{
    XVOptionalType          optional = NUL;
    vector<XVArray_XVPath>  array;
};


#endif // XVPATH_H
