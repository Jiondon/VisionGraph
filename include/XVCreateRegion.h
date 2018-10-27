//工具的头文件
//创建区域

#ifndef	XVCREATEREGION_H
#define	XVCREATEREGION_H

#include "XVBase.h"
#include "AVL.h"


enum XVBorderPosition //圆环创建模式
{
	Internal,  //圆内部
	External,  //圆外部
	Centered   //圆居中
};

enum XVCreateRegionType
{
	Box1,          //框
	Rectangle,     //矩形
	Circle,        //圆
	Ellipse,       //椭圆
	Polygon,       //多边形
	Ring,          //环
	Segment,       //线段 
	Location1      //点集
};

typedef struct XVCreateRegionIn
{
	XVCreateRegionType inType;
	int   inFrameWidth;
	int   inFrameHeight;
	XVCoordinateSystem2D inAlignment; //可选

	//box
	XVBox inBox;

	//rectangle or Ellipse
	XVRectangle2D        inRectangle;

	//Circle or ring
	XVCircle2D           inCircle2D;

	//Polygon
	XVPath              inPolygon;

	//ring
	float				inRingWidth;
	XVBorderPosition	inBorderPosition;

	//Segment
	XVSegment2D			inSegment;
	int					inWidth;
	bool				inRound;  //端点是否为圆

	//location
	vector<XVLocation>  inLocation;

}XVCreateRegionIn;


typedef struct XVCreateRegionOut
{
	XVRegion     outregion;
	XVCreateRegionType outType;

	//Rectangle or Ellipse
	XVRectangle2D outAlignedRectangle;

	//Circle or Ring
	XVCircle2D    outAlignedCircle;
	
	//Polygon
	XVPath outAlignedPolygon;

	//Segment
	XVSegment2D   outAlignedSegment;
}XVCreateRegionOut;

 void XVCreateRegion(XVCreateRegionIn& CreateRegionIn, XVCreateRegionOut& CreateRegionOut);

#endif
