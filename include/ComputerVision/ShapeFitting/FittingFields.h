//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _FITTINGFIELDS_H
#define _FITTINGFIELDS_H

#include "ATL/AtlTypes.h"
#include "Geometry/Geometry.h"
#include "Path/Path.h"

namespace avl
{
	struct CircleFittingField
	{
		Circle2D	axis;
		float		width;

		explicit CircleFittingField
		(
			Circle2D axis_ = Circle2D(),
			float width_ = 20.0f 
		) :
			 axis(axis_),
			 width(width_) 
		{}

		Circle2D Axis() const	{ return axis;	};
		float Width() const		{ return width;	};

		bool operator == ( const avl::CircleFittingField& rhs ) const
		{
			return axis == rhs.axis && 
			width == rhs.width;
		}

		bool operator != ( const avl::CircleFittingField& rhs ) const
		{
			return !(operator==(rhs));
		}

		
			CircleFittingField(Point2D p, float r, float width_)
	  :
		 axis(Circle2D(p, r)),
		 width(width_)
	{}
	
	CircleFittingField(float x, float y, float r, float width_)
	  :
		 axis(Circle2D(x, y, r)),
		 width(width_)
	{}
		
	};

	struct ArcFittingField
	{
		Arc2D	axis;
		float	width;

		explicit ArcFittingField
		(
			Arc2D axis_ = Arc2D(),
			float width_ = 20.0f 
		) :
			 axis(axis_),
			 width(width_) 
		{}

		Arc2D Axis() const	{ return axis;	};
		float Width() const	{ return width;	};

		bool operator == ( const avl::ArcFittingField& rhs ) const
		{
			return axis == rhs.axis && 
			width == rhs.width;
		}

		bool operator != ( const avl::ArcFittingField& rhs ) const
		{
			return !(operator==(rhs));
		}

		
			ArcFittingField(Point2D p, float r, float startAngle, float sweepAngle, float width_)
		  :
			 axis(Arc2D(p, r, startAngle, sweepAngle)),
			 width(width_)
		{}
	
	ArcFittingField(float x, float y, float r, float startAngle, float sweepAngle, float width_)
		  :
			 axis(Arc2D(x, y, r, startAngle, sweepAngle)),
			 width(width_)
		{}
		
	};

	struct SegmentFittingField
	{
		Segment2D	axis;
		float		width;

		explicit SegmentFittingField
		(
			Segment2D axis_ = Segment2D(),
			float width_ = 20.0f 
		) :
			 axis(axis_),
			 width(width_) 
		{}

		Segment2D Axis() const	{ return axis;	};
		float Width() const		{ return width;	};

		bool operator == ( const avl::SegmentFittingField& rhs ) const
		{
			return axis == rhs.axis && 
			width == rhs.width;
		}

		bool operator != ( const avl::SegmentFittingField& rhs ) const
		{
			return !(operator==(rhs));
		}

		
			SegmentFittingField(float x1, float y1, float x2, float y2, float width_)
		  :
			 axis(Segment2D(x1, y1, x2, y2)),
			 width(width_)
		{}
	
	SegmentFittingField(Point2D point1, Point2D point2, float width_)
		  :
			 axis(Segment2D(point1, point2)),
			 width(width_)
		{}
		
	};

	struct PathFittingField
	{
		Path	axis;
		float	width;

		explicit PathFittingField
		(
			Path axis_ = Path(),
			float width_ = 20.0f 
		) :
			 axis(axis_),
			 width(width_) 
		{}

		Path Axis() const	{ return axis;	};
		float Width() const	{ return width;	};

		bool operator == ( const avl::PathFittingField& rhs ) const
		{
			return axis == rhs.axis && 
			width == rhs.width;
		}

		bool operator != ( const avl::PathFittingField& rhs ) const
		{
			return !(operator==(rhs));
		}

		
			PathFittingField(const atl::Array<Point2D>& points, bool closed, float width_)
		  :
			 axis(Path(points, closed)),
			 width(width_)
		{}
		
	};

} //namespace avl


#endif

