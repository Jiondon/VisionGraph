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

static void CopyArray_XVPath(const XVArray_XVPath& src, XVArray_XVPath& dest){
    dest.optional = src.optional;
    dest.array.clear();
    for(auto c : src.array)
    {
        XVPath tmp;
        CopyXVPath(c,tmp);
        dest.array.push_back(tmp);
    }
}

struct XVArrayArray_XVPath
{
    XVOptionalType          optional = NUL;
    vector<XVArray_XVPath>  array;
};

static void CopyArrayArray_XVPath(const XVArrayArray_XVPath& src, XVArrayArray_XVPath& dest){
    dest.optional = src.optional;
    dest.array.clear();
    for(auto c : src.array)
    {
        XVArray_XVPath tmp;
        CopyArray_XVPath(c,tmp);
        dest.array.push_back(tmp);
    }
}

#endif // XVPATH_H
