#ifndef XVBASETYPE_H
#define XVBASETYPE_H

#include "XVOptional.h"

struct XVInt
{
    XVOptionalType  optional = NUL;
    int             value;
};

struct XVFloat
{
    XVOptionalType  optional = NUL;
    float           value;
};

struct XVBool
{
    XVOptionalType  optional = NUL;
    bool            value;
};

struct XVPoint2D
{
    XVOptionalType optional = NUL;
    float x;
    float y;
};


#endif // XVBASETYPE_H
