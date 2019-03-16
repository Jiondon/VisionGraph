#ifndef VGBASE_H
#define VGBASE_H


#include <vector>
using namespace std;

typedef unsigned char BYTE;
typedef int           BOOL;
#define TRUE	1
#define FALSE	0


enum VGOptionalType
{
    VG_NUL,
    VG_ENABLE
};


typedef struct VGInt
{
    VGOptionalType  optional = VG_ENABLE;
    int             value;

    VGInt(int _value = 0, VGOptionalType _optional = VG_ENABLE){
        optional = _optional;
        value = _value;
    }
}VGInt;

typedef struct VGFloat
{
    VGOptionalType  optional = VG_ENABLE;
    float           value;

    VGFloat(float _value = 0, VGOptionalType _optional = VG_ENABLE){
        optional = _optional;
        value = _value;
    }
}VGFloat;

//像素
struct VGPixel
{
    VGOptionalType  optional = VG_ENABLE;
    float           x;
    float           y;
    float           z;
    float           w;

    VGPixel(float x_ = 0, float y_ = 0, float z_ = 0, float w_ = 0, VGOptionalType _optional = VG_ENABLE){
        optional = _optional;
        x = x_;
        y = y_;
        z = z_;
        w = w_;
    }
};


//二维点
typedef struct VGPoint2DInt
{
    VGOptionalType  optional = VG_ENABLE;
    int x;
    int y;

    VGPoint2DInt(int x_=0, int y_=0,VGOptionalType optional_ = VG_ENABLE){
        optional = optional_;
        x = x_;
        y = y_;
    }
}VGLocation;


struct VGPoint2D
{
    VGOptionalType optional = VG_ENABLE;
    float x;
    float y;

    VGPoint2D(float x_ = 0, float y_ = 0, VGOptionalType optional_ = VG_ENABLE){
        optional = optional_;
        x = x_;
        y = y_;
    }
    VGPoint2D(int x_, int y_, VGOptionalType optional_ = VG_ENABLE){
        optional = optional_;
        x = (float)x_;
        y = (float)y_;
    }
    VGPoint2D(int x_, float y_, VGOptionalType optional_ = VG_ENABLE){
        optional = optional_;
        x = (float)x_;
        y = y_;
    }
    VGPoint2D(float x_, int y_, VGOptionalType optional_ = VG_ENABLE){
        optional = optional_;
        x = x_;
        y = (float)y_;
    }

};

//三维点
struct VGPoint3D
{
    VGOptionalType optional = VG_ENABLE;
    float x;
    float y;
    float z;

    VGPoint3D(float x_=0, float y_=0, float z_=0, VGOptionalType optional_ = VG_ENABLE){
        optional = optional_;
        x = x_;
        y = y_;
        z = z_;
    }
};

//圆
struct VGCircle2D
{
    VGOptionalType  optional = VG_ENABLE;
    VGPoint2D       center;     //中心
    float           radius;     //半径

    VGCircle2D(VGPoint2D center_=VGPoint2D(), float radius_=0,  VGOptionalType opt_=VG_ENABLE){
        optional = opt_;
        center = center_;
        radius = radius_;
    }
};

//圆环域
struct VGCircleFittingField
{
    VGCircle2D	axis;  //扫描中心轴
    float	width; //扫描宽度

    VGCircleFittingField(VGCircle2D axis_=VGCircle2D() , float w_=0){
        axis = axis_;
        width = w_;
    }
};

//圆弧
struct VGArc2D
{
    VGPoint2D   center;     //中心
    float       radius;     //半径
    float       startAngle; //起始角度
    float       sweepAngle; //扫描角度


    VGArc2D(VGPoint2D   center_ = VGPoint2D(),
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
struct VGArcFittingField
{
    VGArc2D	axis;
    float	width;

    VGArcFittingField(VGArc2D axis_=VGArc2D() , float w_=0){
        axis = axis_;
        width = w_;
    }
};

//矩形及其旋转角度
typedef struct VGRectangle2D
{
    VGOptionalType optional = VG_ENABLE;
    VGPoint2D   origin; //顶点(左上点，不是中心)
    float       angle;  //旋转角度（绕中心旋转角度）
    float       width;  //宽度
    float       height; //高度

    VGRectangle2D(VGPoint2D origin_ = VGPoint2D(),
                  float     angle_  = 0,
                  float     width_  = 0,
                  float     height_ = 0,
                  VGOptionalType optional_ = VG_ENABLE){
        origin = origin_;
        angle  = angle_ ;
        width  = width_ ;
        height = height_;
        optional = optional_;
    }
}VGRectangle2D;

//Box
typedef struct VGBox
{
    VGOptionalType  optional = VG_ENABLE;
    VGPoint2DInt    origin; //顶点(左上点，不是中心)
    int             width;  //宽度
    int             height; //高度

    VGBox(VGPoint2DInt origin_=VGPoint2DInt(), int width_=0, int height_=0, VGOptionalType opt_=VG_ENABLE){
        optional =  opt_   ;
        origin   =  origin_;
        width    =  width_ ;
        height   =  height_;
    }
}VGBox;


enum VGPlainType
{
    VG_Int8,
    VG_UInt8,
    VG_Int16,
    VG_UInt16,
    VG_Int32,
    VG_Real
};

typedef struct VGImage
{
    int             width   ;			// number of pixel columns
    int             height  ;			// number of pixel rows
    VGPlainType	    type    ;                   // type of channels (默认UInt8)
    int             depth   ;			// number of channels(灰度图1)
    BYTE*           data    ;
}VGImage;


//直线ax + by + c = 0
struct VGLine2D
{
    VGOptionalType      optional = VG_ENABLE;
    float a;
    float b;
    float c;

    VGLine2D(float a_=0, float b_=0, float c_=0, VGOptionalType optional_ = VG_ENABLE)
    {
        optional = optional_;
        a = a_;
        b = b_;
        c = c_;
    }
};
//行程
struct VGPointRun
{
    int    x;
    int    y;  // PointRun begin location 起始点的x,y像素位置
    int    length;//行程

    VGPointRun(int x_=0, int y_=0, int length_=0){
        x = x_;
        y = y_;
        length = length_;
    }
};

typedef struct VGRegion
{
    VGOptionalType      optional = VG_ENABLE; //ROI是否起作用
    int                 frameWidth;
    int                 frameHeight;
    vector<VGPointRun>  arrayPointRun;

    VGRegion(){
        optional      = VG_ENABLE;
        frameWidth    = 0;
        frameHeight   = 0;
        arrayPointRun.clear();
    }

    VGRegion(int frameWidth_, int frameHeight_, const vector<VGPointRun> &arrayPointRun_, VGOptionalType optional_ = VG_ENABLE){
        optional      = optional_     ;
        frameWidth    = frameWidth_   ;
        frameHeight   = frameHeight_  ;
        arrayPointRun = arrayPointRun_;
    }
}VGRegion;

//路径或者链条
struct VGPath
{
    vector< VGPoint2D > arrayPoint2D;
    bool                closed;

    VGPath(){
        arrayPoint2D.clear();
        closed = false;
    }
    VGPath(const vector<VGPoint2D>& arrayPoint2D_, bool closed_){
        arrayPoint2D = arrayPoint2D_;
        closed = closed_;
    }
};

struct VGPathFittingField
{
    VGPath	axis;
    float	width;
};

//表示一个局部坐标系，包括参考点、旋转角度及缩放系数（一个匹配结果，用于对模板进行变换）
typedef struct VGCoordinateSystem2D
{
    VGOptionalType  optional = VG_ENABLE;
    VGPoint2D       origin;
    float           angle;
    float           scale;

    VGCoordinateSystem2D(VGPoint2D origin_=VGPoint2D(0,0), float angle_=0, float scale_=1, VGOptionalType  optional_=VG_ENABLE){
        optional = optional_;
        origin   = origin_  ;
        angle    = angle_   ;
        scale    = scale_   ;
    }
}VGCoordinateSystem2D;

struct VGObject2D
{
    VGOptionalType          optional = VG_ENABLE;
    VGRectangle2D           match;     //一个矩形框
    VGCoordinateSystem2D    alignment; //（即定义一个局部的参考坐标系，在模板匹配中是模板之间的相互变换）
    VGPoint2D               point;     //目标在图像中的位置
    float                   angle;     //angle和scale跟alignment中的值相同
    float                   scale;
    float                   score;

    vector<VGPath>	    objectEdges;
};

//通过起点和终点来表示一条有向线段
struct VGSegment2D
{
    VGOptionalType optional = VG_ENABLE;
    VGPoint2D point1; //起点
    VGPoint2D point2; //终点

    VGSegment2D(VGPoint2D p1=VGPoint2D(0,0), VGPoint2D p2=VGPoint2D(0,0), VGOptionalType opt=VG_ENABLE){
        point1 = p1;
        point2 = p2;
        optional = opt;
    }
};

struct VGSegmentFittingField
{
    VGSegment2D	axis;
    float       width = 20.0f;
};


struct VGColor
{
    int red;            //红
    int green;          //绿
    int blue;           //蓝
    int alpha = 255;    //色彩空间

    VGColor(int red_ = 255, int green_ = 0, int blue_ = 0, int alpha_ = 255):red(red_),green(green_),blue(blue_),alpha(alpha_){ }
};

#endif // VGBASE_H
