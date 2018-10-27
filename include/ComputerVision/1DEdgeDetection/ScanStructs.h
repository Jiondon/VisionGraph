//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _SCANSTRUCTS_H
#define _SCANSTRUCTS_H

#include "ATL/AtlTypes.h"
#include "Enums/EdgeTransition.h"
#include "Enums/Polarity.h"
#include "Geometry/Geometry.h"

namespace avl
{
	struct Edge1D
	{
		Point2D					point;
		float					magnitude;
		EdgeTransition::Type	transition;

		explicit Edge1D
		(
			Point2D point_ = Point2D(),
			float magnitude_ = 0.0f,
			EdgeTransition::Type transition_ = EdgeTransition::Any 
		) :
			 point(point_),
			 magnitude(magnitude_),
			 transition(transition_) 
		{}

		Point2D Point() const					{ return point;			};
		float Magnitude() const					{ return magnitude;		};
		EdgeTransition::Type Transition() const	{ return transition;	};

		bool operator == ( const avl::Edge1D& rhs ) const
		{
			return point == rhs.point && 
			magnitude == rhs.magnitude && 
			transition == rhs.transition;
		}

		bool operator != ( const avl::Edge1D& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

	struct Ridge1D
	{
		Point2D			point;
		float			magnitude;
		Polarity::Type	polarity;

		explicit Ridge1D
		(
			Point2D point_ = Point2D(),
			float magnitude_ = 0.0f,
			Polarity::Type polarity_ = Polarity::Any 
		) :
			 point(point_),
			 magnitude(magnitude_),
			 polarity(polarity_) 
		{}

		Point2D Point() const			{ return point;		};
		float Magnitude() const			{ return magnitude;	};
		Polarity::Type Polarity() const	{ return polarity;	};

		bool operator == ( const avl::Ridge1D& rhs ) const
		{
			return point == rhs.point && 
			magnitude == rhs.magnitude && 
			polarity == rhs.polarity;
		}

		bool operator != ( const avl::Ridge1D& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

	struct Stripe1D
	{
		Point2D			point1;
		Point2D			point2;
		float			width;
		float			magnitude;
		Polarity::Type	polarity;

		explicit Stripe1D
		(
			Point2D point1_ = Point2D(),
			Point2D point2_ = Point2D(),
			float width_ = 0.0f,
			float magnitude_ = 0.0f,
			Polarity::Type polarity_ = Polarity::Any 
		) :
			 point1(point1_),
			 point2(point2_),
			 width(width_),
			 magnitude(magnitude_),
			 polarity(polarity_) 
		{}

		Point2D Point1() const			{ return point1;	};
		Point2D Point2() const			{ return point2;	};
		float Width() const				{ return width;		};
		float Magnitude() const			{ return magnitude;	};
		Polarity::Type Polarity() const	{ return polarity;	};

		bool operator == ( const avl::Stripe1D& rhs ) const
		{
			return point1 == rhs.point1 && 
			point2 == rhs.point2 && 
			width == rhs.width && 
			magnitude == rhs.magnitude && 
			polarity == rhs.polarity;
		}

		bool operator != ( const avl::Stripe1D& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

	struct Gap1D
	{
		Point2D	point1;
		Point2D	point2;
		float	width;

		explicit Gap1D
		(
			Point2D point1_ = Point2D(),
			Point2D point2_ = Point2D(),
			float width_ = 0.0f 
		) :
			 point1(point1_),
			 point2(point2_),
			 width(width_) 
		{}

		Point2D Point1() const	{ return point1;	};
		Point2D Point2() const	{ return point2;	};
		float Width() const		{ return width;		};

		bool operator == ( const avl::Gap1D& rhs ) const
		{
			return point1 == rhs.point1 && 
			point2 == rhs.point2 && 
			width == rhs.width;
		}

		bool operator != ( const avl::Gap1D& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

} //namespace avl


#endif

