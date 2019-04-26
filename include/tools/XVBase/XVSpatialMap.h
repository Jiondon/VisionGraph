#ifndef XVSPATIALMAP_H
#define XVSPATIALMAP_H

#include "XVPImpl.h"


struct XVAvsSpatialMap;//仅前置声明
struct XVSpatialMap : public XVPImpl{

    XVSpatialMap() : XVPImpl(){}
    XVSpatialMap(const XVSpatialMap& rhs) : XVPImpl(rhs){}//浅拷贝
    XVSpatialMap(XVPImpl& rhs) : XVPImpl(rhs){//浅拷贝
        if(rhs.TypeMemo() != NameStr(XVSpatialMap))
            throw XVError(Domain_ERROR," XVSpatialMap(const XVPImpl& rhs), rhs.TypeMemo() != NameStr(XVSpatialMap)");
    }
    string TypeMemo(){
        return NameStr(XVSpatialMap);
    }
private:
    //私有反向构造 及 反向 "=" 重载，如需转换，必须使用子类的toParent()深拷贝函数
    XVSpatialMap(const XVAvsSpatialMap&){}
    XVSpatialMap& operator = (const XVAvsSpatialMap&){}
    //shared_ptr共享式智能指针不允许delete get()返回的原始指针
};

#endif // XVSPATIALMAP_H
