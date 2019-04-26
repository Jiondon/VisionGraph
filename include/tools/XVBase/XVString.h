#ifndef XVSTRING_H
#define XVSTRING_H

#include "XVGlobal.h"
#include <string>

struct XVString
{
    XVOptionalType optional = NUL;
    string         value;
};

struct XVArray_XVString
{
    XVOptionalType   optional = NUL;
    vector<XVString> array;
};

static void CopyArray_XVString(const XVArray_XVString& src, XVArray_XVString& dest)
{
    dest.optional = src.optional;
    dest.array.clear();
    for(auto c : src.array)
    {
        dest.array.push_back(c);
    }
}


typedef XVString XVFile;

#endif // XVSTRING_H
