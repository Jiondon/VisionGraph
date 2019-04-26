#ifndef XVERROR_H
#define XVERROR_H

#include <exception>
#include <string>

using namespace std;

//抛出异常列表
#define THROW_XV_ERRORS throw(...)

enum XVErrorType
{
    Any_ERROR,           //任意错误
    Io_ERROR,            //IO错误：与外部设备(磁盘、网络等)通信的异常
    System_ERROR,        //系统错误：操作系统的异常(内存、库、服务)
    Domain_ERROR,        //逻辑错误：用户不正确的数据输入或编程的异常
    License_ERROR,       //许可证错误：在许可证出现问题时抛出异常
    Runtime_ERROR,       //执行错误：函数无法完成时发生的异常
    Assertion_ERROR,     //断言错误
    Unhandled_ERROR,     //未处理
    Out_of_memory_ERROR, //内存溢出：当无法分配内存时发生异常
    NONE
};

static string ErrorTypeText(XVErrorType _type){
    switch (_type) {
    case Any_ERROR           : return "Any Error!";
    case Io_ERROR            : return "IO Error!";
    case System_ERROR        : return "System Error!";
    case Domain_ERROR        : return "Domain Error!";
    case License_ERROR       : return "License Error!";
    case Runtime_ERROR       : return "Runtime Error!";
    case Assertion_ERROR     : return "Assertion Error!";
    case Unhandled_ERROR     : return "Unhandled Error!";
    case Out_of_memory_ERROR : return "Out of memory Error!";
    case NONE                : return "No Error!";
    default                  : return "Unknow Error!";
    }
}

class XVError : public std::exception
{
public:
    XVError(const string& text) : exception(text.c_str()), mErrType(Any_ERROR){}
    XVError(XVErrorType errtype, const string& text = "") : std::exception(text.c_str()), mErrType(errtype){}

    XVErrorType ErrorType() const {return mErrType;}

private:
    XVErrorType mErrType;
    string msg;
};

#endif // XVERROR_H
