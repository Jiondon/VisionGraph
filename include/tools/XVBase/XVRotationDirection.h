#ifndef XVROTATIONDIRECTION_H
#define XVROTATIONDIRECTION_H

#include "XVOptional.h"

enum XVRotationDirectionType
{
    Clockwise,          //顺时针
    CounterClockwise    //逆时针
};

struct XVRotationDirection
{
    XVOptionalType          optional = NUL;
    XVRotationDirectionType type = XVRotationDirectionType::Clockwise;
};

#endif // XVROTATIONDIRECTION_H
