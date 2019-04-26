#ifndef XVBASETYPEARRAY_H
#define XVBASETYPEARRAY_H

#include "XVBaseType.h"
#include "XVGlobal.h"

struct XVArray_XVInt{
    XVOptionalType      optional = NUL;
    vector<XVInt>       array;
};

struct XVArray_XVFloat{
    XVOptionalType      optional = NUL;
    vector<XVFloat>     array;
};

struct XVArray_XVBool{
    XVOptionalType      optional = NUL;
    vector<XVBool>      array;
};

struct XVArray_XVPoint2D
{
    XVOptionalType      optional = NUL;
    vector<XVPoint2D>   array;
};

struct XVArrayArray_XVInt{
    XVOptionalType              optional = NUL;
    vector<XVArray_XVInt>       array;
};

struct XVArrayArray_XVFloat{
    XVOptionalType              optional = NUL;
    vector<XVArray_XVFloat>     array;
};

struct XVArrayArray_XVPoint2D
{
    XVOptionalType              optional = NUL;
    vector<XVArray_XVPoint2D>   array;
};

#endif
