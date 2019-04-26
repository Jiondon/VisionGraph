#ifndef XVGEOMETRY3D_H
#define XVGEOMETRY3D_H

#include "XVOptional.h"

//三维点
struct XVPoint3D
{
    XVOptionalType optional = NUL;
    float x;
    float y;
    float z;
};

struct XVVector3D
{
    XVOptionalType optional = NUL;
    float deltaX;
    float deltaY;
    float deltaZ;
};

struct XVSegment3D
{
    XVOptionalType optional = NUL;
    XVPoint3D point1;
    XVPoint3D point2;
};

struct XVLine3D
{
    XVOptionalType optional = NUL;
    float x;
    float y;
    float z;
    float deltaX;
    float deltaY;
    float deltaZ;
};

struct XVPlane3D
{
    XVOptionalType optional = NUL;
    float a;
    float b;
    float c;
    float d;
};

struct XVCircle3D
{
    XVOptionalType optional = NUL;
    XVPoint3D center;
    XVPlane3D plane;
    float radius;
};

struct XVBox3D
{
    XVOptionalType optional = NUL;
    float x      ;
    float y      ;
    float z      ;
    float xLength;
    float yLength;
    float zLength;
};

struct XVSphere3D
{
    XVOptionalType optional = NUL;
    XVPoint3D center;
    float radius;
};


#endif // XVGEOMETRY3D_H
