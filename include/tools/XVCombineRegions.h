#ifndef XVCOMBINEREGIONS_H
#define XVCOMBINEREGIONS_H

#ifdef XVCOMBINEREGIONS_LIBRARY
#define MAKEDLL_API extern "C" __declspec(dllexport)
#else
#define MAKEDLL_API extern "C" __declspec(dllimport)
#endif

#include "XVBase.h"

enum XVCombineRegionsType
{
    Difference,                     //region1-region2
    //    Symmetricdiffence,
    SymmetricDifference,            //并集-交集
    Intersection,                   //交集
    Union,                          //并集
    SymmetricDifference_ofArray,    //数组版 并集-交集
    Intersection_ofArray,           //数组版交集
    Union_ofArray                   //数组版并集
};


typedef struct XVCombineRegionsIn
{
    XVCombineRegionsType   inCombineRegionsType;
    XVRegion               inRegion1; //Difference / SymmetricDifference / Intersection / Union
    XVRegion               inRegion2; //Difference / SymmetricDifference / Intersection / Union

    //combine Region of Array
    XVRegion         inInitialRegion;//Intersection_ofArray
    vector<XVRegion> inRegionArray;  //Intersection_ofArray / SymmetricDifference_ofArray / Union_ofArray
}XVCombineRegionsIn;

typedef struct XVCombineRegionsOut
{
    XVRegion RegionOut;
}XVCombineRegionsOut;

MAKEDLL_API void XVCombineRegions(XVCombineRegionsIn& in, XVCombineRegionsOut& out);

#endif // XVCOMBINEREGIONS_H
