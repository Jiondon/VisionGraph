#ifndef XVBASE_H
#define XVBASE_H

#include <vector>
using namespace std;

typedef unsigned char BYTE;
typedef int			  BOOL;
#define TRUE	1
#define FALSE	0

//表示图像的像素点或者二维矩阵的元素等
struct XVLocation
{
	int x;
	int y;
};

//二维点
struct XVPoint2DInt
{
	int x;
	int y;
};

struct XVPoint2D
{
	float x;
	float y;
};
//三维点
struct XVPoint3D
{
	float x;
	float y;
	float z;
};

//圆
struct XVCircle2D
{
	XVPoint2D center;//中心
	float radius;    //半径
};

//圆环域
struct XVCircleFittingField
{
	XVCircle2D	axis;  //扫描中心轴
	float		width; //扫描宽度
};

//圆弧
struct XVArc2D
{
	XVPoint2D center; //中心
	float radius;     //半径
	float startAngle; //起始角度
	float sweepAngle; //扫描角度
};

//圆弧域
struct XVArcFittingField
{
	XVArc2D	axis;
	float	width; 
};

//矩形及其旋转角度
typedef struct XVRectangle2D
{
	XVPoint2D origin; //顶点(左上点，不是中心)
	float angle;      //旋转角度（绕中心旋转角度）
	float width;      //宽度
	float height;     //高度
}XVRectangle2D;

//Box
typedef struct XVBox
{
	XVPoint2D origin; //顶点(左上点，不是中心)
	float width;      //宽度
	float height;     //高度
}XVBox;

enum XVOptionalType
{
	NUL,
	ENABLE
};

//边缘跳变类型
enum XVEdgeTransitionType
{
	BrightToDark, // 由白到黑
	DarkToBright, // 由黑到白
	Any           // 任意
};

//表示一个边缘点
struct XVEdge1D
{
	XVPoint2D			    point;      //坐标
	float			        magnitude;  //梯度幅值
	XVEdgeTransitionType	transition; //方向
};

//表示边缘点之间的距离
struct XVGap1D
{
	XVPoint2D	point1;
	XVPoint2D	point2;
	float	width;
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
	int				width;			// number of pixel columns
	int				height;			// number of pixel rows
	XVPlainType	    type;	        // type of channels (默认UInt8)
	int				depth;			// number of channels(灰度图1)
	BYTE*           data;

}XVImage;

//直线ax + by + c = 0
struct XVLine2D
{
	float a;
	float b;
	float c;
};
//行程
struct XVPointRun
{
	int    x;
	int    y;  // PointRun begin location 起始点的x,y像素位置
	int    length;//行程
};

typedef struct XVRegion
{
	XVOptionalType  optional; //ROI是否起作用
	int frameWidth;
	int frameHeight;
	vector<XVPointRun> arrayPointRun;
}XVRegion;

//路径或者链条
struct XVPath
{
	vector< XVPoint2D > arrayPoint2D;
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
	float		    magnitude;
	XVPolarityType	polarity;
};
//Represents stripes found by 1D Edge Detection functions
struct XVStripe1D
{
	XVPoint2D		point1;
	XVPoint2D	    point2;
	float			width;
	float			magnitude;
	XVPolarityType	polarity;
};

//通过起点和终点来表示一条有向线段
struct XVSegment2D
{
	XVPoint2D point1; //起点
	XVPoint2D point2; //终点
};

struct XVSegmentFittingField
{
	XVSegment2D	axis;
	float		width;
};

struct XVSegmentScanField
{
	XVSegment2D	axis;
	float		width;
};

//表示一个局部坐标系，包括参考点、旋转角度及缩放系数（一个匹配结果，用于对模板进行变换）
typedef struct XVCoordinateSystem2D
{
	XVOptionalType  optional; 
	XVPoint2D       origin;
	float angle;
	float scale;
}XVCoordinateSystem2D;

struct XVObject2D
{
	XVRectangle2D			match;     //一个矩形框
	XVCoordinateSystem2D	alignment; //（即定义一个局部的参考坐标系，在模板匹配中是模板之间的相互变换） 
	XVPoint2D				point;     //目标在图像中的位置
	float				    angle;     //angle和scale跟alignment中的值相同
	float				    scale;
	float				    score;

	vector<XVPath>	        objectEdges;
};
#endif // XVBASE_H