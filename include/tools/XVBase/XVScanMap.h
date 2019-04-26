#ifndef XVCPPSCANMAP_H
#define XVCPPSCANMAP_H

#include "XVBase/XVPImpl.h"
#include "XVBase/XVError.h"

struct XVAvsScanMap;//仅前置声明
struct XVScanMap : public XVPImpl{

    XVScanMap() : XVPImpl(){}
    XVScanMap(const XVScanMap& rhs) : XVPImpl(rhs){}//浅拷贝
    XVScanMap(XVPImpl& rhs) : XVPImpl(rhs){//浅拷贝
        if(rhs.TypeMemo() != NameStr(XVScanMap))
            throw XVError(Domain_ERROR," XVScanMap(const XVPImpl& rhs), rhs.TypeMemo() != NameStr(XVScanMap)");
    }
    string TypeMemo(){
        return NameStr(XVScanMap);
    }
private:
    //私有反向构造 及 反向 "=" 重载，如需转换，必须使用子类的toParent()深拷贝函数
    XVScanMap(const XVAvsScanMap&){}
    XVScanMap& operator = (const XVAvsScanMap&){}
    //shared_ptr共享式智能指针不允许delete get()返回的原始指针
};

struct XVScanMapState : public XVBaseState
{
    XVScanMap scanMap;
};


#endif // XVCPPSCANMAP_H
