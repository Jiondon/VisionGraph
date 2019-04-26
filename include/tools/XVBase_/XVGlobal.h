#ifndef XVGLOBAL_H
#define XVGLOBAL_H

#include <vector>
#include "XVOptional.h"

using namespace std;


typedef unsigned char BYTE;
typedef int           BOOL;
#define TRUE	1
#define FALSE	0


//('#'是为后面的任意添加双引号) 用法 ： NameStr(*) -> "*"
#define NameStr(X) #X

#endif // XVGLOBAL_H
