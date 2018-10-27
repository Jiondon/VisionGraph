//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _SCANSTRUCTS3D_H
#define _SCANSTRUCTS3D_H

#include "ATL/AtlTypes.h"
#include "Enums/SurfaceEdgeTransition.h"
#include "Enums/SurfaceStripePolarity.h"
#include "Geometry3D/Geometry3D.h"

namespace avl
{
	struct SurfaceEdge1D
	{
		Point3D						point;
		float						magnitude;
		SurfaceEdgeTransition::Type	transition;

		explicit SurfaceEdge1D
		(
			Point3D point_ = Point3D(),
			float magnitude_ = 0.0f,
			SurfaceEdgeTransition::Type transition_ = SurfaceEdgeTransition::AnyLowHigh 
		) :
			 point(point_),
			 magnitude(magnitude_),
			 transition(transition_) 
		{}

		Point3D Point() const							{ return point;			};
		float Magnitude() const							{ return magnitude;		};
		SurfaceEdgeTransition::Type Transition() const	{ return transition;	};

		bool operator == ( const avl::SurfaceEdge1D& rhs ) const
		{
			return point == rhs.point && 
			magnitude == rhs.magnitude && 
			transition == rhs.transition;
		}

		bool operator != ( const avl::SurfaceEdge1D& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

	struct SurfaceStripe1D
	{
		Point3D						point1;
		Point3D						point2;
		float						width;
		float						magnitude;
		SurfaceStripePolarity::Type	polarity;

		explicit SurfaceStripe1D
		(
			Point3D point1_ = Point3D(),
			Point3D point2_ = Point3D(),
			float width_ = 0.0f,
			float magnitude_ = 0.0f,
			SurfaceStripePolarity::Type polarity_ = SurfaceStripePolarity::AnyLowHigh 
		) :
			 point1(point1_),
			 point2(point2_),
			 width(width_),
			 magnitude(magnitude_),
			 polarity(polarity_) 
		{}

		Point3D Point1() const							{ return point1;	};
		Point3D Point2() const							{ return point2;	};
		float Width() const								{ return width;		};
		float Magnitude() const							{ return magnitude;	};
		SurfaceStripePolarity::Type Polarity() const	{ return polarity;	};

		bool operator == ( const avl::SurfaceStripe1D& rhs ) const
		{
			return point1 == rhs.point1 && 
			point2 == rhs.point2 && 
			width == rhs.width && 
			magnitude == rhs.magnitude && 
			polarity == rhs.polarity;
		}

		bool operator != ( const avl::SurfaceStripe1D& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

} //namespace avl


#endif

