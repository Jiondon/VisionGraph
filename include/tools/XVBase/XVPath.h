#ifndef XVPATH_H
#define XVPATH_H

#include "XVBaseType.h"
#include "XVGlobal.h"

//路径或者链条
struct XVPath
{
    XVOptionalType      optional = NUL;
    vector< XVPoint2D > arrayPoint2D;
    bool                closed   = false;
};

static void CopyXVPath(const XVPath& src, XVPath& dest){
    dest.optional = src.optional;
    dest.closed   = src.closed;
    dest.arrayPoint2D.clear();
    for(auto c : src.arrayPoint2D)
        dest.arrayPoint2D.push_back(c);
}

#endif // XVPATH_H
