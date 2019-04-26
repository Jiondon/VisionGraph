#ifndef XVTESTREGION_H
#define XVTESTREGION_H

#include "xvregionanalysis_global.h"

/// <summary>Tests whether a region is adjacent to its border.</summary>
/// <param name="inRegion">Input region.</param>

typedef RegionIn XVTestRegionOnBorderIn;
struct XVTestRegionOnBorderOut
{
    bool                outIsOnBorder ;
};


/// <summary>Tests whether the size of a region equals zero.</summary>
/// <param name="inRegion">Input region.</param>
typedef RegionIn XVTestRegionEmptyIn;
struct XVTestRegionEmptyOut
{
    bool 				outIsEmpty ;
};


/// <summary>Tests whether the size of a region doesn't equal zero.</summary>
/// <param name="inRegion">Input region.</param>
typedef RegionIn XVTestRegionNotEmptyIn;
struct XVTestRegionNotEmptyOut
{
    bool 				outIsNotEmpty ;
};


/// <summary>Checks if the input region has well sorted  not overlapping and in-range point-runs.</summary>
/// <param name="inRegion">Input region.</param>
typedef RegionIn XVTestRegionValidIn;
struct XVTestRegionValidOut
{
    bool 				outIsValid  ;
};

struct XVTestRegionIn
{
    XVRegion            inRegion          ;
    XVRegion            inReferenceRegion ;
};

/// <summary>Tests whether given regions are equal.</summary>
/// <param name="inRegion">Input region.</param>
typedef XVTestRegionIn XVTestRegionEqualToIn;
struct XVTestRegionEqualToOut
{
    bool 				outIsEqual        ;
};


/// <summary>Tests whether given regions are not equal.</summary>
/// <param name="inRegion">Input region.</param>
typedef XVTestRegionIn XVTestRegionUnequalToIn;
struct XVTestRegionUnequalToOut
{
    bool 				outIsUnequal      ;
};


/// <summary>Tests whether two regions have non-empty intersection.</summary>
/// <param name="inRegion">Input region.</param>
typedef XVTestRegionIn XVTestRegionIntersectsWithIn;
struct XVTestRegionIntersectsWithOut
{
    bool 				outRegionsIntersect ;
};


/// <summary>Tests whether a region is contained in another one.</summary>
/// <param name="inRegion">Input region.</param>
struct XVTestRegionInRegionIn
{
    XVRegion            inSubregion    ;
    XVRegion            inRegion       ;
};
struct XVTestRegionInRegionOut
{
    bool                outIsContained ;
};


MAKEDLL_API void XVTestRegionOnBorder       (XVTestRegionOnBorderIn        &in, XVTestRegionOnBorderOut        &out)throw(...);
MAKEDLL_API void XVTestRegionEmpty          (XVTestRegionEmptyIn           &in, XVTestRegionEmptyOut           &out)throw(...);
MAKEDLL_API void XVTestRegionNotEmpty       (XVTestRegionNotEmptyIn        &in, XVTestRegionNotEmptyOut        &out)throw(...);
MAKEDLL_API void XVTestRegionValid          (XVTestRegionValidIn           &in, XVTestRegionValidOut           &out)throw(...);
MAKEDLL_API void XVTestRegionEqualTo        (XVTestRegionEqualToIn         &in, XVTestRegionEqualToOut         &out)throw(...);
MAKEDLL_API void XVTestRegionUnequalTo      (XVTestRegionUnequalToIn       &in, XVTestRegionUnequalToOut       &out)throw(...);
MAKEDLL_API void XVTestRegionIntersectsWith (XVTestRegionIntersectsWithIn  &in, XVTestRegionIntersectsWithOut  &out)throw(...);
MAKEDLL_API void XVTestRegionInRegion       (XVTestRegionInRegionIn        &in, XVTestRegionInRegionOut        &out)throw(...);

#endif // XVTESTREGION_H
