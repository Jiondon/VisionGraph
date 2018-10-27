//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _METRIC_H__
#define _METRIC_H__

namespace avl
{
	namespace Metric
	{
		enum Type 						// Two-point distance calculation method
		{
			Taxi, 						// Rectilinear distance
			Maximum,  					// Chebyshev distance
			Euclidean 					// Euclidean metric distance
		};
	}
}

#endif
