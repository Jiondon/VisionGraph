#ifndef XVGEOMETRY_H
#define XVGEOMETRY_H

#include "XVGlobal.h"
#include "XVBaseType.h"

namespace XVShape2DType {
enum Type
{
    Circle            ,//圆
    Ellipse           ,//椭圆
    Line              ,//线
    Polygon           ,//多边形
    Rect              ,//填充矩形框
    Ring              ,//环
    PointArray        ,//点集
    LineArray         ,//线集
    BrokenLine         //折线
};
}

//直线ax + by + c = 0
struct XVLine2D
{
    XVOptionalType optional = NUL;
    float a;
    float b;
    float c;
};

//通过起点和终点来表示一条有向线段
struct XVSegment2D
{
    XVOptionalType optional = NUL;
    XVPoint2D point1; //起点
    XVPoint2D point2; //终点
};

//圆
struct XVCircle2D
{
    XVOptionalType  optional = NUL;
    XVPoint2D       center;     //中心
    float           radius;     //半径
};


//圆弧
struct XVArc2D
{
    XVOptionalType  optional = NUL;
    XVPoint2D   center;     //中心
    float       radius;     //半径
    float       startAngle; //起始角度
    float       sweepAngle; //扫描角度
};


//矩形及其旋转角度
struct XVRectangle2D
{
    XVOptionalType optional = NUL;
    XVPoint2D   origin; //顶点(左上点，不是中心)
    float       angle;  //旋转角度（绕中心旋转角度）
    float       width;  //宽度
    float       height; //高度
};


//表示一个局部坐标系，包括参考点、旋转角度及缩放系数（一个匹配结果，用于对模板进行变换）
struct XVCoordinateSystem2D
{
    XVOptionalType  optional = NUL;
    XVPoint2D       origin;
    float           angle;
    float           scale;
};

struct XVVector2D
{
    XVOptionalType  optional = NUL;
    float           deltaX  ;
    float           deltaY  ;
};

//文本
struct XVStringLabel
{
    string text;
    XVPoint2D position;
};

//所有图形总成
struct XVGlobal{
    XVOptionalType      optional = NUL;
    XVShape2DType::Type shape2D  = XVShape2DType::Rect;
    vector< XVPoint2D > arrayPoint2D;
};

namespace XVGeometryMatch {

inline float crossProduct(const XVVector2D &A, const XVVector2D &B)
{
    return A.deltaX * B.deltaY - A.deltaY * B.deltaX;
}

inline float dotProduct(const XVVector2D &A, const XVVector2D &B)
{
    return A.deltaX * B.deltaX + A.deltaY * B.deltaY;
}

inline XVPoint2D operator+(const XVPoint2D& p, const XVVector2D& v)
{
    XVPoint2D tmp;
    tmp.x = p.x + v.deltaX;
    tmp.y = p.y + v.deltaY;
    tmp.optional = ENABLE;
    return tmp;
}
inline XVPoint2D operator-(const XVPoint2D& p, const XVVector2D& v)
{
    XVPoint2D tmp;
    tmp.x = p.x - v.deltaX;
    tmp.y = p.y - v.deltaY;
    tmp.optional = ENABLE;
    return tmp;
}

inline XVVector2D operator-(const XVPoint2D& a, const XVPoint2D& b)
{
    XVVector2D tmp;
    tmp.deltaX = a.x - b.x;
    tmp.deltaY = a.y - b.y;
    tmp.optional = ENABLE;
    return tmp;
}
inline XVVector2D operator*(const XVVector2D& v, float a)
{
    XVVector2D tmp;
    tmp.deltaX = v.deltaX*a;
    tmp.deltaY = v.deltaY*a;
    tmp.optional = ENABLE;
    return tmp;
}
inline XVVector2D operator*(float a, const XVVector2D& v)
{
    XVVector2D tmp;
    tmp.deltaX = v.deltaX*a;
    tmp.deltaY = v.deltaY*a;
    tmp.optional = ENABLE;
    return tmp;
}
inline XVVector2D operator-(const XVVector2D& a, const XVVector2D& b)
{
    XVVector2D tmp;
    tmp.deltaX = a.deltaX - b.deltaX;
    tmp.deltaY = a.deltaY - b.deltaY;
    tmp.optional = ENABLE;
    return tmp;
}
inline XVVector2D operator+(const XVVector2D& a, const XVVector2D& b)
{
    XVVector2D tmp;
    tmp.deltaX = a.deltaX + b.deltaX;
    tmp.deltaY = a.deltaY + b.deltaY;
    tmp.optional = ENABLE;
    return tmp;
}

}


#endif // XVGEOMETRY_H
