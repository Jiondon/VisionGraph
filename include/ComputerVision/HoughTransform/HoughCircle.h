//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _HOUGHCIRCLE_H
#define _HOUGHCIRCLE_H

#include "ATL/AtlTypes.h"
#include "Geometry/Geometry.h"

namespace avl
{
	struct HoughCircle
	{
		Circle2D	circle;
		Point2D		center;
		float		score;

		explicit HoughCircle
		(
			Circle2D circle_ = Circle2D(),
			Point2D center_ = Point2D(),
			float score_ = 0.0f 
		) :
			 circle(circle_),
			 center(center_),
			 score(score_) 
		{}

		Circle2D Circle() const	{ return circle;	};
		Point2D Center() const	{ return center;	};
		float Score() const		{ return score;		};

		bool operator == ( const avl::HoughCircle& rhs ) const
		{
			return circle == rhs.circle && 
			center == rhs.center && 
			score == rhs.score;
		}

		bool operator != ( const avl::HoughCircle& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

} //namespace avl


#endif

