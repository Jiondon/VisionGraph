//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _EXTREMUM2D_H
#define _EXTREMUM2D_H

#include "ATL/AtlTypes.h"
#include "Enums/Polarity.h"
#include "Geometry/Geometry.h"

namespace avl
{
	struct Extremum2D
	{
		Point2D			point;
		float			value;
		Polarity::Type	polarity;

		explicit Extremum2D
		(
			Point2D point_ = Point2D(),
			float value_ = 0.0f,
			Polarity::Type polarity_ = Polarity::Any 
		) :
			 point(point_),
			 value(value_),
			 polarity(polarity_) 
		{}

		Point2D Point() const			{ return point;		};
		float Value() const				{ return value;		};
		Polarity::Type Polarity() const	{ return polarity;	};

		bool operator == ( const avl::Extremum2D& rhs ) const
		{
			return point == rhs.point && 
			value == rhs.value && 
			polarity == rhs.polarity;
		}

		bool operator != ( const avl::Extremum2D& rhs ) const
		{
			return !(operator==(rhs));
		}

		
		bool operator < (const Extremum2D& rhs) const
		{
			return value < rhs.value;
		}
		
	};

} //namespace avl


#endif

