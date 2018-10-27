//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _OBJECT2D_H
#define _OBJECT2D_H

#include "ATL/AtlTypes.h"
#include "Geometry/Geometry.h"

namespace avl
{
	struct Object2D
	{
		Rectangle2D			match;
		CoordinateSystem2D	alignment;
		Point2D				point;
		float				angle;
		float				scale;
		float				score;

		explicit Object2D
		(
			Rectangle2D match_ = Rectangle2D(),
			CoordinateSystem2D alignment_ = CoordinateSystem2D(),
			Point2D point_ = Point2D(),
			float angle_ = 0.0f,
			float scale_ = 0.0f,
			float score_ = 0.0f 
		) :
			 match(match_),
			 alignment(alignment_),
			 point(point_),
			 angle(angle_),
			 scale(scale_),
			 score(score_) 
		{}

		Rectangle2D Match() const				{ return match;		};
		CoordinateSystem2D Alignment() const	{ return alignment;	};
		Point2D Point() const					{ return point;		};
		float Angle() const						{ return angle;		};
		float Scale() const						{ return scale;		};
		float Score() const						{ return score;		};

		bool operator == ( const avl::Object2D& rhs ) const
		{
			return match == rhs.match && 
			alignment == rhs.alignment && 
			point == rhs.point && 
			angle == rhs.angle && 
			scale == rhs.scale && 
			score == rhs.score;
		}

		bool operator != ( const avl::Object2D& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

} //namespace avl


#endif

