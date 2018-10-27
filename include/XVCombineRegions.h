//���ߵ�ͷ�ļ�
//������

#include "XVBase.h"
#include "AVL.h"


enum XVCombineRegionsType
{
	Difference,            //region1-region2
	Symmetricdiffence,     //����-����
	Intersection,          //����
	Union,                 //����
	Intersection_ofArray,  //����潻��
	Union_ofArray          //����沢��
};


typedef struct XVCombineRegionsIn
{
	XVCombineRegionsType   inCombineRegionsType;
	XVRegion*               inRegion1;
	XVRegion*               inRegion2;

	//combine Region of Array
	XVRegion* inInitialRegion;
	vector<XVRegion*> inRegionArray;

}XVCombineRegionsIn;

typedef struct XVCombineRegionsOut
{
	XVRegion RegionOut;
}XVCombineRegionsOut;

void XVCombineRegions(XVCombineRegionsIn& CombineRegionsIn, XVCombineRegionsOut& CombineRegionOut);