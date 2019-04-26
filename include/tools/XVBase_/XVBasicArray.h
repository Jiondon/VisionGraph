#ifndef XVBASICARRAY_H
#define XVBASICARRAY_H

#include "XVGlobal.h"
#include "XVBasic.h"

struct XVArray_XVLocation{
    XVOptionalType      optional = NUL;
    vector<XVLocation>  array;
};

struct XVArray_XVPixel{
    XVOptionalType  optional = NUL;
    vector<XVPixel> array;
};


#endif // XVBASIC_H
