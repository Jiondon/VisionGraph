#ifndef XVREGIONLOGIC_H
#define XVREGIONLOGIC_H
#include "xvregionanalysis_global.h"
#include "XVRegionArray.h"
#include "XVBaseTypeArray.h"
#include "XVPathArray.h"
#include "XVRegionFeatureType.h"


namespace XVSortingOrder
{
    enum Type
    {
        Ascending,
        Descending
    };
}

namespace XVMatchingCriterion
{
    enum Type
    {
        Intersection,
        Inclusion
    };
}


/// <summary>Splits an array of regions according to the selected feature and range.</summary>
/// <param name="inRegions">Input regions.</param>
/// <param name="inFeature">Region feature value to be computed.</param>
/// <param name="inMinimum">Lowest value of the range. Default value: atl::NIL.</param>
/// <param name="inMaximum">Highest value of the range. Default value: atl::NIL.</param>
/// <param name="outAccepted">Regions with feature values matching the range.</param>
/// <param name="outRejected">Regions with feature values outside the range.</param>
/// <param name="outBelow">Regions with feature values lower than inMinimum.</param>
/// <param name="outAbove">Regions with feature values higher than inMaximum.</param>
/// <param name="outValues">Computed feature values.</param>
struct XVClassifyRegionsIn
{
    XVArray_XVRegion        inRegions   ;
    XVRegionFeature::Type   inFeature   ;
    XVFloat                 inMinimum   ;
    XVFloat                 inMaximum   ;
};
struct XVClassifyRegionsOut
{
    XVArray_XVRegion        outAccepted ;
    XVArray_XVRegion        outRejected ;
    XVArray_XVRegion        outBelow    ;
    XVArray_XVRegion        outAbove    ;
    XVArray_XVFloat         outValues   ;
};


/// <summary>Computes region feature and checks whether its value is in range.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inFeature">Region feature value to be computed.</param>
/// <param name="inMinimum">Lowest value of the range. Default value: atl::NIL.</param>
/// <param name="inMaximum">Highest value of the range. Default value: atl::NIL.</param>
/// <param name="outConditionalRegion">The region if the condition is met or nothing otherwise.</param>
struct XVMakeRegionConditionalIn
{
    XVRegion                inRegion             ;
    XVRegionFeature::Type   inFeature            ;
    XVFloat                 inMinimum            ;
    XVFloat                 inMaximum            ;
};
struct XVMakeRegionConditionalOut
{
XVRegion                outConditionalRegion ;
};

/// <summary>Changes the order of regions from the input array accordingly to an ascending/descending sequence of their computed feature values.</summary>
/// <param name="inRegions">Input regions.</param>
/// <param name="inFeature">Region feature value to be computed.</param>
/// <param name="inSortingOrder">Sorting order.</param>
/// <param name="outSortedRegions">Regions sorted according to the computed feature values.</param>
/// <param name="outSortedValues">Computed feature values.</param>
struct XVSortRegionsIn
{
    XVArray_XVRegion        inRegions        ;
    XVRegionFeature::Type   inFeature        ;
    XVSortingOrder::Type    inSortingOrder   ;
};
struct XVSortRegionsOut{
    XVArray_XVRegion        outSortedRegions ;
    XVArray_XVFloat         outSortedValues  ;
};

/// <summary>Returns the region from the input array that corresponds to the smallest computed feature value; returns NIL if the array or any region inside it is empty.</summary>
/// <param name="inRegions">Input regions.</param>
/// <param name="inFeature">Region feature value to be computed.</param>
/// <param name="outRegion">Output region.</param>
/// <param name="outValue">Computed feature value of the output region.</param>
struct XVGetMinimumRegionIn
{
    XVArray_XVRegion        inRegions ;
    XVRegionFeature::Type   inFeature ;
};
struct XVGetMinimumRegionOut
{
    XVRegion                outRegion ;
    XVFloat                 outValue  ;
    XVInt                   outIndex  ;
};

/// <summary>Returns the region from the input array that corresponds to the largest computed feature value; returns NIL if the array or any region inside it is empty.</summary>
/// <param name="inRegions">Input regions.</param>
/// <param name="inFeature">Region feature value to be computed.</param>
/// <param name="outRegion">Output region.</param>
/// <param name="outValue">Computed feature value of the output region.</param>
struct XVGetMaximumRegionIn
{
    XVArray_XVRegion        inRegions ;
    XVRegionFeature::Type   inFeature ;
};
struct XVGetMaximumRegionOut
{
    XVRegion                outRegion ;
    XVFloat                 outValue  ;
    XVInt                   outIndex  ;
};


/// <summary>For each region returns which points lie inside of it.</summary>
struct XVGroupPointsByRegionsIn
{
    XVArray_XVPoint2D       inPoints          ;
    XVArray_XVRegion        inRegions         ;
};
struct XVGroupPointsByRegionsOut
{
    XVArrayArray_XVInt      outGroupedIndices ;
    XVArrayArray_XVPoint2D  outGroupedPoints  ;
};

/// <summary>For each region returns which paths lie inside of it or intersect with it.</summary>
/// <param name="inPaths">Array of paths that will be classified into multiple groups.</param>
/// <param name="inRegions">Array of regions that define the groups.</param>
/// <param name="inMatchingCriterion">Specifies whether a path must fully belong to a group region or if it is enough that it intersects.</param>
/// <param name="outGroupedIndices">Indices of input paths classified into multiple groups.</param>
/// <param name="outGroupedPaths">Input paths classified into multiple groups.</param>
struct XVGroupPathsByRegionsIn
{
    XVArray_XVPath              inPaths             ;
    XVArray_XVRegion            inRegions           ;
    XVMatchingCriterion::Type   inMatchingCriterion ;
};
struct XVGroupPathsByRegionsOut
{
    XVArrayArray_XVInt          outGroupedIndices   ;
    XVArrayArray_XVPath         outGroupedPaths     ;
};

/// <summary>For each region returns which regions lie inside of it or intersect with it.</summary>
/// <param name="inRegions">Array of regions that will be classified into multiple groups.</param>
/// <param name="inGroupRegions">Array of regions that define the groups.</param>
/// <param name="inMatchingCriterion">Specifies whether a region must fully belong to a group region or if it is enough that it intersects.</param>
/// <param name="outGroupedIndices">Indices of input regions classified into multiple groups.</param>
/// <param name="outGroupedRegions">Input regions classified into multiple groups.</param>
struct XVGroupRegionsByRegionsIn
{
    XVArray_XVRegion            inRegions           ;
    XVArray_XVRegion            inGroupRegions      ;
    XVMatchingCriterion::Type   inMatchingCriterion ;
};
struct XVGroupRegionsByRegionsOut
{
    XVArrayArray_XVInt          outGroupedIndices   ;
    XVArrayArray_XVRegion       outGroupedRegions   ;
};


MAKEDLL_API void XVClassifyRegions      (XVClassifyRegionsIn        &in, XVClassifyRegionsOut       &out)throw(...);
MAKEDLL_API void XVMakeRegionConditional(XVMakeRegionConditionalIn  &in, XVMakeRegionConditionalOut &out)throw(...);
MAKEDLL_API void XVSortRegions          (XVSortRegionsIn            &in, XVSortRegionsOut           &out)throw(...);
MAKEDLL_API void XVGetMinimumRegion     (XVGetMinimumRegionIn       &in, XVGetMinimumRegionOut      &out)throw(...);
MAKEDLL_API void XVGetMaximumRegion     (XVGetMaximumRegionIn       &in, XVGetMaximumRegionOut      &out)throw(...);

MAKEDLL_API void XVGroupPointsByRegions (XVGroupPointsByRegionsIn   &in, XVGroupPointsByRegionsOut  &out)throw(...);
MAKEDLL_API void XVGroupPathsByRegions  (XVGroupPathsByRegionsIn    &in, XVGroupPathsByRegionsOut   &out)throw(...);
MAKEDLL_API void XVGroupRegionsByRegions(XVGroupRegionsByRegionsIn  &in, XVGroupRegionsByRegionsOut &out)throw(...);


#endif // XVREGIONLOGIC_H
