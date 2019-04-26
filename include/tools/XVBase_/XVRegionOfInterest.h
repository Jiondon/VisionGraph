#ifndef XVREGIONOFINTEREST_H
#define XVREGIONOFINTEREST_H

#include "XVRegion.h"
#include "XVGeometry.h"
#include "XVPath.h"

namespace XVRegionOfInterestType//感兴趣区域类型
{
    enum Type
    {
        Region      ,
        Rectangle   ,
        Circle      ,
        Polygon
    };
}

struct XVRegionOfInterest
{
    XVOptionalType               optional = NUL;
    XVRegionOfInterestType::Type tag        ;
    XVRegion                     region     ;
    XVRectangle2D                rectangle  ;
    XVCircle2D                   circle     ;
    XVPath                       polygon    ;
};

#endif // XVXVRegionOfInterest_H
