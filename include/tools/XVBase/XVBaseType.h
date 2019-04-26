#ifndef XVBASETYPE_H
#define XVBASETYPE_H

#include "XVOptional.h"

struct XVInt
{
    XVOptionalType  optional = NUL;
    int             value = 0;
};

struct XVFloat
{
    XVOptionalType  optional = NUL;
    float           value = 0.0f;
};

struct XVBool
{
    XVOptionalType  optional = NUL;
    bool            value = false;
};

struct XVPoint2D
{
    XVOptionalType optional = NUL;
    float x = 0.0f;
    float y = 0.0f;
};


#endif // XVBASETYPE_H
