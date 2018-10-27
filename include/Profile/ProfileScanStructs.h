//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _PROFILESCANSTRUCTS_H
#define _PROFILESCANSTRUCTS_H

#include "ATL/AtlTypes.h"
#include "Enums/EdgeTransition.h"
#include "Enums/Polarity.h"

namespace avl
{
	struct ProfileEdge
	{
		float					point;
		float					magnitude;
		EdgeTransition::Type	transition;

		explicit ProfileEdge
		(
			float point_ = 0.0f,
			float magnitude_ = 0.0f,
			EdgeTransition::Type transition_ = EdgeTransition::Any 
		) :
			 point(point_),
			 magnitude(magnitude_),
			 transition(transition_) 
		{}

		float Point() const						{ return point;			};
		float Magnitude() const					{ return magnitude;		};
		EdgeTransition::Type Transition() const	{ return transition;	};

		bool operator == ( const avl::ProfileEdge& rhs ) const
		{
			return point == rhs.point && 
			magnitude == rhs.magnitude && 
			transition == rhs.transition;
		}

		bool operator != ( const avl::ProfileEdge& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

	struct ProfileRidge
	{
		float			point;
		float			magnitude;
		Polarity::Type	polarity;

		explicit ProfileRidge
		(
			float point_ = 0.0f,
			float magnitude_ = 0.0f,
			Polarity::Type polarity_ = Polarity::Any 
		) :
			 point(point_),
			 magnitude(magnitude_),
			 polarity(polarity_) 
		{}

		float Point() const				{ return point;		};
		float Magnitude() const			{ return magnitude;	};
		Polarity::Type Polarity() const	{ return polarity;	};

		bool operator == ( const avl::ProfileRidge& rhs ) const
		{
			return point == rhs.point && 
			magnitude == rhs.magnitude && 
			polarity == rhs.polarity;
		}

		bool operator != ( const avl::ProfileRidge& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

	struct ProfileStripe
	{
		float			point1;
		float			point2;
		float			width;
		float			magnitude;
		Polarity::Type	polarity;

		explicit ProfileStripe
		(
			float point1_ = 0.0f,
			float point2_ = 0.0f,
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

		float Point1() const			{ return point1;	};
		float Point2() const			{ return point2;	};
		float Width() const				{ return width;		};
		float Magnitude() const			{ return magnitude;	};
		Polarity::Type Polarity() const	{ return polarity;	};

		bool operator == ( const avl::ProfileStripe& rhs ) const
		{
			return point1 == rhs.point1 && 
			point2 == rhs.point2 && 
			width == rhs.width && 
			magnitude == rhs.magnitude && 
			polarity == rhs.polarity;
		}

		bool operator != ( const avl::ProfileStripe& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

	struct ProfileSection
	{
		float	point1;
		float	point2;
		float	width;

		explicit ProfileSection
		(
			float point1_ = 0.0f,
			float point2_ = 0.0f,
			float width_ = 0.0f 
		) :
			 point1(point1_),
			 point2(point2_),
			 width(width_) 
		{}

		float Point1() const	{ return point1;	};
		float Point2() const	{ return point2;	};
		float Width() const		{ return width;		};

		bool operator == ( const avl::ProfileSection& rhs ) const
		{
			return point1 == rhs.point1 && 
			point2 == rhs.point2 && 
			width == rhs.width;
		}

		bool operator != ( const avl::ProfileSection& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

} //namespace avl


#endif

