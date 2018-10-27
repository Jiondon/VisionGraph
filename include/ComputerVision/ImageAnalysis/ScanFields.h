//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _SCANFIELDS_H
#define _SCANFIELDS_H

#include "ATL/AtlTypes.h"
#include "Geometry/Geometry.h"

namespace avl
{
	struct SegmentScanField
	{
		Segment2D	axis;
		float		width;

		explicit SegmentScanField
		(
			Segment2D axis_ = Segment2D(),
			float width_ = 20.0f 
		) :
			 axis(axis_),
			 width(width_) 
		{}

		Segment2D Axis() const	{ return axis;	};
		float Width() const		{ return width;	};

		bool operator == ( const avl::SegmentScanField& rhs ) const
		{
			return axis == rhs.axis && 
			width == rhs.width;
		}

		bool operator != ( const avl::SegmentScanField& rhs ) const
		{
			return !(operator==(rhs));
		}

		
			SegmentScanField(float x1, float y1, float x2, float y2, float width_)
		  :
			 axis(Segment2D(x1, y1, x2, y2)),
			 width(width_)
		{}
		
	SegmentScanField(Point2D point1, Point2D point2, float width_)
		  :
			 axis(Segment2D(point1, point2)),
			 width(width_)
		{}
		
	};

} //namespace avl


#endif

