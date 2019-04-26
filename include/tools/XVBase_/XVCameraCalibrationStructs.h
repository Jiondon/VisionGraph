#ifndef XVCAMERACALIBRATIONSTRUCTS_H
#define XVCAMERACALIBRATIONSTRUCTS_H

#include "XVOptional.h"

struct XVLensDistortion
{
    float	k1;
    float	k2;
    float	p1;
    float	p2;
    float	k3;
    float	k4;
    float	k5;
    float	k6;
    float	s1;
    float	s2;
    float	s3;
    float	s4;
    XVOptionalType      optional = NUL;
};

struct XVPosition3D
{
    float	x;
    float	y;
    float	z;
    float	phi;
    float	theta;
    float	psi;
    XVOptionalType      optional = NUL;
};

#endif

