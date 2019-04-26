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


static void CopyArray_XVRegion(const XVArray_XVRegion& src, XVArray_XVRegion& dest){
    dest.optional = src.optional;
    dest.array.clear();
    for(auto c : src.array)
    {
        XVRegion tmp;
        CopyXVRegion(c,tmp);
        dest.array.push_back(tmp);
    }
}
static void CopyArrayArray_XVRegion(const XVArrayArray_XVRegion& src, XVArrayArray_XVRegion& dest){
    dest.optional = src.optional;
    dest.array.clear();
    for(auto c : src.array)
    {
        XVArray_XVRegion tmp;
        CopyArray_XVRegion(c,tmp);
        dest.array.push_back(tmp);
    }
}

#endif // XVENUM_H
