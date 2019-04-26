#ifndef XVREGIONANALYSIS_GLOBAL_H
#define XVREGIONANALYSIS_GLOBAL_H


#ifdef XVREGIONANALYSIS_LIBRARY
#define MAKEDLL_API extern "C" __declspec(dllexport)
#else
#define MAKEDLL_API extern "C" __declspec(dllimport)
#endif

#include "XVRegion.h"


struct RegionIn
{
    XVRegion    inRegion;
};

struct RegionOut{
    XVRegion    outRegion;
};

#endif // XVREGIONANALYSIS_GLOBAL_H
