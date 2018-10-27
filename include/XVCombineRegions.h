//工具的头文件
//区域结合

#include "XVBase.h"
#include "AVL.h"


enum XVCombineRegionsType
{
	Difference,            //region1-region2
	Symmetricdiffence,     //并集-交集
	Intersection,          //交集
	Union,                 //并集
	Intersection_ofArray,  //数组版交集
	Union_ofArray          //数组版并集
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