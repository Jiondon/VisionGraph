#ifndef XVREGIONFEATURE_H
#define XVREGIONFEATURE_H

#include "xvregionanalysis_global.h"
#include "XVGeometry.h"
#include "XVProfile.h"
#include "XVBaseTypeArray.h"
#include "XVBasicArray.h"
#include "XVPathArray.h"
#include "XVRegionArray.h"
#include "XVEnums/XVProjectionDirection.h"
#include "XVRegionConnectivity.h"


namespace XVBoundingRectangleFeature
{
enum Type
{
    MinimalArea,
    MinimalPerimeter
};
}
namespace XVRectangleOrientation
{
enum Type
{
    Horizontal,
    Vertical,
    Any
};
}
namespace XVCircularityMeasure
{
enum Type
{
    BoundingCirclePreserving,
    PerimeterPreserving,
    RadiusPreserving
};
}
namespace XVRegionContourMode
{
enum Type
{
    PixelCenters,
    PixelEdges
};
}
namespace XVRegionMomentType
{
enum Type
{
    _02,
    _11,
    _20
};
}
namespace XVRegionSkeletonMethod
{
enum Type
{
    EightConnected,
    TwelveConnected
};
}


/// <summary>Computes selected second-order moment of a region in regular and normalized { divided by region area } variant.</summary>
/// <param name="inRegion">Input region.</param>
struct XVRegionMomentIn
{
    XVRegion                    inRegion      ;
    XVRegionMomentType::Type    inMomentType  ;
    bool						inCentral     ;

};
struct XVRegionMomentOut
{
    float                       outMoment     ;
    float                       outNormMoment ;
};

/// <summary>Computes the number of pixels contained in a region.</summary>
/// <param name="inRegion">Input region.</param>
typedef RegionIn XVRegionAreaIn;
struct XVRegionAreaOut
{
    int         outArea;
};

/// <summary>Computes the smallest box containing a region.</summary>
/// <param name="inRegion">Input region.</param>
typedef RegionIn XVRegionBoundingBoxIn;
struct XVRegionBoundingBoxOut
{
    XVBox       outBoundingBox;
};

/// <summary>Computes the smallest circle enclosing a region.</summary>
/// <param name="inRegion">Input region.</param>
typedef RegionIn XVRegionBoundingCircleIn;
struct XVRegionBoundingCircleOut
{
    XVCircle2D  outBoundingCircle ;
};

/// <summary>Computes the smallest rectangle containing a region; returns NIL if the region is empty.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inBoundingRectangleFeature">Determines what kind of bounding rectangle will be computed. Default value: MinimalArea.</param>
/// <param name="inReferenceAngle">The middle angle of the valid range of the output rectangle's angle. Default value: 0.0f.</param>
/// <param name="inRectangleOrientation">Orientation of the output rectangle. Default value: Horizontal.</param>
/// <param name="outBoundingRectangle">Smallest bounding rectangle of the input region.</param>
/// <param name="outCenter">Center of the bounding rectangle.</param>
/// <param name="outLongSide">Length of the bounding rectangle long side.</param>
/// <param name="outShortSide">Length of the bounding rectangle short side.</param>
struct XVRegionBoundingRectangleIn
{
    XVRegion                            inRegion                   ;
    XVBoundingRectangleFeature::Type    inBoundingRectangleFeature = XVBoundingRectangleFeature::MinimalArea;
    float                               inReferenceAngle           = 0.0f;
    XVRectangleOrientation::Type        inRectangleOrientation     = XVRectangleOrientation::Horizontal;
};
struct XVRegionBoundingRectangleOut
{
    XVRectangle2D   outBoundingRectangle ;
    XVPoint2D       outCenter            ;
    XVFloat         outLongSide          ;
    XVFloat         outShortSide         ;
};

/// <summary>Computes the smallest rectangle with the given orientation angle containing a region; returns NIL if the region is empty.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inAngle">Expected angle of the resulting rectangle.</param>
/// <param name="outBoundingRectangle">Smallest bounding rectangle of the input region.</param>
/// <param name="outCenter">Center of the bounding rectangle.</param>
/// <param name="outLongSide">Length of the bounding rectangle long side.</param>
/// <param name="outShortSide">Length of the bounding rectangle short side.</param>
struct XVRegionBoundingRectangle_FixedAngleIn
{
    XVRegion        inRegion             ;
    float           inAngle              ;
};
typedef XVRegionBoundingRectangleOut XVRegionBoundingRectangle_FixedAngleOut;

/// <summary>Computes the area of a region divided by the area of a circular region having the same feature.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inCircularityMeasure">Which algorithm should be used to compute a circle. Default value: RadiusPreserving.</param>
/// <param name="diagCircle">Computed circle which area was compared.</param>
struct XVRegionCircularityIn
{
    XVRegion                    inRegion             ;
    XVCircularityMeasure::Type  inCircularityMeasure = XVCircularityMeasure::RadiusPreserving;
};
struct XVRegionCircularityOut
{
    float                       outCircularity       ;
    XVCircle2D                  diagCircle           ;
};

/// <summary>Computes an array of closed paths corresponding to the contours of the input region.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inRegionConnectivity">Region connectivity semantics. Default value: EightDirections.</param>
struct XVRegionContoursIn
{
    XVRegion                    inRegion             ;
    XVRegionContourMode::Type	inContourMode        ;
    XVRegionConnectivity::Type	inRegionConnectivity = XVRegionConnectivity::EightDirections;
};
struct XVRegionContoursOut
{
    XVArray_XVPath              outContours          ;
};

/// <summary>Computes the area of a region divided by area of its convex hull.</summary>
/// <param name="inRegion">Input region.</param>
typedef RegionIn XVRegionConvexityIn;
struct XVRegionConvexityOut
{
    float   outConvexity;
};

/// <summary>Computes the longest segment connecting two pixels contained in region and its length.</summary>
/// <param name="inRegion">Input region.</param>
typedef RegionIn XVRegionDiameterIn;
struct XVRegionDiameterOut
{
    XVSegment2D outDiameter         ;
    XVFloat     outDiameterLength   ;
};


/// <summary>Computes axes of an ellipse having the same first and second order moments as the given region.</summary>
/// <param name="inRegion">Input region.</param>
typedef RegionIn XVRegionEllipticAxesIn;
struct XVRegionEllipticAxesOut
{
    XVSegment2D  outMajorAxis;
    XVSegment2D  outMinorAxis;
};

/// <summary>Computes the elongation factor of a region { perfect circle has minimal elongation equal 1.0 }.</summary>
/// <param name="inRegion">Input region.</param>
typedef RegionIn XVRegionElongationIn;
struct XVRegionElongationOut
{
    float   outElongation;
};

/// <summary>Creates regions of the holes of the input region.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inConnectivity">Region connectivity semantics.</param>
/// <param name="inMinHoleArea">Minimal area of a resulting hole. Default value: 1.</param>
/// <param name="inMaxHoleArea">Maximal area of a resulting hole. Default value: atl::NIL.</param>
struct XVRegionHolesIn
{
    XVRegion                    inRegion        ;
    XVRegionConnectivity::Type	inConnectivity  ;
    int							inMinHoleArea   = 1;
    XVInt                       inMaxHoleArea   ;
};
struct XVRegionHolesOut
{
    XVArray_XVRegion            outHoles        ;
};

/// <summary>Computes the largest box contained in a region.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inMinAspectRatio">Minimal aspect ratio of found box. Default value: 0.0f.</param>
/// <param name="inMaxAspectRatio">Maximal aspect ratio of found box {reciprocal of inMinAspectRatio by default}. Default value: atl::NIL.</param>
/// <param name="inMinWidth">Minimal width of found box. Default value: 1.</param>
/// <param name="inMaxWidth">Maximal width of found box. Default value: atl::NIL.</param>
/// <param name="inMinHeight">Minimal height of found box. Default value: 1.</param>
/// <param name="inMaxHeight">Maximal height of found box. Default value: atl::NIL.</param>
/// <param name="outBox">Found box with largest area.</param>
struct XVRegionInscribedBoxIn
{
    XVRegion    inRegion            ;
    float       inMinAspectRatio    = 0.0f;
    XVFloat     inMaxAspectRatio    ;
    int         inMinWidth          = 1;
    XVInt       inMaxWidth          ;
    int         inMinHeight         = 1;
    XVInt       inMaxHeight         ;

};
struct XVRegionInscribedBoxOut
{
    XVBox       outBox              ;
};

/// <summary>Computes a point with coordinates equal to the average coordinates of the region's pixels.</summary>
/// <param name="inRegion">Input region.</param>
typedef RegionIn XVRegionMassCenterIn;
struct XVRegionMassCenterOut
{
    XVPoint2D	outMassCenter   ;
};

/// <summary>Computes an array of paths corresponding to the skeleton of the input region.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inRegionSkeletonMethod">Default value: TwelveConnected.</param>
struct XVRegionMedialAxisIn
{
    XVRegion                        inRegion                    ;
    XVRegionSkeletonMethod::Type	inRegionSkeletonMethod      = XVRegionSkeletonMethod::TwelveConnected;
};
struct XVRegionMedialAxisOut
{
    XVArray_XVPath                  outSkeletonPaths            ;
};

/// <summary>Computes the number of holes in a region.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inConnectivity">Region connectivity semantics.</param>
/// <param name="inMinHoleArea">Minimal area of a hole. Default value: 1.</param>
/// <param name="inMaxHoleArea">Maximal area of a hole. Default value: atl::NIL.</param>
struct XVRegionNumberOfHolesIn
{
    XVRegion                    inRegion         ;
    XVRegionConnectivity::Type  inConnectivity   ;
    int							inMinHoleArea    = 1;
    XVInt                       inMaxHoleArea    ;
};
struct XVRegionNumberOfHolesOut
{
    int                         outNumberOfHoles ;
};

/// <summary>Computes the orientation of a region as an angle of value in range 0.0 - 180.0.</summary>
/// <param name="inRegion">Input region.</param>
typedef RegionIn XVRegionOrientationIn;
struct XVRegionOrientationOut
{
    float       outOrientationAngle ;
};

/// <summary>Computes the length of the input region perimeter.</summary>
/// <param name="inRegion">Input region.</param>
typedef RegionIn XVRegionPerimeterLengthIn;
struct XVRegionPerimeterLengthOut
{
    float       outPerimeterLength ;
};

/// <summary>Computes the profile of the region pixel count in consecutive rows or columns.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inProjectionDirection">Direction in which the pixel occurrences are counted 'horizontal' means summation row after row 'vertical' indicates summation column after column.</param>
/// <param name="outProfile">Profile of pixel count in consecutive rows/columns.</param>
struct XVRegionProjectionIn
{
    XVRegion                    inRegion                ;
    XVProjectionDirection::Type	inProjectionDirection   ;
};
struct XVRegionProjectionOut
{
    XVProfile					outProfile              ;
};

/// <summary>Computes the area of a region divided by the area of its bounding rectangle.</summary>
/// <param name="inRegion">Input region.</param>
typedef RegionIn XVRegionRectangularityIn;
struct XVRegionRectangularityOut
{
    float       outRectangularity ;
};

/// <summary>Computes the smallest parallelogram containing a region.</summary>
/// <param name="inRegion">Input region.</param>
/// <param name="inBoundingParallelogramFeature">Determines what kind of bounding parallelogram will be computed. Default value: MinimalArea.</param>
/// <param name="outBoundingParallelogram">Smallest bounding parallelogram of the input points.</param>
/// <param name="outCenter">Center of the bounding parallelogram.</param>
/// <param name="outLongSide">Length of the bounding parallelogram long side.</param>
/// <param name="outShortSide">Length of the bounding parallelogram short side.</param>
/// <param name="outAngle">Angle of the bounding parallelogram.</param>
struct XVRegionBoundingParallelogramIn
{
    XVRegion                            inRegion                       ;
    XVBoundingRectangleFeature::Type    inBoundingParallelogramFeature = XVBoundingRectangleFeature::MinimalArea;
};
struct XVRegionBoundingParallelogramOut
{
    XVPath                              outBoundingParallelogram       ;
    XVPoint2D                           outCenter                      ;
    XVFloat                             outLongSide                    ;
    XVFloat                             outShortSide                   ;
    XVFloat                             outAngle                       ;
};

/// <summary>Internal character normalization.</summary>
struct XVRegionSimilarityIn
{
    XVSize      inNormalizationSize ;
    XVRegion	inA                 ;
    XVRegion	inB                 ;
};
struct XVRegionSimilarityOut
{
    float		outFactor           ;
};

/// <summary>Returns the lengths of horizontal sequences of locations that itute the input region.</summary>
/// <param name="inRegion">Input region.</param>
typedef RegionIn XVRegionPointRunLengthsIn;
struct XVRegionPointRunLengthsOut
{
    XVArray_XVInt	outPointRunLengths  ;
};

/// <summary>Converts a region to an array of its pixels locations.</summary>
/// <param name="inRegion">Input region.</param>
typedef RegionIn XVRegionToLocationsIn;
struct XVRegionToLocationsOut
{
    XVArray_XVLocation	outLocations ;
};

/// <summary>Forms a region containing pixels of given locations.</summary>
/// <param name="outRegion">Output region.</param>
struct XVLocationsToRegionIn
{
    XVArray_XVLocation	inLocations   ;
    int					inFrameWidth  ;
    int                 inFrameHeight ;
};
struct XVLocationsToRegionOut
{
    XVRegion            outRegion     ;
};


MAKEDLL_API void XVRegionArea                        (XVRegionAreaIn                         &in, XVRegionAreaOut                         &out)throw(...);//计算区域中包含的像素数
MAKEDLL_API void XVRegionBoundingBox                 (XVRegionBoundingBoxIn                  &in, XVRegionBoundingBoxOut                  &out)throw(...);//计算包含区域的最小框
MAKEDLL_API void XVRegionBoundingCircle              (XVRegionBoundingCircleIn               &in, XVRegionBoundingCircleOut               &out)throw(...);//计算包围区域的最小圆
MAKEDLL_API void XVRegionBoundingRectangle           (XVRegionBoundingRectangleIn            &in, XVRegionBoundingRectangleOut            &out)throw(...);//计算包含区域的最小矩形
MAKEDLL_API void XVRegionBoundingRectangle_FixedAngle(XVRegionBoundingRectangle_FixedAngleIn &in, XVRegionBoundingRectangle_FixedAngleOut &out)throw(...);//计算给定包含区域的方位角的最小矩形
MAKEDLL_API void XVRegionCircularity                 (XVRegionCircularityIn                  &in, XVRegionCircularityOut                  &out)throw(...);//计算一个区域的面积除以具有相同特征的圆形区域的面积
MAKEDLL_API void XVRegionContours                    (XVRegionContoursIn                     &in, XVRegionContoursOut                     &out)throw(...);//计算与输入区域的轮廓对应的闭合路径数组
MAKEDLL_API void XVRegionConvexity                   (XVRegionConvexityIn                    &in, XVRegionConvexityOut                    &out)throw(...);//计算一个区域的面积除以其凸包的面积
MAKEDLL_API void XVRegionDiameter                    (XVRegionDiameterIn                     &in, XVRegionDiameterOut                     &out)throw(...);//计算连接区域内两个像素点的最长段及其长度
MAKEDLL_API void XVRegionEllipticAxes                (XVRegionEllipticAxesIn                 &in, XVRegionEllipticAxesOut                 &out)throw(...);//计算具有与给定区域相同的一阶和二阶矩的椭圆的轴线
MAKEDLL_API void XVRegionElongation                  (XVRegionElongationIn                   &in, XVRegionElongationOut                   &out)throw(...);//计算一个区域的伸长因子{完美圆的最小伸长值为1.0}
MAKEDLL_API void XVRegionHoles                       (XVRegionHolesIn                        &in, XVRegionHolesOut                        &out)throw(...);//创建输入区域的空穴区域
MAKEDLL_API void XVRegionInscribedBox                (XVRegionInscribedBoxIn                 &in, XVRegionInscribedBoxOut                 &out)throw(...);//计算区域中包含的最大框
MAKEDLL_API void XVRegionMassCenter                  (XVRegionMassCenterIn                   &in, XVRegionMassCenterOut                   &out)throw(...);//计算坐标等于该区域像素的平均坐标的点
MAKEDLL_API void XVRegionMedialAxis                  (XVRegionMedialAxisIn                   &in, XVRegionMedialAxisOut                   &out)throw(...);//计算与输入区域骨架相对应的路径数组
MAKEDLL_API void XVRegionNumberOfHoles               (XVRegionNumberOfHolesIn                &in, XVRegionNumberOfHolesOut                &out)throw(...);//计算一个区域的孔数
MAKEDLL_API void XVRegionOrientation                 (XVRegionOrientationIn                  &in, XVRegionOrientationOut                  &out)throw(...);//以0.0 - 180.0范围内的值角计算区域的方向
MAKEDLL_API void XVRegionPerimeterLength             (XVRegionPerimeterLengthIn              &in, XVRegionPerimeterLengthOut              &out)throw(...);//计算输入区域周长的长度
MAKEDLL_API void XVRegionProjection                  (XVRegionProjectionIn                   &in, XVRegionProjectionOut                   &out)throw(...);//计算连续行或列中区域像素计数的概要
MAKEDLL_API void XVRegionRectangularity              (XVRegionRectangularityIn               &in, XVRegionRectangularityOut               &out)throw(...);//计算区域的面积除以其包围矩形的面积
MAKEDLL_API void XVRegionToLocations                 (XVRegionToLocationsIn                  &in, XVRegionToLocationsOut                  &out)throw(...);//将一个区域转换为其像素位置的数组
MAKEDLL_API void XVLocationsToRegion                 (XVLocationsToRegionIn                  &in, XVLocationsToRegionOut                  &out)throw(...);//形成包含给定位置像素的区域

MAKEDLL_API void XVRegionMoment                      (XVRegionMomentIn                       &in, XVRegionMomentOut                       &out)throw(...);//用正则和归一化的{除以区域面积}变量计算区域的选定二阶矩
MAKEDLL_API void XVRegionBoundingParallelogram       (XVRegionBoundingParallelogramIn        &in, XVRegionBoundingParallelogramOut        &out)throw(...);//计算包含区域的最小平行四边形
MAKEDLL_API void XVRegionSimilarity                  (XVRegionSimilarityIn                   &in, XVRegionSimilarityOut                   &out)throw(...);//内部字符归一化
MAKEDLL_API void XVRegionPointRunLengths             (XVRegionPointRunLengthsIn              &in, XVRegionPointRunLengthsOut              &out)throw(...);//返回分解输入区域的水平位置序列的长度


#endif // XVREGIONFEATURE_H
