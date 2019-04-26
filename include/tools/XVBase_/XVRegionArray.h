#ifndef XVREGIONARRAY_H
#define XVREGIONARRAY_H

#include "XVRegion.h"

struct XVArray_XVRegion
{
    XVOptionalType  optional = NUL;
    vector< XVRegion > array;
};

struct XVArrayArray_XVRegion
{
    XVOptionalType  optional = NUL;
    vector<XVArray_XVRegion> array;
};


#endif // XVENUM_H
