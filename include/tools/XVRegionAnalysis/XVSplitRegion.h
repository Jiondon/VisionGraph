#ifndef XVSPLITREGION_H
#define XVSPLITREGION_H

#include "xvregionanalysis_global.h"
#include "XVRegionConnectivity.h"
#include "XVBaseTypeArray.h"
#include "XVRegionArray.h"
#include "XVProfile.h"

/// <summary>Splits a region into an array of regions corresponding to its connected components.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inConnectivity">Type of connectivity used for the region foreground.</param>
/// <param name="inMinBlobArea">Minimal area of a resulting blob. Default value: 1.</param>
/// <param name="inMaxBlobArea">Maximal area of a resulting blob. Default value: atl::NIL.</param>
/// <param name="inRemoveBoundaryBlobs">Flag indicating whether the blobs on border of the input region should be removed or not. Default value: False.</param>
/// <param name="diagBlobAreas">Areas of extracted blobs.</param>
struct XVSplitRegionIntoBlobsIn
{
    XVRegion                    inRegion               ;
    XVRegionConnectivity::Type	inConnectivity         ;        //用于区域前景的连接类型。
    int                         inMinBlobArea          = 1;     //生成的blob的最小面积
    XVInt                       inMaxBlobArea          ;        //生成的blob的最大面积
    bool						inRemoveBoundaryBlobs  = false; //指示是否应删除输入区域边界上的小块
};
struct XVSplitRegionIntoBlobsOut
{
    XVArray_XVRegion            outBlobs               ;
    XVArray_XVInt 				diagBlobAreas          ;
};

/// <summary>Splits a region into an array of regions corresponding to its connected components.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inMinArea">Default value: 20.</param>
struct XVSplitRegionIntoBlobs_CarbonIn
{
    XVRegion                    inRegion       ;
    XVRegionConnectivity::Type	inConnectivity ;
    int							inMinArea      = 20;
    XVInt                       inMaxArea      ;
};
struct XVSplitRegionIntoBlobs_Carbonout
{
    XVArray_XVRegion            outBlobs       ;
};

/// <summary>Splits a region into an array of regions. Operates by merging blobs in accordance to the inMaxDistance parameter.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inMaxDistance">Default value: 5.</param>
/// <param name="inDistanceBalance">Defines how much important the distance between regions in x coordinate is according to distance in y coordinate.</param>
/// <param name="inMinComponentArea">Minimal area of a resulting component. Default value: 1.</param>
/// <param name="inMaxComponentArea">Maximal area of a resulting component. Default value: atl::NIL.</param>
/// <param name="inRemoveBoundaryBlobs">Flag indicating whether the blobs on border of the input region should be removed or not. Default value: False.</param>
struct XVSplitRegionIntoComponentsIn
{
    XVRegion            inRegion               ;
    XVInt               inMaxDistance          ;        //5
    float               inDistanceBalance      ;        //
    XVFloat             inMaxJointDiameter     ;        //
    XVInt               inMaxJointWidth        ;        //
    XVInt               inMaxJointHeight       ;        //
    int                 inMinComponentArea     = 1;     //1
    XVInt               inMaxComponentArea     ;        //NUL
    bool                inRemoveBoundaryBlobs  = false; //false;
};
struct XVSplitRegionIntoComponentsOut
{
    XVArray_XVRegion    outComponents          ;
};

/// <summary>Splits a region into a fixed-size array of regions.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inMaxDistance">Default value: 5.</param>
/// <param name="inDistanceBalance">Defines how much important the distance between regions in x coordinate is according to distance in y coordinate.</param>
/// <param name="inRemoveBoundaryBlobs">Flag indicating whether the blobs on border of the input region should be removed or not. Default value: False.</param>
struct XVSplitRegionIntoExactlyNComponentsIn
{
    XVRegion            inRegion              ;
    int                 inComponentCount      ;
    XVInt               inMaxDistance         ;     //5
    float               inDistanceBalance     ;
    XVFloat             inMaxJointDiameter    ;
    XVInt               inMaxJointWidth       ;
    XVInt               inMaxJointHeight      ;
    bool                inRemoveBoundaryBlobs = false;
};
typedef XVSplitRegionIntoComponentsOut XVSplitRegionIntoExactlyNComponentsOut;


struct XVSplitRegionIntoCharactersOut
{
    XVArray_XVRegion	outRegions         ;
    XVArray_XVRegion	diagClasses        ;
    XVProfile 			diagProjection     ;
};

/// <summary>Splits the input region into an array of regions corresponding to individual characters.</summary>
/// <param name="inRegion">Input region containing characters.</param>
/// <param name="inProjectionSmooth">Value of smooth applied to region projection before splitting into separated characters. Default value: 1.0f.</param>
/// <param name="inCharacterWidth">Single character width. Default value: 15.</param>
/// <param name="outRegions">Array or regions containing single characters.</param>
/// <param name="diagClasses">Regions in which characters parts will be connected into a single character region.</param>
/// <param name="diagProjection">Profile of region projection used to distinguish characters.</param>
struct XVSplitRegionIntoMultipleCharactersIn
{
    XVRegion 			inRegion           ;
    float               inProjectionSmooth = 1.0f;
    int 				inCharacterWidth   = 15;
};
typedef XVSplitRegionIntoCharactersOut XVSplitRegionIntoMultipleCharactersOut;

/// <summary>Splits the input region into a fixed-size array of regions corresponding to individual characters.</summary>
/// <param name="inRegion">Region which contains characters.</param>
/// <param name="inCharacterCount">Character count in provided region.</param>
/// <param name="inCharacterSpacing">Spacing size between characters.</param>
/// <param name="inProjectionSmooth">Projection smoothing value used to remove noises from character region. Default value: 1.0f.</param>
/// <param name="outRegions">Output array of regions containing separated characters.</param>
/// <param name="diagClasses">Regions that contain location of split characters.</param>
/// <param name="diagProjection">Profile of region projection used to distinguish characters.</param>
struct XVSplitRegionIntoExactlyNCharactersIn
{
    XVRegion            inRegion           ;
    int 				inCharacterCount   ;
    int 				inCharacterSpacing ;
    float 				inProjectionSmooth = 1.0f;
};
typedef XVSplitRegionIntoCharactersOut XVSplitRegionIntoExactlyNCharactersOut;



MAKEDLL_API void XVSplitRegionIntoBlobs             (XVSplitRegionIntoBlobsIn               &in, XVSplitRegionIntoBlobsOut              &out)throw(...);//将一个区域分割为一系列与其连接的组件相对应的区域
MAKEDLL_API void XVSplitRegionIntoBlobs_Carbon      (XVSplitRegionIntoBlobs_CarbonIn        &in, XVSplitRegionIntoBlobs_Carbonout       &out)throw(...);//同上
MAKEDLL_API void XVSplitRegionIntoComponents        (XVSplitRegionIntoComponentsIn          &in, XVSplitRegionIntoComponentsOut         &out)throw(...);//将一个区域分割为一系列区域。操作方法是根据inMaxDistance参数合并blob
MAKEDLL_API void XVSplitRegionIntoExactlyNComponents(XVSplitRegionIntoExactlyNComponentsIn  &in, XVSplitRegionIntoExactlyNComponentsOut &out)throw(...);//将一个区域分割为一个固定大小的区域数组
MAKEDLL_API void XVSplitRegionIntoMultipleCharacters(XVSplitRegionIntoMultipleCharactersIn  &in, XVSplitRegionIntoMultipleCharactersOut &out)throw(...);//将输入区域分割为与单个字符对应的区域数组
MAKEDLL_API void XVSplitRegionIntoExactlyNCharacters(XVSplitRegionIntoExactlyNCharactersIn  &in, XVSplitRegionIntoExactlyNCharactersOut &out)throw(...);//将输入区域分割为与单个字符对应的固定大小的区域数组



#endif // XVSPLITREGION_H
