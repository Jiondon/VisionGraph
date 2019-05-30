#ifndef ADD_H
#define ADD_H

#include "add_global.h"


class ADDSHARED_EXPORT Add
{

public:
    Add();

    int sum(int a,int b);
};

extern "C" int ADDSHARED_EXPORT sum(int a,int b);

#endif // ADD_H
