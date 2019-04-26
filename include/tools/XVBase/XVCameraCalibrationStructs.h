#ifndef XVCAMERACALIBRATIONSTRUCTS_H
#define XVCAMERACALIBRATIONSTRUCTS_H

#include "XVOptional.h"

struct XVLensDistortion
{
    float	k1 = 0.0f;
    float	k2 = 0.0f;
    float	p1 = 0.0f;
    float	p2 = 0.0f;
    float	k3 = 0.0f;
    float	k4 = 0.0f;
    float	k5 = 0.0f;
    float	k6 = 0.0f;
    float	s1 = 0.0f;
    float	s2 = 0.0f;
    float	s3 = 0.0f;
    float	s4 = 0.0f;
    XVOptionalType      optional = NUL;
};

struct XVPosition3D
{
    float	x     = 0.0f;
    float	y     = 0.0f;
    float	z     = 0.0f;
    float	phi   = 0.0f;
    float	theta = 0.0f;
    float	psi   = 0.0f;
    XVOptionalType      optional = NUL;
};

#endif

