#ifndef XVSCAN_H
#define XVSCAN_H

#include "XVGlobal.h"
#include "XVBaseType.h"
#include "XVEnums/XVPolarity.h"

enum XVMatchNumber {
    Single      ,   //单个
    Multiple    ,   //多个
    ExactlyN        //指定N个
};

//边缘跳变类型
enum XVEdgeTransitionType
{
    BrightToDark, // 由白到黑
    DarkToBright, // 由黑到白
    Any           // 任意
};

enum XVProfileInterpolationMethod //用于提取亚像素
{
    Linear,   					// 线性 Linear interpolation between consecutive points of the profile. (一维线性插值，是三个点的（位置*像素值）/(像素值求和)？)
    Quadratic3,   				// 三次 Interpolation that fits a parabola to 3 consecutive points.（拟合抛物线 求抛物线的最高点？）
    Quadratic4					// 四次 Interpolation that fits a parabola to 4 consecutive points.（哪4个点参与运算？）
};

enum XVRidgeOperatorType
{
    Minimum,
    GeometricMean,
    ArithmeticMean,
    HarmonicMean
};


//表示一个边缘点
struct XVEdge1D
{
    XVOptionalType          optional = NUL;
    XVPoint2D               point;      //坐标
    float                   magnitude;  //梯度幅值
    XVEdgeTransitionType    transition; //方向
};

//表示一维边缘检测函数找到的脊线 Represents ridges found by 1D Edge Detection functions
struct XVRidge1D
{
    XVOptionalType  optional = NUL;
    XVPoint2D       point;
    float           magnitude;
    XVPolarityType  polarity;
};

//表示一维边缘检测函数找到的条纹 Represents stripes found by 1D Edge Detection functions
struct XVStripe1D
{
    XVOptionalType      optional = NUL;
    XVPoint2D		point1      ;
    XVPoint2D           point2      ;
    float               width       ;
    float               magnitude   ;
    XVPolarityType	polarity    ;
};

//表示边缘点之间的距离
struct XVGap1D
{
    XVOptionalType  optional  = NUL;
    XVPoint2D       point1;
    XVPoint2D       point2;
    float           width;
};

struct XVEdgeScanParams
{
    XVProfileInterpolationMethod    profileInterpolation ;//= Quadratic4;               //(插值方法)Selects the method of sub-pixel precise edge detection     (Quadratic4)
    float                           smoothingStdDev      ;//= 0.6f;                     //(滤波参数)Parameter for gaussian smoothing of the brightness profile (0.6)（StdDev决定形状 滤波器的大小？）
    float                           minMagnitude         ;//= 5.0f;                     //(梯度阈值)Minimum acceptable edge strength                           (5)
    XVEdgeTransitionType            edgeTransition       ;//= XVEdgeTransitionType::Any;//(边缘类型)Specifies the type of edges to be detected.                (BrightToDark)
};

struct XVRidgeScanParams
{
    XVProfileInterpolationMethod    profileInterpolation ;//= Quadratic4   ;        //Quadratic4 Selects the method of sub-pixel precise ridge detection
    float                           smoothingStdDev      ;//= 0.6f         ;        //0.6f       Parameter for gaussian smoothing of the brightness profile
    int                             ridgeWidth           ;//= 5            ;        //5	       Expected thickness of the ridge in pixels ridge的宽度
    int                             ridgeMargin          ;//= 2            ;        //2          Number of pixels that are sampled outside of the ridge, on both of its sides???
    XVRidgeOperatorType             ridgeOperator        ;//= Minimum      ;        //Minimum    Selects the function used to combine the brightness on the left and on the right side of the ridge???
    float                           minMagnitude         ;//= 5.0f         ;        //5.0f       Minimum acceptable ridge strength 最小阈值
    XVPolarityType                  ridgePolarity        ;//= XVPolarityType::ANY;  //(Bright, Dark or Any) Specifies the type of ridges to be detected
};

struct XVStripeScanParams
{
    XVProfileInterpolationMethod    profileInterpolation  ;//= Quadratic4 ;        //Quadratic4 Selects the method of sub-pixel precise ridge detection
    float			    smoothingStdDev       ;//= 0.6f       ;        //0.6f	Parameter for gaussian smoothing of the brightness profile
    float			    minMagnitude          ;//= 5.0f       ;        //5.0f	Minimum acceptable edge strength 注意这里还是边缘！！
    XVFloat			    maxInnerEdgeMagnitude ;//= NUL        ;        //NUL   Maximum strength of edges appearing between the two ends of a stripe(条内部最大梯度不超过该值 默认值0时该参数不起作用)！！！！
    XVPolarityType                  stripePolarity        ;//= XVPolarityType::ANY;//ANY   Specifies the type of stripes to be detected (Bright, Dark or Any)
    float                           minStripeWidth        ;//= 0          ;        //0     Minimum acceptable stripe width in pixels （0）最小带宽
    XVFloat                         maxStripeWidth        ;//= NUL        ;        //NUL   Maximum acceptable stripe width in pixels
};

struct XVLocalBlindness//这个参数是弱边缘点与强边缘点之间的位置关系
{
    XVOptionalType  optional  ;//= NUL;
    XVFloat         radius    ;//= NUL;    //半径
    float           threshold ;//= 0.5f;   //阈值
    float           fuzziness ;//= 0.0f;   //颜色容差
};

struct XVArray_XVEdge1D
{
    XVOptionalType      optional = NUL;
    vector<XVEdge1D>    array;
};

struct XVArray_XVRidge1D
{
    XVOptionalType       optional = NUL;
    vector<XVRidge1D>    array;
};

struct XVArray_XVStripe1D
{
    XVOptionalType      optional = NUL;
    vector<XVStripe1D>  array;
};

struct XVArray_XVGap1D
{
    XVOptionalType      optional = NUL;
    vector<XVGap1D>     array;
};



#endif // XVSCAN_H
