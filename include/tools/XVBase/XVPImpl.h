#ifndef XVPIMPI_H
#define XVPIMPI_H

#include <memory>
#include "XVBase/XVGlobal.h"
#include "XVError.h"
#include "XVDataGlobal.h"

/** 所有不明内存的指针
 * @brief The XVPImpl struct
 */
struct XVPImpl : public XVDataGlobal
{
    std::shared_ptr<void> pImpl =  nullptr;//共享式智能指针
    XVOptionalType      optional = NUL;

    XVPImpl(){
        pImpl.reset();
        optional = NUL;
    }
    XVPImpl(const XVPImpl& rhs){//浅拷贝
        pImpl = rhs.pImpl;
        optional = rhs.optional;
        if(pImpl == nullptr)
            throw XVError(Domain_ERROR,"pImpl == nullptr !" );//抛出异常
    }

    string TypeMemo(){
        return NameStr(XVPImpl);
    }
};

struct XVBaseState
{
public:
    // Informs whether it is the first time this state is used
    bool IsFirstTime(){
        bool result = isFirstTime;
        isFirstTime = false;
        return result;
    }
protected:
    XVBaseState() : isFirstTime(true){}
private:
    bool isFirstTime;
};

#endif // XVPIMPI_H
