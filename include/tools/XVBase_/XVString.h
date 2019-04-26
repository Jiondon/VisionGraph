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


typedef XVString XVFile;

#endif // XVSTRING_H
