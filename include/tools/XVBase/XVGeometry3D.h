#ifndef XVGEOMETRY3D_H
#define XVGEOMETRY3D_H

#include "XVOptional.h"

//三维点
struct XVPoint3D
{
    XVOptionalType optional = NUL;
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

struct XVVector3D
{
    XVOptionalType optional = NUL;
    float deltaX = 0.0f;
    float deltaY = 0.0f;
    float deltaZ = 0.0f;
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
    float x      = 0.0f;
    float y      = 0.0f;
    float z      = 0.0f;
    float deltaX = 0.0f;
    float deltaY = 0.0f;
    float deltaZ = 0.0f;
};

struct XVPlane3D
{
    XVOptionalType optional = NUL;
    float a = 0.0f;
    float b = 0.0f;
    float c = 0.0f;
    float d = 0.0f;
};

struct XVCircle3D
{
    XVOptionalType optional = NUL;
    XVPoint3D center;
    XVPlane3D plane;
    float radius = 0.0f;
};

struct XVBox3D
{
    XVOptionalType optional = NUL;
    float x       = 0.0f;
    float y       = 0.0f;
    float z       = 0.0f;
    float xLength = 0.0f;
    float yLength = 0.0f;
    float zLength = 0.0f;
};

struct XVSphere3D
{
    XVOptionalType optional = NUL;
    XVPoint3D center;
    float radius = 0.0f;
};


#endif // XVGEOMETRY3D_H
