#ifndef XVIMAGEARRAY_H
#define XVIMAGEARRAY_H

#include "XVImage.h"


struct XVArray_XVImage
{
    XVOptionalType  optional = NUL;
    vector<XVImage> array;
};

struct XVArray_XVExtremum2D
{
    XVOptionalType       optional = NUL;
    vector<XVExtremum2D> array;
};

#endif // ARRAY
