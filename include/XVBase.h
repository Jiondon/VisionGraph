#ifndef XVBASE_H
#define XVBASE_H

#include <vector>
using namespace std;

typedef unsigned char BYTE;
typedef int			  BOOL;
#define TRUE	1
#define FALSE	0

//��ʾͼ������ص���߶�ά�����Ԫ�ص�
struct XVLocation
{
	int x;
	int y;
};

//��ά��
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
//��ά��
struct XVPoint3D
{
	float x;
	float y;
	float z;
};

//Բ
struct XVCircle2D
{
	XVPoint2D center;//����
	float radius;    //�뾶
};

//Բ����
struct XVCircleFittingField
{
	XVCircle2D	axis;  //ɨ��������
	float		width; //ɨ����
};

//Բ��
struct XVArc2D
{
	XVPoint2D center; //����
	float radius;     //�뾶
	float startAngle; //��ʼ�Ƕ�
	float sweepAngle; //ɨ��Ƕ�
};

//Բ����
struct XVArcFittingField
{
	XVArc2D	axis;
	float	width; 
};

//���μ�����ת�Ƕ�
typedef struct XVRectangle2D
{
	XVPoint2D origin; //����(���ϵ㣬��������)
	float angle;      //��ת�Ƕȣ���������ת�Ƕȣ�
	float width;      //���
	float height;     //�߶�
}XVRectangle2D;

//Box
typedef struct XVBox
{
	XVPoint2D origin; //����(���ϵ㣬��������)
	float width;      //���
	float height;     //�߶�
}XVBox;

enum XVOptionalType
{
	NUL,
	ENABLE
};

//��Ե��������
enum XVEdgeTransitionType
{
	BrightToDark, // �ɰ׵���
	DarkToBright, // �ɺڵ���
	Any           // ����
};

//��ʾһ����Ե��
struct XVEdge1D
{
	XVPoint2D			    point;      //����
	float			        magnitude;  //�ݶȷ�ֵ
	XVEdgeTransitionType	transition; //����
};

//��ʾ��Ե��֮��ľ���
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
	XVPlainType	    type;	        // type of channels (Ĭ��UInt8)
	int				depth;			// number of channels(�Ҷ�ͼ1)
	BYTE*           data;

}XVImage;

//ֱ��ax + by + c = 0
struct XVLine2D
{
	float a;
	float b;
	float c;
};
//�г�
struct XVPointRun
{
	int    x;
	int    y;  // PointRun begin location ��ʼ���x,y����λ��
	int    length;//�г�
};

typedef struct XVRegion
{
	XVOptionalType  optional; //ROI�Ƿ�������
	int frameWidth;
	int frameHeight;
	vector<XVPointRun> arrayPointRun;
}XVRegion;

//·����������
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

//ͨ�������յ�����ʾһ�������߶�
struct XVSegment2D
{
	XVPoint2D point1; //���
	XVPoint2D point2; //�յ�
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

//��ʾһ���ֲ�����ϵ�������ο��㡢��ת�Ƕȼ�����ϵ����һ��ƥ���������ڶ�ģ����б任��
typedef struct XVCoordinateSystem2D
{
	XVOptionalType  optional; 
	XVPoint2D       origin;
	float angle;
	float scale;
}XVCoordinateSystem2D;

struct XVObject2D
{
	XVRectangle2D			match;     //һ�����ο�
	XVCoordinateSystem2D	alignment; //��������һ���ֲ��Ĳο�����ϵ����ģ��ƥ������ģ��֮����໥�任�� 
	XVPoint2D				point;     //Ŀ����ͼ���е�λ��
	float				    angle;     //angle��scale��alignment�е�ֵ��ͬ
	float				    scale;
	float				    score;

	vector<XVPath>	        objectEdges;
};
#endif // XVBASE_H