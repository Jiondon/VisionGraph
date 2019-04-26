#ifndef XVCOMBINEREGIONS_H
#define XVCOMBINEREGIONS_H

#include "xvregionanalysis_global.h"
#include "XVRegionArray.h"


struct TwoRegionIn
{
    XVRegion     inRegion1 ;
    XVRegion     inRegion2 ;
};

/// <summary>Computes the common part of two regions.</summary>
/// <param name="inRegion1">First input region.</param>
/// <param name="inRegion2">Second input region.</param>
/// <param name="outRegion">Output region.</param>
typedef TwoRegionIn XVRegionIntersectionIn;
typedef RegionOut XVRegionIntersectionOut;


/// <summary>Computes a region containing pixels from the first input region  but not from the second input region.</summary>
/// <param name="inRegion1">First input region.</param>
/// <param name="inRegion2">Second input region.</param>
/// <param name="outRegion">Output region.</param>
typedef TwoRegionIn XVRegionDifferenceIn;
typedef RegionOut XVRegionDifferenceOut;

/// <summary>Computes a region containing pixels from both input regions.</summary>
/// <param name="inRegion1">First input region.</param>
/// <param name="inRegion2">Second input region.</param>
/// <param name="outRegion">Output region.</param>
typedef TwoRegionIn XVRegionUnionIn;
typedef RegionOut XVRegionUnionOut;

/// <summary>Computes a region containing pixels from first or second input region  but not from both.</summary>
/// <param name="inRegion1">First input region.</param>
/// <param name="inRegion2">Second input region.</param>
/// <param name="outRegion">Output region.</param>
typedef TwoRegionIn XVRegionSymmetricDifferenceIn;
typedef RegionOut XVRegionSymmetricDifferenceOut;

/// <summary>Computes a region containing pixels belonging to odd number of array regions.</summary>
/// <param name="outRegion">Output region.</param>
struct XVRegionSymmetricDifference_OfArrayIn
{
    XVArray_XVRegion         inRegionArray ;
};
typedef RegionOut XVRegionSymmetricDifference_OfArrayOut;

/// <summary>Computes a region containing all the pixels that any of the input regions contains.</summary>
/// <param name="inArray">Array of regions.</param>
/// <param name="outRegion">Union of the input regions.</param>
struct XVRegionUnion_OfArrayIn
{
    XVArray_XVRegion        	inArray   ;
};
typedef RegionOut XVRegionUnion_OfArrayOut;


/// <summary>Computes common part of array of regions.</summary>
/// <param name="outRegion">Output region.</param>
struct XVRegionIntersection_OfArrayIn
{
    XVRegion                   	inInitialRegion ;
    XVArray_XVRegion        	inArray         ;
};
typedef RegionOut XVRegionIntersection_OfArrayOut;




MAKEDLL_API void XVRegionDifference                 (XVRegionDifferenceIn                  &in, XVRegionDifferenceOut                  &out)throw(...);//region1-region2
MAKEDLL_API void XVRegionIntersection               (XVRegionIntersectionIn                &in, XVRegionIntersectionOut                &out)throw(...);//交集
MAKEDLL_API void XVRegionUnion                      (XVRegionUnionIn                       &in, XVRegionUnionOut                       &out)throw(...);//并集
MAKEDLL_API void XVRegionSymmetricDifference        (XVRegionSymmetricDifferenceIn         &in, XVRegionSymmetricDifferenceOut         &out)throw(...);//并集-交集
MAKEDLL_API void XVRegionIntersection_OfArray       (XVRegionIntersection_OfArrayIn        &in, XVRegionIntersection_OfArrayOut        &out)throw(...);//数组版交集
MAKEDLL_API void XVRegionUnion_OfArray              (XVRegionUnion_OfArrayIn               &in, XVRegionUnion_OfArrayOut               &out)throw(...);//数组版并集
MAKEDLL_API void XVRegionSymmetricDifference_OfArray(XVRegionSymmetricDifference_OfArrayIn &in, XVRegionSymmetricDifference_OfArrayOut &out)throw(...);//数组版 并集-交集




#endif // XVCOMBINEREGIONS_H
