#ifndef XVREGIONMORPHOLOGY_H
#define XVREGIONMORPHOLOGY_H
#include "xvregionanalysis_global.h"
#include "XVBasic.h"
#include "XVRegionArray.h"
#include "XVEnums/XVKernelShape.h"
#include "XVMetric.h"

namespace XVRegionSkeletonMethod
{
enum Type
{
    EightConnected,
    TwelveConnected
};
}


/// <summary>Performs a morphological dilation on a region using an arbitrary kernel.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inKernel">Kernel shape(any).</param>
/// <param name="inKernelAnchor">Location within inKernel defining its center. Default value: atl::NIL.</param>
/// <param name="outRegion">Output region.</param>
struct XVDilateRegion_AnyKernelIn
{
    XVRegion    					inRegion       ;
    XVRegion    					inKernel       ;
    XVLocation                      inKernelAnchor ;
};
typedef RegionOut XVDilateRegion_AnyKernelOut;



/// <summary>Performs a morphological dilation on a region using a predefined kernel.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inKernel">Kernel shape(predefined).</param>
/// <param name="inRadiusX">Nearly half of the kernel's width(2*R+1). Default value: 1.</param>
/// <param name="inRadiusY">Nearly half of the kernel's height(2*R+1) or same as inRadiusX. Default value: atl::NIL.</param>
/// <param name="outRegion">Output region.</param>
struct XVDilateRegionIn
{
    XVRegion    					inRegion  ;
    XVKernelShape::Type             inKernel  ;
    int								inRadiusX ;
    XVInt             				inRadiusY ;
};
typedef RegionOut XVDilateRegionOut;


/// <summary>Performs a morphological erosion on a region using an arbitrary kernel.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inKernel">Kernel shape(any).</param>
/// <param name="inKernelAnchor">Location within inKernel defining its center. Default value: atl::NIL.</param>
/// <param name="outRegion">Output region.</param>
struct XVErodeRegion_AnyKernelIn
{
    XVRegion    					inRegion       ;
    XVRegion    					inKernel       ;
    XVLocation                      inKernelAnchor ;
};
typedef RegionOut XVErodeRegion_AnyKernelOut;


/// <summary>Performs a morphological erosion on a region using a predefined kernel.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inKernel">Kernel shape(predefined).</param>
/// <param name="inRadiusX">Nearly half of the kernel's width(2*R+1). Default value: 1.</param>
/// <param name="inRadiusY">Nearly half of the kernel's height(2*R+1) or same as inRadiusX. Default value: atl::NIL.</param>
/// <param name="outRegion">Output region.</param>
struct XVErodeRegionIn
{
    XVRegion    					inRegion  ;
    XVKernelShape::Type             inKernel  ;
    int								inRadiusX ;
    XVInt             				inRadiusY ;
};
typedef RegionOut XVErodeRegionOut;


/// <summary>Erodes a region with inThresholdValue pixels of inKernel.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="outRegion">Output region.</param>
struct XVErodeRegion_ThresholdIn
{
    XVRegion                        inRegion         ;
    XVRegion                        inKernel         ;
    XVLocation                   	inKernelAnchor   ;
    int                             inThresholdValue ;
};
typedef RegionOut XVErodeRegion_ThresholdOut;

/// <summary>Performs a morphological opening on a region using an arbitrary kernel.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inKernel">Kernel shape(any).</param>
/// <param name="outRegion">Output region.</param>
struct XVOpenRegion_AnyKernelIn
{
    XVRegion                        inRegion  ;
    XVRegion                        inKernel  ;
};
typedef RegionOut XVOpenRegion_AnyKernelOut;


/// <summary>Performs a morphological opening on a region using a predefined kernel.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inKernel">Kernel shape(predefined).</param>
/// <param name="inRadiusX">Nearly half of the kernel's width(2*R+1). Default value: 1.</param>
/// <param name="inRadiusY">Nearly half of the kernel's height(2*R+1) or same as inRadiusX. Default value: atl::NIL.</param>
/// <param name="outRegion">Output region.</param>
struct XVOpenRegionIn
{
    XVRegion    					inRegion  ;
    XVKernelShape::Type             inKernel  ;
    int                             inRadiusX ;
    XVInt                           inRadiusY ;
};
typedef RegionOut XVOpenRegionOut;


/// <summary>Performs a morphological closing on a region using an arbitrary kernel.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inKernel">Kernel shape(any).</param>
/// <param name="outRegion">Output region.</param>
struct XVCloseRegion_AnyKernelIn
{
    XVRegion                        inRegion  ;
    XVRegion                        inKernel  ;
};
typedef RegionOut XVCloseRegion_AnyKernelOut;


/// <summary>Performs a morphological closing on a region using selected predefined kernel.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inKernel">Kernel shape(predefined).</param>
/// <param name="inRadiusX">Nearly half of the kernel's width(2*R+1). Default value: 1.</param>
/// <param name="inRadiusY">Nearly half of the kernel's height(2*R+1) or same as inRadiusX. Default value: atl::NIL.</param>
/// <param name="outRegion">Output region.</param>
struct XVCloseRegionIn
{
    XVRegion    					inRegion  ;
    XVKernelShape::Type             inKernel  ;
    int                             inRadiusX ;
    XVInt                           inRadiusY ;
};
typedef RegionOut XVCloseRegionOut;


/// <summary>Performs a hit-and-miss transformation on a region using arbitrary kernels.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inHitKernel">The kernel of pixels that should be present.</param>
/// <param name="inHitKernelAnchor">Location withing inHitKernel defining its center. Default value: atl::NIL.</param>
/// <param name="inMissKernel">The kernel of pixels that should be missing.</param>
/// <param name="inMissKernelAnchor">Location withing inMissKernel defining its center. Default value: atl::NIL.</param>
/// <param name="outRegion">Output region.</param>
struct XVRegionHitAndMissTransformIn
{
    XVRegion    					inRegion           ;
    XVRegion    					inHitKernel        ;
    XVLocation                   	inHitKernelAnchor  ;
    XVRegion    					inMissKernel       ;
    XVLocation                   	inMissKernelAnchor ;
};
typedef RegionOut XVRegionHitAndMissTransformOut;

/// <summary>Performs a morphological thinning on a region using predefined kernels.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="outRegion">Output region.</param>
typedef RegionIn  XVThinRegionIn;
typedef RegionOut XVThinRegionOut;


/// <summary>Performs a morphological thickening on a region using predefined kernels.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="outRegion">Output region.</param>
typedef RegionIn  XVThickenRegionIn;
typedef RegionOut XVThickenRegionOut;


/// <summary>Removes one pixel wide branches from a region.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inMaxLength">Maximal length of a branch of the input region to be pruned. Default value: 3.</param>
/// <param name="outRegion">Output region.</param>
struct XVPruneRegionIn
{
    XVRegion                        inRegion    ;
    int                             inMaxLength ;
};
typedef RegionOut XVPruneRegionOut;


/// <summary>Thins a region to its skeleton.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inRegionSkeletonMethod">Default value: TwelveConnected.</param>
/// <param name="outRegion">Output region.</param>
struct XVSkeletonizeRegionIn
{
    XVRegion                        inRegion               ;
    XVRegionSkeletonMethod::Type    inRegionSkeletonMethod ;
};
typedef RegionOut XVSkeletonizeRegionOut;

struct XVArray_XVRegionOut
{
    XVArray_XVRegion                    outRegions ;
};

/// <summary>Splits common pixels of the input regions among these regions.</summary>
/// <param name="inMetric">Metric used for deciding which region owns a pixel; if set to NIL region with lowest index in the input array is chosen. Default value: atl::NIL.</param>
struct XVDemarcateRegionsIn
{
    XVArray_XVRegion                    inRegions  ;
    XVMetric                            inMetric   ;
};
typedef XVArray_XVRegionOut XVDemarcateRegionsOut;


/// <summary>Splits pixels of the input regions and their complement among these regions.</summary>
/// <param name="inMetric">Metric used for deciding which region receives a pixel; if set to NIL Taxi metric is used after demarcating with NIL metric. Default value: atl::NIL.</param>
struct XVExpandRegionsIn
{
    XVArray_XVRegion                    inRegions  ;
    XVMetric                            inMetric   ;
};
typedef XVArray_XVRegionOut XVExpandRegionsOut;


MAKEDLL_API void XVDilateRegion_AnyKernel   (XVDilateRegion_AnyKernelIn     &in, XVDilateRegion_AnyKernelOut    &out)throw(...);
MAKEDLL_API void XVDilateRegion             (XVDilateRegionIn               &in, XVDilateRegionOut              &out)throw(...);
MAKEDLL_API void XVErodeRegion_AnyKernel    (XVErodeRegion_AnyKernelIn      &in, XVErodeRegion_AnyKernelOut     &out)throw(...);
MAKEDLL_API void XVErodeRegion              (XVErodeRegionIn                &in, XVErodeRegionOut               &out)throw(...);
MAKEDLL_API void XVErodeRegion_Threshold    (XVErodeRegion_ThresholdIn      &in, XVErodeRegion_ThresholdOut     &out)throw(...);
MAKEDLL_API void XVOpenRegion_AnyKernel     (XVOpenRegion_AnyKernelIn       &in, XVOpenRegion_AnyKernelOut      &out)throw(...);
MAKEDLL_API void XVOpenRegion               (XVOpenRegionIn                 &in, XVOpenRegionOut                &out)throw(...);
MAKEDLL_API void XVCloseRegion_AnyKernel    (XVCloseRegion_AnyKernelIn      &in, XVCloseRegion_AnyKernelOut     &out)throw(...);
MAKEDLL_API void XVCloseRegion              (XVCloseRegionIn                &in, XVCloseRegionOut               &out)throw(...);
MAKEDLL_API void XVRegionHitAndMissTransform(XVRegionHitAndMissTransformIn  &in, XVRegionHitAndMissTransformOut &out)throw(...);
MAKEDLL_API void XVThinRegion               (XVThinRegionIn                 &in, XVThinRegionOut                &out)throw(...);
MAKEDLL_API void XVThickenRegion            (XVThickenRegionIn              &in, XVThickenRegionOut             &out)throw(...);
MAKEDLL_API void XVPruneRegion              (XVPruneRegionIn                &in, XVPruneRegionOut               &out)throw(...);
MAKEDLL_API void XVSkeletonizeRegion        (XVSkeletonizeRegionIn          &in, XVSkeletonizeRegionOut         &out)throw(...);
MAKEDLL_API void XVDemarcateRegions         (XVDemarcateRegionsIn           &in, XVDemarcateRegionsOut          &out)throw(...);
MAKEDLL_API void XVExpandRegions            (XVExpandRegionsIn              &in, XVExpandRegionsOut             &out)throw(...);


#endif // XVREGIONMORPHOLOGY_H
