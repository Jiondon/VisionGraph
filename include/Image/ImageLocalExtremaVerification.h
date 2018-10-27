//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _IMAGELOCALEXTREMAVERIFICATION_H
#define _IMAGELOCALEXTREMAVERIFICATION_H

#include "ATL/AtlTypes.h"

namespace avl
{
	struct ImageLocalExtremaVerification
	{
		int		pointCount;
		float	radius;
		float	minDifference;

		explicit ImageLocalExtremaVerification
		(
			int pointCount_ = 8,
			float radius_ = 3.0f,
			float minDifference_ = 0.0f 
		) :
			 pointCount(pointCount_),
			 radius(radius_),
			 minDifference(minDifference_) 
		{}

		int PointCount() const		{ return pointCount;	};
		float Radius() const		{ return radius;		};
		float MinDifference() const	{ return minDifference;	};

		bool operator == ( const avl::ImageLocalExtremaVerification& rhs ) const
		{
			return pointCount == rhs.pointCount && 
			radius == rhs.radius && 
			minDifference == rhs.minDifference;
		}

		bool operator != ( const avl::ImageLocalExtremaVerification& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

} //namespace avl


#endif

