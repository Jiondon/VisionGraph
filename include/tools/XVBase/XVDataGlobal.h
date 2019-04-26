#ifndef XVDATAGLOBAL_H
#define XVDATAGLOBAL_H

#include "XVBase/XVGlobal.h"

//struct XVInt;
//struct XVFloat;
//struct XVPoint2D;
//struct XVArray_XVInt;
//struct XVArray_XVFloat;
//struct XVArray_XVPoint2D;
//struct XVLocation;
//struct XVBox;
//struct XVPixel;
//struct XVSize;
//struct XVArray_XVPixel;
//struct XVSegmentScanField;
//struct XVCircleFittingField;
//struct XVArcFittingField;
//struct XVSegmentFittingField;
//struct XVPathFittingField;
//struct XVLine2D;
//struct XVSegment2D;
//struct XVCircle2D;
//struct XVArc2D;
//struct XVRectangle2D;
//struct XVCoordinateSystem2D;
//struct XVStringLabel;
//struct XVGlobal;
//struct XVPoint3D;
//struct XVArray_XVSegment2D;
//struct XVArray_XVRectangle;
//struct XVImage;
//struct XVImageFormat;
//struct XVExtremum2D;
//struct XVImageLocalExtremaVerification;
//struct XVArray_XVImage;
//struct XVMEstimator;
//struct XVPImpl;
//struct XVPath;
//struct XVArray_XVPath;
//struct XVArrayArray_XVPath;
//struct XVProfile;
//struct XVColor;
//struct XVChartItem;
//struct XVChart;
//struct XVPointRun;
//struct XVRegion;
//struct XVShapeRegion;
//struct XVArray_XVRegion;
//struct XVArrayArray_XVRegion;
//struct XVEdge1D;
//struct XVRidge1D;
//struct XVStripe1D;
//struct XVGap1D;
//struct XVEdgeScanParams;
//struct XVRidgeScanParams;
//struct XVStripeScanParams;
//struct XVLocalBlindness;
//struct XVArray_XVEdge1D;
//struct XVArray_XVRidge1D;
//struct XVArray_XVStripe1D;
//struct XVArray_XVGap1D;
//struct XVString;
//struct XVArray_XVString;
//struct XVObject2D;


/** 所有数据全局多态
 *  便于以多态的形式传输数据
 * @brief The XVDataGlobal struct
 */
struct XVDataGlobal
{
    virtual string TypeMemo() = 0;

    virtual ~XVDataGlobal(){}
};

//private:
//    XVDataGlobal& operator=( const XVInt& ) { return *this; }
//    XVDataGlobal& operator=( const XVCppInt& ) { return *this; }
//    XVDataGlobal& operator=( const XVFloat& ) { return *this; }
//    XVDataGlobal& operator=( const XVPoint2D& ) { return *this; }
//    XVDataGlobal& operator=( const XVArray_XVInt& ) { return *this; }
//    XVDataGlobal& operator=( const XVArray_XVFloat& ) { return *this; }
//    XVDataGlobal& operator=( const XVArray_XVPoint2D& ) { return *this; }
//    XVDataGlobal& operator=( const XVLocation& ) { return *this; }
//    XVDataGlobal& operator=( const XVBox& ) { return *this; }
//    XVDataGlobal& operator=( const XVPixel& ) { return *this; }
//    XVDataGlobal& operator=( const XVSize& ) { return *this; }
//    XVDataGlobal& operator=( const XVArray_XVPixel& ) { return *this; }
//    XVDataGlobal& operator=( const XVSegmentScanField& ) { return *this; }
//    XVDataGlobal& operator=( const XVCircleFittingField& ) { return *this; }
//    XVDataGlobal& operator=( const XVArcFittingField& ) { return *this; }
//    XVDataGlobal& operator=( const XVSegmentFittingField& ) { return *this; }
//    XVDataGlobal& operator=( const XVPathFittingField& ) { return *this; }
//    XVDataGlobal& operator=( const XVLine2D& ) { return *this; }
//    XVDataGlobal& operator=( const XVSegment2D& ) { return *this; }
//    XVDataGlobal& operator=( const XVCircle2D& ) { return *this; }
//    XVDataGlobal& operator=( const XVArc2D& ) { return *this; }
//    XVDataGlobal& operator=( const XVRectangle2D& ) { return *this; }
//    XVDataGlobal& operator=( const XVCoordinateSystem2D& ) { return *this; }
//    XVDataGlobal& operator=( const XVStringLabel& ) { return *this; }
//    XVDataGlobal& operator=( const XVGlobal& ) { return *this; }
//    XVDataGlobal& operator=( const XVPoint3D& ) { return *this; }
//    XVDataGlobal& operator=( const XVArray_XVSegment2D& ) { return *this; }
//    XVDataGlobal& operator=( const XVArray_XVRectangle& ) { return *this; }
//    XVDataGlobal& operator=( const XVImage& ) { return *this; }
//    XVDataGlobal& operator=( const XVImageFormat& ) { return *this; }
//    XVDataGlobal& operator=( const XVExtremum2D& ) { return *this; }
//    XVDataGlobal& operator=( const XVImageLocalExtremaVerification& ) { return *this; }
//    XVDataGlobal& operator=( const XVArray_XVImage& ) { return *this; }
//    XVDataGlobal& operator=( const XVMEstimator& ) { return *this; }
//    XVDataGlobal& operator=( const XVPImpl& ) { return *this; }
//    XVDataGlobal& operator=( const XVPath& ) { return *this; }
//    XVDataGlobal& operator=( const XVArray_XVPath& ) { return *this; }
//    XVDataGlobal& operator=( const XVArrayArray_XVPath& ) { return *this; }
//    XVDataGlobal& operator=( const XVProfile& ) { return *this; }
//    XVDataGlobal& operator=( const XVColor& ) { return *this; }
//    XVDataGlobal& operator=( const XVChartItem& ) { return *this; }
//    XVDataGlobal& operator=( const XVChart& ) { return *this; }
//    XVDataGlobal& operator=( const XVPointRun& ) { return *this; }
//    XVDataGlobal& operator=( const XVRegion& ) { return *this; }
//    XVDataGlobal& operator=( const XVShapeRegion& ) { return *this; }
//    XVDataGlobal& operator=( const XVArray_XVRegion& ) { return *this; }
//    XVDataGlobal& operator=( const XVArrayArray_XVRegion& ) { return *this; }
//    XVDataGlobal& operator=( const XVEdge1D& ) { return *this; }
//    XVDataGlobal& operator=( const XVRidge1D& ) { return *this; }
//    XVDataGlobal& operator=( const XVStripe1D& ) { return *this; }
//    XVDataGlobal& operator=( const XVGap1D& ) { return *this; }
//    XVDataGlobal& operator=( const XVEdgeScanParams& ) { return *this; }
//    XVDataGlobal& operator=( const XVRidgeScanParams& ) { return *this; }
//    XVDataGlobal& operator=( const XVStripeScanParams& ) { return *this; }
//    XVDataGlobal& operator=( const XVLocalBlindness& ) { return *this; }
//    XVDataGlobal& operator=( const XVArray_XVEdge1D& ) { return *this; }
//    XVDataGlobal& operator=( const XVArray_XVRidge1D& ) { return *this; }
//    XVDataGlobal& operator=( const XVArray_XVStripe1D& ) { return *this; }
//    XVDataGlobal& operator=( const XVArray_XVGap1D& ) { return *this; }
//    XVDataGlobal& operator=( const XVString& ) { return *this; }
//    XVDataGlobal& operator=( const XVArray_XVString& ) { return *this; }
//    XVDataGlobal& operator=( const XVObject2D& ) { return *this; }

#endif // XVDATAGLOBAL_H
