#ifndef XVTEMPLATE2D_H
#define XVTEMPLATE2D_H

#include "XVPImpl.h"

struct XVAvsEdgeModel;//仅前置声明
struct XVEdgeModel : public XVPImpl{

    XVEdgeModel() : XVPImpl(){}
    XVEdgeModel(const XVEdgeModel& rhs) : XVPImpl(rhs){}//浅拷贝
    XVEdgeModel(XVPImpl& rhs) : XVPImpl(rhs){
        if(rhs.TypeMemo() != NameStr(XVEdgeModel)){
            throw XVError(Domain_ERROR," XVEdgeModel(const XVPImpl& rhs), rhs.TypeMemo() != NameStr(XVEdgeModel)");
        }
    }//浅拷贝
    string TypeMemo(){
        return NameStr(XVEdgeModel);
    }
private:
    //私有反向构造 及 反向 "=" 重载，如需转换，必须使用子类的toParent()深拷贝函数
    XVEdgeModel(const XVAvsEdgeModel&){}
    XVEdgeModel& operator = (const XVAvsEdgeModel&){}
    //shared_ptr共享式智能指针不允许delete get()返回的原始指针
};

struct XVAvsGrayModel;//仅前置声明
struct  XVGrayModel : public XVPImpl{

    XVGrayModel() : XVPImpl(){}
    XVGrayModel(const XVGrayModel& rhs) : XVPImpl(rhs){}//浅拷贝
    XVGrayModel(XVPImpl& rhs) : XVPImpl(rhs){
        if(rhs.TypeMemo() != NameStr(XVGrayModel)){
            throw XVError(Domain_ERROR," XVGrayModel(const XVPImpl& rhs), rhs.TypeMemo() != NameStr(XVGrayModel)");
        }
    }//浅拷贝
    string TypeMemo(){
        return NameStr(XVGrayModel);
    }
private:
    //私有反向构造 及 反向 "=" 重载，如需转换，必须使用子类的toParent()深拷贝函数
    XVGrayModel(const XVAvsGrayModel&){}
    XVGrayModel& operator = (const XVAvsGrayModel&){}
    //shared_ptr共享式智能指针不允许delete get()返回的原始指针
};

#endif // XVTEMPLATE2D_H
