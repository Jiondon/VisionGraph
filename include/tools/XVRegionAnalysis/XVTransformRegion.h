#ifndef XVTRANSFORMREGION_H
#define XVTRANSFORMREGION_H
#include "xvregionanalysis_global.h"
#include "XVBasic.h"
#include "XVEnums/XVMirrorDirection.h"
#include "XVEnums/XVAxis.h"
#include "XVRegionConnectivity.h"
#include "XVRegionFeatureType.h"

/// <summary>Mirrors a region across vertical or horizontal axis.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inMirrorDirection">Reverse the order of region columns {horizontal direction}; or rows {vertical direction};. Default value: Horizontal.</param>
/// <param name="outRegion">Output region.</param>
struct XVMirrorRegionIn
{
    XVRegion    				inRegion          ;
    XVMirrorDirection::Type     inMirrorDirection ;
};
typedef RegionOut XVMirrorRegionOut;

/// <summary>Translates a region by a given number of pixels along each axis.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inDeltaX">Horizontal shift.</param>
/// <param name="inDeltaY">Vertical shift.</param>
/// <param name="inInverse">Negates the delta values.</param>
/// <param name="inFrameWidth">Output region frame width. Default value: atl::NIL.</param>
/// <param name="inFrameHeight">Output region frame height. Default value: atl::NIL.</param>
/// <param name="outRegion">Output region.</param>
struct XVTranslateRegionIn
{
    XVRegion                inRegion      ;
    int						inDeltaX      ;
    int						inDeltaY      ;
    bool					inInverse     ;
    XVInt             		inFrameWidth  ;
    XVInt             		inFrameHeight ;
};
typedef RegionOut XVTranslateRegionOut;

/// <summary>Enlarges a region by a natural factor.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inN">The scaling coefficient. Default value: 2.</param>
/// <param name="outRegion">Output region.</param>
struct XVEnlargeRegionNTimesIn
{
    XVRegion            inRegion  ;
    int					inN       ;
};
typedef RegionOut XVEnlargeRegionNTimesOut;

/// <summary>Flips and rotates a region so that x-coordinates are exchanged with y-coordinates.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="outRegion">Output region.</param>
typedef RegionIn XVTransposeRegionIn;
typedef RegionOut XVTransposeRegionOut;

/// <summary>Reflects a region through the given location.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="outRegion">Output region.</param>
struct XVReflectRegionIn
{
    XVRegion    		inRegion           ;
    XVLocation          inReflectionCenter ;
};
typedef RegionOut XVReflectRegionOut;

/// <summary>Rotates a region around a point.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inCenter">Center of rotation. Default value: atl::NIL.</param>
/// <param name="inAngle">Clockwise rotation angle.</param>
/// <param name="inInverse">Switches to counter-clockwise rotation.</param>
/// <param name="inFrameWidth">Output region frame width. Default value: atl::NIL.</param>
/// <param name="inFrameHeight">Output region frame height. Default value: atl::NIL.</param>
/// <param name="outRegion">Output region.</param>
struct XVRotateRegionIn
{
    XVRegion    					inRegion      ;
    XVPoint2D                       inCenter      ;
    float							inAngle       ;
    bool							inInverse     ;
    XVInt                           inFrameWidth  ;
    XVInt                           inFrameHeight ;
};
typedef RegionOut XVRotateRegionOut;

/// <summary>Computes a leant region.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inShear">The relative shift of each consecutive row or column.</param>
/// <param name="inAxis">Switches between shifting rows or columns.</param>
/// <param name="outRegion">Output region.</param>
struct XVShearRegionIn
{
    XVRegion            inRegion  ;
    float               inShear   ;
    XVAxis::Type		inAxis    ;
};
typedef RegionOut XVShearRegionOut;

/// <summary>Creates a region from a rectangular fragment of another one.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inSelection">Box defining the range of cropping.</param>
/// <param name="outRegion">Output region.</param>
struct XVCropRegionIn
{
    XVRegion            inRegion     ;
    XVBox               inSelection  ;
};
typedef RegionOut XVCropRegionOut;

/// <summary>Inverse of CropRegion</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inSelection">Box defining the range of the original cropping.</param>
/// <param name="inWidth">Width of the uncropped region.</param>
/// <param name="inHeight">Height of the uncropped region.</param>
/// <param name="outRegion">Output region.</param>
struct XVUncropRegionIn
{
    XVRegion            inRegion    ;
    XVBox               inSelection ;
    int					inWidth     ;
    int					inHeight    ;
};
typedef RegionOut XVUncropRegionOut;

/// <summary>Creates a region from a rectangular fragment of another one.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inRectangle">Rectangle defining a rotated subregion.</param>
/// <param name="inRectangleAlignment">Adjusts the rectangle to the position of the inspected object. Default value: atl::NIL.</param>
/// <param name="outRegion">Output region.</param>
/// <param name="outAlignedRectangle">Input rectangle after transformation {in the region coordinates};.</param>
/// <param name="outOutputAlignment">Alignment of the output region.</param>
struct XVCropRegionToRectangleIn
{
    XVRegion                inRegion             ;
    XVRectangle2D           inRectangle          ;
    XVCoordinateSystem2D    inRectangleAlignment ;
};
struct XVCropRegionToRectangleOut
{
    XVRegion    			outRegion            ;
    XVRectangle2D           outAlignedRectangle  ;
    XVCoordinateSystem2D    outOutputAlignment   ;
};

/// <summary>Enlarges or shrinks a region to new dimensions.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="outRegion">Output region.</param>
struct XVResizeRegionIn
{
    XVRegion            inRegion    ;
    XVInt             	inNewWidth  ;
    XVInt             	inNewHeight ;
};
typedef RegionOut XVResizeRegionOut;

/// <summary>Resizes region relatively along each axis.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inHorizontalScale">Default value: 1.0f.</param>
/// <param name="inVerticalScale">Default value: 1.0f.</param>
/// <param name="outRegion">Output region.</param>
struct XVResizeRegion_RelativeIn
{
    XVRegion    	inRegion          ;
    float			inHorizontalScale ;
    float			inVerticalScale   ;
};
typedef RegionOut XVResizeRegion_RelativeOut;

/// <summary>Aligns a region to a coordinate system.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inAlignment">Coordinate system to align to.</param>
/// <param name="inInverse">Switches to the inverse transform.</param>
/// <param name="inFrameWidth">Output region's frame width. Default value: atl::NIL.</param>
/// <param name="inFrameHeight">Output region's frame height. Default value: atl::NIL.</param>
struct XVAlignRegionIn
{
    XVRegion                    inRegion          ;
    XVCoordinateSystem2D    	inAlignment       ;
    bool                        inInverse         ;
    XVInt                       inFrameWidth      ;
    XVInt                       inFrameHeight     ;

};
struct XVAlignRegionOut
{
    XVRegion                    outAlignedRegion  ;
};

namespace XVDownsampleRegionMode
{
enum Type
{
    Any,
    All
};
}

/// <summary>Shrinks a region by the factor of two along each axis.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inScaleStep">Defines how many times the region size is divided by 2. Default value: 1.</param>
/// <param name="outRegion">Output region.</param>
struct XVDownsampleRegionIn
{
    XVRegion                        inRegion               ;
    XVDownsampleRegionMode::Type	inDownsampleRegionMode ;
    int                             inScaleStep            ;
};
typedef RegionOut XVDownsampleRegionOut;

/// <summary>Removes regions not fulfilling specific conditions</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inConnectivity">Type of connectivity used for the region foreground.</param>
/// <param name="inFeature">Region feature value to be computed.</param>
/// <param name="inMinimum">Minimal value of the considered feature. Default value: 1.0f.</param>
/// <param name="inMaximum">Maximal value of the considered feature. Default value: atl::NIL.</param>
/// <param name="inRemoveBoundaryBlobs">Flag indicating whether the blobs on border of the input region should be removed or not. Default value: False.</param>
/// <param name="outRegion">Output region.</param>
struct XVRemoveRegionBlobsIn
{
    XVRegion                    inRegion              ;
    XVRegionConnectivity::Type  inConnectivity        ;
    XVRegionFeature::Type       inFeature             ;
    XVFloat                     inMinimum             ;
    XVFloat                     inMaximum             ;
    bool                        inRemoveBoundaryBlobs ;
};
typedef RegionOut XVRemoveRegionBlobsOut;

namespace XVShiftType
{
enum Type
{
    Any,
    Horizontal,
    Vertical
};
}
namespace XVFitType
{
enum Type
{
    FirstFit,
    BestFit
};
}

/// <summary>Shifts source region so that it is contained in target region.</summary>
/// <param name="inTargetRegion">Region to contain source region.</param>
/// <param name="inSourceRegion">Region to be shifted.</param>
/// <param name="inPossibleShift">Possible directions of shift.</param>
/// <param name="inFitType">Determines if the common border length should be maximized.</param>
/// <param name="outShiftX">X coordinate of the shift.</param>
/// <param name="outShiftY">Y coordinate of the shift.</param>
/// <param name="outShiftedRegion">Shifted source region.</param>
struct XVInscribeRegionInRegionIn
{
    XVRegion                    inTargetRegion   ;
    XVRegion                    inSourceRegion   ;
    XVShiftType::Type           inPossibleShift  ;
    XVFitType::Type             inFitType        ;
};
struct XVInscribeRegionInRegionOut
{
    XVInt                       outShiftX        ;
    XVInt                       outShiftY        ;
    XVRegion                    outShiftedRegion ;
};


MAKEDLL_API void XVCropRegion               (XVCropRegionIn             &in, XVCropRegionOut                &out)throw(...);//从另一个矩形碎片创建一个区域
MAKEDLL_API void XVCropRegionToRectangle    (XVCropRegionToRectangleIn  &in, XVCropRegionToRectangleOut     &out)throw(...);
MAKEDLL_API void XVDownsampleRegion         (XVDownsampleRegionIn       &in, XVDownsampleRegionOut          &out)throw(...);//沿每个轴将一个区域缩小两倍。
MAKEDLL_API void XVEnlargeRegionNTimes      (XVEnlargeRegionNTimesIn    &in, XVEnlargeRegionNTimesOut       &out)throw(...);
MAKEDLL_API void XVMirrorRegion             (XVMirrorRegionIn           &in, XVMirrorRegionOut              &out)throw(...);
MAKEDLL_API void XVReflectRegion            (XVReflectRegionIn          &in, XVReflectRegionOut             &out)throw(...);
MAKEDLL_API void XVResizeRegion             (XVResizeRegionIn           &in, XVResizeRegionOut              &out)throw(...);
MAKEDLL_API void XVResizeRegion_Relative    (XVResizeRegion_RelativeIn  &in, XVResizeRegion_RelativeOut     &out)throw(...);
MAKEDLL_API void XVRotateRegion             (XVRotateRegionIn           &in, XVRotateRegionOut              &out)throw(...);
MAKEDLL_API void XVShearRegion              (XVShearRegionIn            &in, XVShearRegionOut               &out)throw(...);
MAKEDLL_API void XVTranslateRegion          (XVTranslateRegionIn        &in, XVTranslateRegionOut           &out)throw(...);
MAKEDLL_API void XVTransposeRegion          (XVTransposeRegionIn        &in, XVTransposeRegionOut           &out)throw(...);
MAKEDLL_API void XVUncropRegion             (XVUncropRegionIn           &in, XVUncropRegionOut              &out)throw(...);

MAKEDLL_API void XVAlignRegion              (XVAlignRegionIn            &in, XVAlignRegionOut               &out)throw(...);
MAKEDLL_API void XVRemoveRegionBlobs        (XVRemoveRegionBlobsIn      &in, XVRemoveRegionBlobsOut         &out)throw(...);
MAKEDLL_API void XVInscribeRegionInRegion   (XVInscribeRegionInRegionIn &in, XVInscribeRegionInRegionOut    &out)throw(...);






#endif // XVTRANSFORMREGION_H
