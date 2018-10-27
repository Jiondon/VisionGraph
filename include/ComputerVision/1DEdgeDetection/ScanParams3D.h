//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _SCANPARAMS3D_H
#define _SCANPARAMS3D_H

#include "ATL/AtlTypes.h"
#include "ATL/Optional.h"
#include "Enums/ProfileInterpolationMethod.h"
#include "Enums/SurfaceEdgeTransition.h"
#include "Enums/SurfaceStripePolarity.h"

namespace avl
{
	struct EdgeScanParams3D
	{
		ProfileInterpolationMethod::Type	profileInterpolation;
		float								smoothingStdDev;
		float								minMagnitude;
		SurfaceEdgeTransition::Type			edgeTransition;

		explicit EdgeScanParams3D
		(
			ProfileInterpolationMethod::Type profileInterpolation_ = ProfileInterpolationMethod::Quadratic4,
			float smoothingStdDev_ = 0.6f,
			float minMagnitude_ = 5.0f,
			SurfaceEdgeTransition::Type edgeTransition_ = SurfaceEdgeTransition::HighToLow 
		) :
			 profileInterpolation(profileInterpolation_),
			 smoothingStdDev(smoothingStdDev_),
			 minMagnitude(minMagnitude_),
			 edgeTransition(edgeTransition_) 
		{}

		ProfileInterpolationMethod::Type ProfileInterpolation() const	{ return profileInterpolation;	};
		float SmoothingStdDev() const									{ return smoothingStdDev;		};
		float MinMagnitude() const										{ return minMagnitude;			};
		SurfaceEdgeTransition::Type EdgeTransition() const				{ return edgeTransition;		};

		bool operator == ( const avl::EdgeScanParams3D& rhs ) const
		{
			return profileInterpolation == rhs.profileInterpolation && 
			smoothingStdDev == rhs.smoothingStdDev && 
			minMagnitude == rhs.minMagnitude && 
			edgeTransition == rhs.edgeTransition;
		}

		bool operator != ( const avl::EdgeScanParams3D& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

	struct StripeScanParams3D
	{
		ProfileInterpolationMethod::Type	profileInterpolation;
		float								smoothingStdDev;
		float								minMagnitude;
		atl::Optional<float>				maxInnerEdgeMagnitude;
		SurfaceStripePolarity::Type			stripePolarity;
		float								minStripeWidth;
		atl::Optional<float>				maxStripeWidth;

		explicit StripeScanParams3D
		(
			ProfileInterpolationMethod::Type profileInterpolation_ = ProfileInterpolationMethod::Quadratic4,
			float smoothingStdDev_ = 0.6f,
			float minMagnitude_ = 5.0f,
			atl::Optional<float> maxInnerEdgeMagnitude_ = atl::NIL,
			SurfaceStripePolarity::Type stripePolarity_ = SurfaceStripePolarity::High,
			float minStripeWidth_ = 0.0f,
			atl::Optional<float> maxStripeWidth_ = atl::NIL 
		) :
			 profileInterpolation(profileInterpolation_),
			 smoothingStdDev(smoothingStdDev_),
			 minMagnitude(minMagnitude_),
			 maxInnerEdgeMagnitude(maxInnerEdgeMagnitude_),
			 stripePolarity(stripePolarity_),
			 minStripeWidth(minStripeWidth_),
			 maxStripeWidth(maxStripeWidth_) 
		{}

		ProfileInterpolationMethod::Type ProfileInterpolation() const	{ return profileInterpolation;	};
		float SmoothingStdDev() const									{ return smoothingStdDev;		};
		float MinMagnitude() const										{ return minMagnitude;			};
		atl::Optional<float> MaxInnerEdgeMagnitude() const				{ return maxInnerEdgeMagnitude;	};
		SurfaceStripePolarity::Type StripePolarity() const				{ return stripePolarity;		};
		float MinStripeWidth() const									{ return minStripeWidth;		};
		atl::Optional<float> MaxStripeWidth() const						{ return maxStripeWidth;		};

		bool operator == ( const avl::StripeScanParams3D& rhs ) const
		{
			return profileInterpolation == rhs.profileInterpolation && 
			smoothingStdDev == rhs.smoothingStdDev && 
			minMagnitude == rhs.minMagnitude && 
			maxInnerEdgeMagnitude == rhs.maxInnerEdgeMagnitude && 
			stripePolarity == rhs.stripePolarity && 
			minStripeWidth == rhs.minStripeWidth && 
			maxStripeWidth == rhs.maxStripeWidth;
		}

		bool operator != ( const avl::StripeScanParams3D& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

} //namespace avl


#endif

