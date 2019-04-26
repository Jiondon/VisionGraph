#ifndef XVMETRIC_H
#define XVMETRIC_H

#include "XVOptional.h"


enum XVMetricType   // Two-point distance calculation method
{
    Taxi,           // Rectilinear distance
    Maximum,        // Chebyshev distance
    Euclidean       // Euclidean metric distance
};

struct XVMetric
{
    XVOptionalType      optional = NUL;
    XVMetricType        type = XVMetricType::Maximum;
};

#endif // XVMETRIC_H
