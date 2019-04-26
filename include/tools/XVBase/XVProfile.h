#ifndef XVPROFILE_H
#define XVPROFILE_H

#include "XVGlobal.h"
#include "XVBaseType.h"

namespace XVProfileProcessingMode
{
    enum Type
    {
        Bounded,
        Cyclic
    };
}

//剖面图数据
struct XVProfile
{
    XVOptionalType          optional = NUL;
    vector<XVPoint2D>       dataArray;
};

static void CopyXVProfile(const XVProfile& src, XVProfile& dest){
    dest.optional = src.optional;
    dest.dataArray.clear();
    for(auto c : src.dataArray)
        dest.dataArray.push_back(c);
}

//颜色
struct XVColor
{
    int red;            //红
    int green;          //绿
    int blue;           //蓝
    int alpha = 255;    //色彩空间
};

//图表项
struct XVChartItem
{
    string      name;
    XVColor     color;
    XVProfile   itemdata;
};

//图表
struct XVChart
{
    string              chart_Name;
    string              x_Name;
    string              y_Name;
    vector<XVChartItem> items;
};

#endif // XVPROFILE_H
