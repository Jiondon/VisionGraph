//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _PROFILEINTERPOLATIONMETHOD_H__
#define _PROFILEINTERPOLATIONMETHOD_H__

namespace avl
{
	namespace ProfileInterpolationMethod
	{
		enum Type
		{
			Linear,   					// Linear interpolation between consecutive points of the profile.
			Quadratic3,   				// Interpolation that fits a parabola to 3 consecutive points.
			Quadratic4					// Interpolation that fits a parabola to 4 consecutive points.
		};
	}
}

#endif
