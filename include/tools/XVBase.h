#ifndef XVBASE_H
#define XVBASE_H

#include <vector>
using namespace std;

typedef unsigned char BYTE;
typedef int           BOOL;
#define TRUE	1
#define FALSE	0

namespace XVPolarSpaceType
{
///<summary>Decides which formula use to transform image. Parameters \(m\) and \(k\) are set to values which allow to fit source image in output image.</summary>
enum Type
{
    ///<summary>Polar space</summary>
    Polar,
    ///<summary>Log-Polar space</summary>
    LogPolar
};
}

namespace XVResizeMethod {
enum Type
{
    NearestNeighbour,
    Bilinear,
    Area
};
}

namespace XVCropScaleMode {
enum Type{
    InputScale,
    AlignedScale
};
}
namespace XVAxis {
enum Type
{
    X,
    Y
};
}
namespace XVMirrorDirection {
enum Type
{
    Horizontal,
    Vertical,
    Both
};
}

namespace XVRotationSizeMode {
enum Type
{
    Fit,
    Preserve
};
}

namespace XVMagnitudeMeasure {
enum Type
{
    ///<summary>Horizontal estimation</summary>
    Horizontal,
    ///<summary>Vertical estimation</summary>
    Vertical,
    ///<summary>Average estimation</summary>
    Average,
    ///<summary>Sum estimation</summary>
    Sum,
    ///<summary>Maximum estimation</summary>
    Maximum,
    ///<summary>Hypot estimation</summary>
    Hypot
};
}

namespace XVThresholdSelectionMethod {
enum Type
{
    ClusteringKittler,
    ///<summary>KMeans clustering</summary>
    ClusteringKMeans,
    ///<summary>Otsu clustering</summary>
    ClusteringOtsu,
    Entropy,
    HistogramIntermodes
};

}

namespace XVThresholdDynamicReferenceMethod
{
enum Type
{
    Mean,
    Median,
    Middle
};
}

namespace XVSmoothImageMedianKernel
{
enum Type
{
    Box
};
}
namespace XVMeanKernel
{
///<summary>Describes shape and size of structuring element used during smoothing.</summary>
enum Type
{
    Box3x3,
    Box5x5
};
}

namespace XVGaussKernel
{
///<summary>Possible dimensions of gaussian kernel used to smooth image.</summary>
enum Type
{
    _3x3,
    _5x5,
    _7x7,
    _9x9,
    _11x11
};
}

enum XVMorphologyKernelType
{
    Box3x3,
    Box5x5,
    Cross3x3,
    Cross5x5,
    Disc5x5,
    Disc7x7,
    Disc9x9
};

namespace XVKernelShape {
enum Type
{
    Box,
    Ellipse,
    Cross
};
}


enum XVGradientMaskOperatorType
{
    ///<summary>Sobel operator</summary>
    Sobel,
    ///<summary>Prewitt operator</summary>
    Prewitt,
    Central,
    Forward
};
enum XVGradientAngleRangeType
{
    _0_90,
    _0_180
};
enum XVGradientOperatorType
{
    Gauss,
    Deriche,
    Lanser
};

enum XVBayerTypeType
{
    GR,
    RG,
    GB,
    BG
};

///<summary>Ways of computing image compare.</summary>
enum XVCompareMeasureType
{
    Value,
    NCC,
    DSSIM
};
enum XVCorrelationMeasureType
{
    NormalizedCrossCorrelation,
    CrossCorrelation
};

enum XVDistanceMeasureType
{
    MeanError,
    MeanSquaredError
};
enum XVHSxColorModel
{
    HSV,
    HSL,
    HSI
};

enum XVProjectionDirection
{
    Horizontal,
    Vertical
};

namespace XVProjectionMode {
enum type
{
    Average,
    Maximum,
    Minimum,
    Sum
};
}

//表示图像的像素点或者二维矩阵的元素等

enum XVOptionalType
{
    NUL,
    ENABLE
};

enum XVSelectionType //检测到多个边缘点时对边缘点的选择方式
{
    Best,   //最优
    First,  //第一个边缘点
    Last    //最后一个边缘点
};

enum XVRidgeOperatorType
{
    Minimum,
    GeometricMean,
    ArithmeticMean,
    HarmonicMean
};

enum XVInterpolationMethodType
{
    NearestNeighbour, //最邻近
    Bilinear          //双线性(二维线性插值)
};

enum XVProfileInterpolationMethod //用于提取亚像素
{
    Linear,   					// 线性 Linear interpolation between consecutive points of the profile. (一维线性插值，是三个点的（位置*像素值）/(像素值求和)？)
    Quadratic3,   				// 三次 Interpolation that fits a parabola to 3 consecutive points.（拟合抛物线 求抛物线的最高点？）
    Quadratic4					// 四次 Interpolation that fits a parabola to 4 consecutive points.（哪4个点参与运算？）
};

//边缘跳变类型
enum XVEdgeTransitionType
{
    BrightToDark, // 由白到黑
    DarkToBright, // 由黑到白
    Any           // 任意
};


typedef struct XVInt
{
    XVOptionalType  optional = ENABLE;
    int             value;

    XVInt(int _value = 0, XVOptionalType _optional = ENABLE){
        optional = _optional;
        value = _value;
    }
}XVInt;

typedef struct XVFloat
{
    XVOptionalType  optional = ENABLE;
    float           value;

    XVFloat(float _value = 0, XVOptionalType _optional = ENABLE){
        optional = _optional;
        value = _value;
    }
}XVFloat;

//像素
struct XVPixel
{
    XVOptionalType  optional = ENABLE;
    float           x;
    float           y;
    float           z;
    float           w;

    XVPixel(float x_ = 0, float y_ = 0, float z_ = 0, float w_ = 0, XVOptionalType _optional = ENABLE){
        optional = _optional;
        x = x_;
        y = y_;
        z = z_;
        w = w_;
    }
};


//二维点
typedef struct XVPoint2DInt
{
    XVOptionalType  optional = ENABLE;
    int x;
    int y;

    XVPoint2DInt(int x_=0, int y_=0,XVOptionalType optional_ = ENABLE){
        optional = optional_;
        x = x_;
        y = y_;
    }
}XVLocation;


struct XVPoint2D
{
    XVOptionalType optional = ENABLE;
    float x;
    float y;

    XVPoint2D(float x_ = 0, float y_ = 0, XVOptionalType optional_ = ENABLE){
        optional = optional_;
        x = x_;
        y = y_;
    }
    XVPoint2D(int x_, int y_, XVOptionalType optional_ = ENABLE){
        optional = optional_;
        x = (float)x_;
        y = (float)y_;
    }
    XVPoint2D(int x_, float y_, XVOptionalType optional_ = ENABLE){
        optional = optional_;
        x = (float)x_;
        y = y_;
    }
    XVPoint2D(float x_, int y_, XVOptionalType optional_ = ENABLE){
        optional = optional_;
        x = x_;
        y = (float)y_;
    }

};

//三维点
struct XVPoint3D
{
    XVOptionalType optional = ENABLE;
    float x;
    float y;
    float z;

    XVPoint3D(float x_=0, float y_=0, float z_=0, XVOptionalType optional_ = ENABLE){
        optional = optional_;
        x = x_;
        y = y_;
        z = z_;
    }
};

//圆
struct XVCircle2D
{
    XVOptionalType  optional = ENABLE;
    XVPoint2D       center;     //中心
    float           radius;     //半径

    XVCircle2D(XVPoint2D center_=XVPoint2D(), float radius_=0,  XVOptionalType opt_=ENABLE){
        optional = opt_;
        center = center_;
        radius = radius_;
    }
};

//圆环域
struct XVCircleFittingField
{
    XVCircle2D	axis;  //扫描中心轴
    float	width; //扫描宽度

    XVCircleFittingField(XVCircle2D axis_=XVCircle2D() , float w_=0){
        axis = axis_;
        width = w_;
    }
};

//圆弧
struct XVArc2D
{
    XVPoint2D   center;     //中心
    float       radius;     //半径
    float       startAngle; //起始角度
    float       sweepAngle; //扫描角度


    XVArc2D(XVPoint2D   center_ = XVPoint2D(),
            float       radius_ = 0,
            float       startAngle_ = 0,
            float       sweepAngle_ = 0){
        center     = center_;
        radius     = radius_;
        startAngle = startAngle_;
        sweepAngle = sweepAngle_;
    }
};

//圆弧域
struct XVArcFittingField
{
    XVArc2D	axis;
    float	width;

    XVArcFittingField(XVArc2D axis_=XVArc2D() , float w_=0){
        axis = axis_;
        width = w_;
    }
};

//矩形及其旋转角度
typedef struct XVRectangle2D
{
    XVOptionalType optional = ENABLE;
    XVPoint2D   origin; //顶点(左上点，不是中心)
    float       angle;  //旋转角度（绕中心旋转角度）
    float       width;  //宽度
    float       height; //高度

    XVRectangle2D(XVPoint2D origin_ = XVPoint2D(),
                  float     angle_  = 0,
                  float     width_  = 0,
                  float     height_ = 0,
                  XVOptionalType optional_ = ENABLE){
        origin = origin_;
        angle  = angle_ ;
        width  = width_ ;
        height = height_;
        optional = optional_;
    }
}XVRectangle2D;

//Box
typedef struct XVBox
{
    XVOptionalType  optional = ENABLE;
    XVPoint2DInt    origin; //顶点(左上点，不是中心)
    int             width;  //宽度
    int             height; //高度

    XVBox(XVPoint2DInt origin_=XVPoint2DInt(), int width_=0, int height_=0, XVOptionalType opt_=ENABLE){
        optional =  opt_   ;
        origin   =  origin_;
        width    =  width_ ;
        height   =  height_;
    }
}XVBox;

//表示一个边缘点
struct XVEdge1D
{
    XVPoint2D               point;      //坐标
    float                   magnitude;  //梯度幅值
    XVEdgeTransitionType    transition; //方向

    XVEdge1D(XVPoint2D point_=XVPoint2D(), float magnitude_=0, XVEdgeTransitionType transition_= Any){
        point      = point_      ;
        magnitude  = magnitude_  ;
        transition = transition_ ;
    }
};

//表示边缘点之间的距离
struct XVGap1D
{
    XVPoint2D	point1;
    XVPoint2D	point2;
    float	width;

    XVGap1D(XVPoint2D point1_=XVPoint2D(), XVPoint2D point2_=XVPoint2D(), float width_=0){
        point1 = point1_;
        point2 = point2_;
        width  = width_ ;
    }
};

enum XVPlainType
{
    Int8,
    UInt8,
    Int16,
    UInt16,
    Int32,
    Real
};
typedef struct XVImage
{
    int             width   ;			// number of pixel columns
    int             height  ;			// number of pixel rows
    XVPlainType	    type    ;                   // type of channels (默认UInt8)
    int             depth   ;			// number of channels(灰度图1)
    BYTE*           data    ;
}XVImage;

//直线ax + by + c = 0
struct XVLine2D
{
    XVOptionalType      optional = ENABLE;
    float a;
    float b;
    float c;

    XVLine2D(float a_=0, float b_=0, float c_=0, XVOptionalType optional_ = ENABLE)
    {
        optional = optional_;
        a = a_;
        b = b_;
        c = c_;
    }
};
//行程
struct XVPointRun
{
    int    x;
    int    y;  // PointRun begin location 起始点的x,y像素位置
    int    length;//行程

    XVPointRun(int x_=0, int y_=0, int length_=0){
        x = x_;
        y = y_;
        length = length_;
    }
};

typedef struct XVRegion
{
    XVOptionalType      optional = ENABLE; //ROI是否起作用
    int                 frameWidth;
    int                 frameHeight;
    vector<XVPointRun>  arrayPointRun;

    XVRegion(){
        optional      = ENABLE;
        frameWidth    = 0;
        frameHeight   = 0;
        arrayPointRun.clear();
    }

    XVRegion(int frameWidth_, int frameHeight_, const vector<XVPointRun> &arrayPointRun_, XVOptionalType optional_ = ENABLE){
        optional      = optional_     ;
        frameWidth    = frameWidth_   ;
        frameHeight   = frameHeight_  ;
        arrayPointRun = arrayPointRun_;
    }
}XVRegion;

//路径或者链条
struct XVPath
{
    vector< XVPoint2D > arrayPoint2D;
    bool                closed;

    XVPath(){
        arrayPoint2D.clear();
        closed = false;
    }
    XVPath(const vector<XVPoint2D>& arrayPoint2D_, bool closed_){
        arrayPoint2D = arrayPoint2D_;
        closed = closed_;
    }
};

struct XVPathFittingField
{
    XVPath	axis;
    float	width;
};

enum XVPolarityType
{
    Bright,
    Dark,
    ANY
};
//Represents ridges found by 1D Edge Detection functions
struct XVRidge1D
{
    XVPoint2D		point;
    float		magnitude;
    XVPolarityType	polarity;
};
//Represents stripes found by 1D Edge Detection functions
struct XVStripe1D
{
    XVPoint2D		point1;
    XVPoint2D           point2;
    float               width;
    float               magnitude;
    XVPolarityType	polarity;
};

//通过起点和终点来表示一条有向线段
struct XVSegment2D
{
    XVOptionalType optional = ENABLE;
    XVPoint2D point1; //起点
    XVPoint2D point2; //终点

    XVSegment2D(XVPoint2D p1=XVPoint2D(0,0), XVPoint2D p2=XVPoint2D(0,0), XVOptionalType opt=ENABLE){
        point1 = p1;
        point2 = p2;
        optional = opt;
    }
};

struct XVSegmentFittingField
{
    XVSegment2D	axis;
    float       width = 20.0f;
};

struct XVSegmentScanField //与XVSegmentFittingField取扫描线的方式不同
{
    XVOptionalType optional = ENABLE;
    XVSegment2D	axis;
    float	width;

    XVSegmentScanField(XVSegment2D axis_=XVSegment2D(), float width_=0, XVOptionalType opt_ = ENABLE){
        axis     = axis_;
        width    = width_;
        optional = opt_;
    }
};

//表示一个局部坐标系，包括参考点、旋转角度及缩放系数（一个匹配结果，用于对模板进行变换）
typedef struct XVCoordinateSystem2D
{
    XVOptionalType  optional = ENABLE;
    XVPoint2D       origin;
    float           angle;
    float           scale;

    XVCoordinateSystem2D(XVPoint2D origin_=XVPoint2D(0,0), float angle_=0, float scale_=1, XVOptionalType  optional_=ENABLE){
        optional = optional_;
        origin   = origin_  ;
        angle    = angle_   ;
        scale    = scale_   ;
    }
}XVCoordinateSystem2D;

struct XVObject2D
{
    XVOptionalType          optional = ENABLE;
    XVRectangle2D           match;     //一个矩形框
    XVCoordinateSystem2D    alignment; //（即定义一个局部的参考坐标系，在模板匹配中是模板之间的相互变换）
    XVPoint2D               point;     //目标在图像中的位置
    float                   angle;     //angle和scale跟alignment中的值相同
    float                   scale;
    float                   score;

    vector<XVPath>	    objectEdges;
};

struct XVProfile
{
    vector<XVPoint2D> dataArray;
};

struct XVColor
{
    int red;            //红
    int green;          //绿
    int blue;           //蓝
    int alpha = 255;    //色彩空间

    XVColor(int red_ = 255, int green_ = 0, int blue_ = 0, int alpha_ = 255):red(red_),green(green_),blue(blue_),alpha(alpha_){ }
};

struct XVChartItem
{
    string name;
    XVColor color;
    XVProfile itemdata;
};

struct XVChart
{
    string chart_Name;
    string x_Name;
    string y_Name;
    vector<XVChartItem> items;
};

struct XVLocalBlindness//这个参数是弱边缘点与强边缘点之间的位置关系
{
    XVOptionalType  optional = ENABLE;               //该结构体本身是否有效
    XVOptionalType  radiusOptional = ENABLE;         //半径是否有效
    float           radius;                 //半径
    float           threshold;              //阈值
    float           fuzziness;              //颜色容差

    XVLocalBlindness(){
        optional = ENABLE;
        radiusOptional = ENABLE;
        radius = 0;
        threshold=0.5f;
        fuzziness=0.0f;
    }
};

struct XVImageLocalExtremaVerification
{
    XVOptionalType  optional = ENABLE;
    int             pointCount;
    float           radius;
    float           minDifference;
};

struct XVExtremum2D
{
    XVPoint2D       point;
    float           value;
    XVPolarityType  polarity;
};

struct XVImageFormat
{
    int             width; // Image width in pixels
    int             height; // Image height in pixels
    XVPlainType     type; // Type of pixel components
    int             depth; // Number of pixel components
    int             pitchAlignment;
};
struct XVSpatialMapImpl
{
    //TODO
};
struct XVSpatialMap
{
    XVSpatialMapImpl* pImpl;
};

/////////////////////////////////////   ScanParams  /////////////////////////////////////////
typedef struct XVEdgeScanParams
{
    XVProfileInterpolationMethod    profileInterpolation; //(插值方法)Selects the method of sub-pixel precise edge detection     (Quadratic4)
    float                           smoothingStdDev;      //(滤波参数)Parameter for gaussian smoothing of the brightness profile (0.6)（StdDev决定形状 滤波器的大小？）
    float                           minMagnitude;         //(梯度阈值)Minimum acceptable edge strength                           (5)
    XVEdgeTransitionType            edgeTransition;       //(边缘类型)Specifies the type of edges to be detected.                (BrightToDark)
}XVEdgeScanParams;

typedef struct XVRidgeScanParams
{
    XVProfileInterpolationMethod    profileInterpolation; //Quadratic4 Selects the method of sub-pixel precise ridge detection
    float                           smoothingStdDev;      //0.6f       Parameter for gaussian smoothing of the brightness profile
    int                             ridgeWidth;           //5	       Expected thickness of the ridge in pixels ridge的宽度
    int                             ridgeMargin;          //2          Number of pixels that are sampled outside of the ridge, on both of its sides???
    XVRidgeOperatorType             ridgeOperator;        //Minimum    Selects the function used to combine the brightness on the left and on the right side of the ridge???
    float                           minMagnitude;         //5.0f       Minimum acceptable ridge strength 最小阈值
    XVPolarityType                  ridgePolarity;        //(Bright, Dark or Any) Specifies the type of ridges to be detected
}XVRidgeScanParams;

typedef struct XVStripeScanParams
{
    XVProfileInterpolationMethod    profileInterpolation;  //Quadratic4 Selects the method of sub-pixel precise ridge detection
    float			    smoothingStdDev;       //0.6f	Parameter for gaussian smoothing of the brightness profile
    float			    minMagnitude;          //5.0f	Minimum acceptable edge strength 注意这里还是边缘！！
    XVFloat			    maxInnerEdgeMagnitude; //           Maximum strength of edges appearing between the two ends of a stripe(条内部最大梯度不超过该值 默认值0时该参数不起作用)！！！！
    XVPolarityType                  stripePolarity;        //           Specifies the type of stripes to be detected (Bright, Dark or Any)
    float                           minStripeWidth;        //           Minimum acceptable stripe width in pixels （0）最小带宽
    XVFloat                         maxStripeWidth;        //           Maximum acceptable stripe width in pixels
}XVStripeScanParams;


#endif // XVBASE_H
