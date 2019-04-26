#ifndef XVMESTIMATOR_H
#define XVMESTIMATOR_H

#include "XVOptional.h"

enum XVMEstimatorType
{
    Huber,
    Tukey
};

struct XVMEstimator
{
    XVOptionalType      optional = NUL;
    XVMEstimatorType    type;
};

#endif // XVENUM_H
