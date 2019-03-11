#ifndef XVCREATEREGION_H
#define XVCREATEREGION_H

#ifdef XVCREATEREGION_LIBRARY
#define MAKEDLL_API extern "C" __declspec(dllexport)
#else
#define MAKEDLL_API extern "C" __declspec(dllimport)
#endif

#include "XVBase.h"


namespace XVCreateR
{
enum XVBorderPosition //边模式
{
    Internal,  //边内部
    External,  //边外部
    Centered   //边居中
};
namespace XVRegionOfInterestType//感兴趣区域类型
{
enum Type
{
    Region,
    Rectangle,
    Circle,
    Polygon
};
}


enum XVCreateRegionType
{
    BoxBorder         ,//边框
    Box               ,//填充框
    Circle            ,//圆
    Cross             ,//十字
    Ellipse           ,//椭圆
    Grid              ,//栅格
    Line              ,//线
    PathBorder        ,//路径边
    Polygon           ,//多边形
    RectangleBorder   ,//矩形边框
    Rectangle         ,//填充矩形框
    RegionOfInterest  ,//感兴趣区域
    Ring              ,//环
    Segment           ,//线段
    Location           //点集
};
}

typedef struct XVCreateRegionIn
{
    XVCreateR::XVCreateRegionType inType;
    int   inFrameWidth;
    int   inFrameHeight;
    //Circle / Ellipse / Line / PathBorder / Polygon / RectangleBorder / Rectangle / Ring / Segment
    XVCoordinateSystem2D                    inAlignment;//可选，默认NUL


    //BoxBorder / PathBorder / RectangleBorder
    int                                     inBorderWidth;

    //BoxBorder / PathBorder / RectangleBorder / Ring
    XVCreateR::XVBorderPosition             inBorderPosition;

    //BOX / BoxBorder / Cross / Grid
    XVBox                                   inBox;

    //Circle / RegionOfInterest / Ring
    XVCircle2D                              inCircle2D;

    //Ellipse / RectangleBorder / Rectangle / RegionOfInterest
    XVRectangle2D                           inRectangle2D;

    //Grid
    float                                   inHorizontalStep;
    float                                   inVerticalStep;

    //Line
    XVLine2D                                inLine;

    //Line / Segment
    int                                     inWidth;

    //PathBorder / Polygon / RegionOfInterest
    XVPath                                  inPath;

    //RegionOfInterest
    XVCreateR::XVRegionOfInterestType::Type inRegionOfInterestType;
    XVRegion                                inRegion;

    //Ring
    float                                   inRingWidth;

    //Segment
    XVSegment2D                             inSegment;
    bool                                    inRound;  //端点是否为圆

    //Location
    vector<XVLocation>                      inLocations;

}XVCreateRegionIn;


typedef struct XVCreateRegionOut
{
    XVCreateR::XVCreateRegionType outType;
    XVRegion     outregion;

    //Circle / Ring
    XVCircle2D    outAlignedCircle;

    //Ellipse / RectangleBorder / Rectangle
    XVRectangle2D outAlignedRectangle;

    //Line
    XVLine2D outAlignedLine;

    //PathBorder / Polygon
    XVPath outAlignedPath;

    //Segment
    XVSegment2D   outAlignedSegment;
}XVCreateRegionOut;

MAKEDLL_API void XVCreateRegion(XVCreateRegionIn& in, XVCreateRegionOut& out);


#endif // XVCREATEREGION_H
